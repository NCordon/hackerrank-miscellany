import scala.io.Source.fromFile
import java.io.File
import scala.util.matching.Regex
import scala.collection.mutable.{Map => MutableMap, Set => MutableSet}

def solveFirstPart(file: File): Int = {
    val lines = fromFile(file).getLines().toList
    val visited = Array.fill(lines.size)(false)

    val nop = """nop (.*)""".r
    val acc = """acc (\+|\-)([0-9]+)""".r
    val jmp = """jmp (\+|\-)([0-9]+)""".r

    @annotation.tailrec
    def recSolve(i: Int, sol: Int): Int = {
        if (visited(i)) {
            sol
        } else {
            visited(i) = true
            val op = lines(i)

            val (nextIndx, nextSol)  = op match {
                case nop(_) => (i + 1, sol)
                case acc(sign, inc) => (i + 1, sol + s"${sign}${inc}".toInt)
                case jmp(sign, inc) => (i + s"${sign}${inc}".toInt, sol)
            }

            recSolve(nextIndx, nextSol)
        }
    }

    recSolve(0, sol = 0)
}

case class Path(isSolution: Boolean, acc: Int)

def solveSecondPart(file: File): Path = {
    val lines = fromFile(file).getLines().toList
    val visited = Array.fill(lines.size)(false)
    val n = lines.size

    val nop = """nop (\+|\-)([0-9]+)""".r
    val acc = """acc (\+|\-)([0-9]+)""".r
    val jmp = """jmp (\+|\-)([0-9]+)""".r

    def recSolve(i: Int, sol: Int, changeDone: Boolean): Path = {
        if (i == n) {
            Path(isSolution = true, acc = sol)
        } else if (visited(i)) {
            Path(isSolution = false, acc = -1)
        } else {
            visited(i) = true
            val op = lines(i)

            op match {
                case nop(sign, inc) => 
                    val increment = s"${sign}${inc}".toInt
                    val noChanges = recSolve(i + 1, sol, changeDone)

                    if (noChanges.isSolution)
                        noChanges
                    else if (!changeDone) {
                        val withChange = recSolve(i + increment, sol, changeDone = true)
                        withChange
                    } else
                        noChanges
                case jmp(sign, inc) => 
                    val increment = s"${sign}${inc}".toInt
                    val noChanges = recSolve(i + increment, sol, changeDone)

                    if (noChanges.isSolution)
                        noChanges
                    else if (!changeDone) {
                        val withChange = recSolve(i + 1, sol, changeDone = true)
                        withChange
                    } else
                        noChanges
                case acc(sign, inc) => 
                    recSolve(i + 1, sol + s"${sign}${inc}".toInt, changeDone)
            }
        }
    }

    recSolve(0, sol = 0, changeDone = false)
}

@main
def main(args: String*) = {
    if (args.size == 0) {
        System.err.println("Your script requires the first argument to be the input file")
        exit(-1)
    }
    val inputFile = new File(args(0))
    println(solveFirstPart(inputFile))
    println(solveSecondPart(inputFile).acc)
}