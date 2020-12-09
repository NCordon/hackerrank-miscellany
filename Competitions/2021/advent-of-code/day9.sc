import scala.io.Source.fromFile
import java.io.File
import scala.util.matching.Regex
import scala.collection.mutable.{Map => MutableMap, Set => MutableSet}

def solveFirstPart(file: File): BigInt = {
    val nums = fromFile(file).getLines().toArray.map(BigInt.apply)
    val delta = 25

    def recSolve(n: Int): BigInt = {
        val numsBefore = nums.slice(n - delta, n).toSet
        val target = nums(n)

        val hasSolution = numsBefore.foldLeft(false) { case (isSol, current) =>
            if (isSol)
                isSol
            else {
                val complementary = target - current
                complementary != current && numsBefore.contains(complementary)
            }
        }

        if (!hasSolution) 
            target
        else
            recSolve(n + 1)
    }

    recSolve(delta)
}

def solveSecondPart(file: File, target: BigInt): BigInt = {
    val nums = fromFile(file).getLines().toArray.map(BigInt.apply)

    @annotation.tailrec
    def recSolve(i: Int, j: Int, sum: BigInt): BigInt = {
        if (sum == target) {
            val interval = nums.slice(i, j)
            interval.max + interval.min
        } else if (sum < target) {
            recSolve(i, j + 1, sum + nums(j))
        } else {
            recSolve(i + 1, j, sum - nums(i))
        }
    }

    recSolve(0, 0, 0)
}

@main
def main(args: String*) = {
    if (args.size == 0) {
        System.err.println("Your script requires the first argument to be the input file")
        exit(-1)
    }
    val inputFile = new File(args(0))
    val firstPartSol = solveFirstPart(inputFile)
    val secondPartSol = solveSecondPart(inputFile, firstPartSol)
    println(firstPartSol)
    println(secondPartSol)
}