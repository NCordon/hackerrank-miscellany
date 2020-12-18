import scala.io.Source.fromFile
import java.io.File
import scala.util.matching.Regex
import scala.collection.mutable.{Map => MutableMap, Set => MutableSet}


type Grid = MutableMap[Int, MutableMap[Int, MutableMap[Int, MutableMap[Int, Boolean]]]]

def isCurrentActive(w: Int, z: Int, x: Int, y: Int, active: Grid): Boolean = 
    active
        .get(w)
        .flatMap(_.get(z)
        .flatMap(_.get(x))
        .flatMap(_.get(y)))
        .getOrElse(false)

def findActiveNeighbours(w: Int, z: Int, x: Int, y: Int, active: Grid): Int = {
    var count = 0

    (-1 to 1).foreach { i =>
        (-1 to 1).foreach { j =>
            (-1 to 1).foreach { k =>
                (-1 to 1).foreach { q =>
                    if (i != 0 || j != 0 || k != 0 || q != 0) {
                        if (isCurrentActive(w + i, z + j, x + k, y + q, active))
                            count += 1
                    }
                }
            }   
        }
    }

    count
}

def solveFirstPart(file: File): Long = {
    val active: Grid = MutableMap.empty
    active += (0 -> MutableMap(0 -> MutableMap.empty))

    fromFile(file).getLines().zipWithIndex.foreach { case (line, i) =>
        active(0)(0) += (i -> MutableMap.empty)
        line.zipWithIndex.foreach { case (c, j) =>
            active(0)(0)(i) += (j -> (c == '#'))
        }
    }

    @annotation.tailrec
    def solve(i: Int, active: Grid): Long = {
        if (i >= 6) {
            active.foldLeft(0L) { case (resw, (_, w)) =>
                resw + w.foldLeft(0L) { case (resz, (_, z)) =>
                    resz + z.foldLeft(0L) { case (resx, (_, x)) =>
                        resx + x.count { case (_, y) => y }
                    }
                }
            }
        } else {
            val minw = active.keys.min - 1
            val maxw = active.keys.max + 1
            val minz = active.head._2.keys.min - 1
            val maxz = active.head._2.keys.max + 1
            val minx = active.head._2.head._2.keys.min - 1
            val maxx = active.head._2.head._2.keys.max + 1
            val miny = active.head._2.head._2.head._2.keys.min - 1
            val maxy = active.head._2.head._2.head._2.keys.max + 1
            val next: Grid = MutableMap.empty

            (minw to maxw).foreach { w =>
                next += (w -> MutableMap.empty)
                (minz to maxz).foreach { z =>
                    next(w) += (z -> MutableMap.empty)
                    (minx to maxx).foreach { x =>
                        next(w)(z) += (x -> MutableMap.empty)
                        (miny to maxy).foreach { y =>
                            val currentActive = isCurrentActive(w, z, x, y, active)
                            val numActiveNeighbours = findActiveNeighbours(w, z, x, y, active)
                            if (currentActive)
                                next(w)(z)(x) += (y -> (numActiveNeighbours == 2 || numActiveNeighbours == 3))
                            else
                                next(w)(z)(x) += (y -> (numActiveNeighbours == 3))
                        }
                    }
                }
            }

            solve(i + 1, next)
        }
    }

    solve(0, active)
}

@main
def main(args: String*) = {
    if (args.size == 0) {
        System.err.println("Your script requires the first argument to be the input file")
        exit(-1)
    }
    val inputFile = new File(args(0))
    println(solveFirstPart(inputFile))
}