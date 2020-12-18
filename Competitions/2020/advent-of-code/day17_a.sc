import scala.io.Source.fromFile
import java.io.File
import scala.util.matching.Regex
import scala.collection.mutable.{Map => MutableMap, Set => MutableSet}


type Grid = MutableMap[Int, MutableMap[Int, MutableMap[Int, Boolean]]]

def isCurrentActive(z: Int, x: Int, y: Int, active: Grid): Boolean = 
    active.get(z)
        .flatMap(_.get(x)
        .flatMap(_.get(y)))
        .getOrElse(false)

def findActiveNeighbours(z: Int, x: Int, y: Int, active: Grid): Int = {
    var count = 0

    (-1 to 1).foreach { i =>
        (-1 to 1).foreach { j =>
            (-1 to 1).foreach { k =>
                if (i != 0 || j != 0 || k != 0) {
                    if (isCurrentActive(z + i, x + j, y + k, active))
                        count += 1
                }
            }
        }
    }

    count
}

def solveFirstPart(file: File): Long = {
    val active = MutableMap.empty[Int, MutableMap[Int, MutableMap[Int, Boolean]]]
    active += (0 -> MutableMap.empty)

    fromFile(file).getLines().zipWithIndex.foreach { case (line, i) =>
        active(0) += (i -> MutableMap.empty)
        line.zipWithIndex.foreach { case (c, j) =>
            active(0)(i) += (j -> (c == '#'))
        }
    }

    @annotation.tailrec
    def solve(i: Int, active: Grid): Long = {
        if (i >= 6) {
            active.foldLeft(0L) { case (res, (_, z)) =>
                res + z.foldLeft(0L) { case (sumRes, (_, x)) =>
                    sumRes + x.count { case (_, y) => y }
                }
            }
        } else {
            val minz = active.keys.min - 1
            val maxz = active.keys.max + 1
            val minx = active.head._2.keys.min - 1
            val maxx = active.head._2.keys.max + 1
            val miny = active.head._2.head._2.keys.min - 1
            val maxy = active.head._2.head._2.keys.max + 1
            val next = MutableMap.empty[Int, MutableMap[Int, MutableMap[Int, Boolean]]]

            (minz to maxz).foreach { z =>
                next += (z -> MutableMap.empty)
                (minx to maxx).foreach { x =>
                    next(z) += (x -> MutableMap.empty)
                    (miny to maxy).foreach { y =>
                        val currentActive = isCurrentActive(z, x, y, active)
                        val numActiveNeighbours = findActiveNeighbours(z, x, y, active)
                        if (currentActive)
                            next(z)(x) += (y -> (numActiveNeighbours == 2 || numActiveNeighbours == 3))
                        else
                            next(z)(x) += (y -> (numActiveNeighbours == 3))
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