import scala.io.Source.fromFile
import java.io.File
import scala.util.matching.Regex
import scala.collection.mutable.{Map => MutableMap, Set => MutableSet}

def solveFirstPart(file: File): BigInt = {
    val input = fromFile(file).getLines().toArray.map(_.toInt)
    val sorted = input.sorted
    val jolts = Array(0) ++ sorted ++ Array(sorted.last + 3)

    def recSolve(i: Int, numOnes: Int, numThrees: Int): Int = {
        if (i == jolts.size) {
            numOnes * numThrees
        } else {
            val diff = jolts(i) - jolts(i - 1)

            if (diff == 1)
                recSolve(i + 1, numOnes + 1, numThrees)
            else if (diff == 3)
                recSolve(i + 1, numOnes, numThrees + 1)
            else
                recSolve(i + 1, numOnes, numThrees)
        }
    }
    
    recSolve(i = 1, numOnes = 0, numThrees = 0)
}

def solveSecondPart(file: File): BigInt = {
    val input = fromFile(file).getLines().toArray.map(_.toInt)
    val jolts = input.toSet
    val deviceJolt = jolts.max + 3
    val combinations = Array.fill[BigInt](deviceJolt + 1)(0)
    combinations(0) = 1

    def numCombinations(n: Int): BigInt = if (n >= 0) combinations(n) else 0

    def recSolve(n: Int): BigInt = {
        if (n > deviceJolt) {
            combinations(deviceJolt)
        } else {
            if (jolts.contains(n) || n == deviceJolt)
                combinations(n) = numCombinations(n - 1) + numCombinations(n - 2) + numCombinations(n - 3)
            
            recSolve(n + 1)
        }
    }
    
    recSolve(n = 1)
}

@main
def main(args: String*) = {
    if (args.size == 0) {
        System.err.println("Your script requires the first argument to be the input file")
        exit(-1)
    }
    val inputFile = new File(args(0))
    println(solveFirstPart(inputFile))
    println(solveSecondPart(inputFile))
}