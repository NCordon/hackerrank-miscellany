import scala.io.Source.fromFile
import java.io.File
import scala.util.matching.Regex
import scala.collection.mutable.{Map => MutableMap}

def solve(input: Array[Int], targetTurn: Int): Int = {
    val positions = MutableMap.empty[Int, Int]

    input.slice(0, input.size - 1).zipWithIndex.foreach { case (num, index) => 
        positions(num) = index + 1
    }

    @annotation.tailrec
    def solve(turn: Int, element: Int): Int = {
        if (turn == targetTurn)
            element
        else {
            val result = positions.get(element) match {
                case Some(previousTurn) => turn - previousTurn
                case None => 0
            }
            
            positions(element) = turn
            solve(turn + 1, result)
        }
    }

    solve(input.size, input.last)
}

@main
def main(args: String*) = {
    val input = Array(12,20,0,6,1,17,7)
    println(solve(input, targetTurn = 2020))
    // Is this the best solution?
    println(solve(input, targetTurn = 30000000))
}