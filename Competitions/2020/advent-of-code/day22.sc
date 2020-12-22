import scala.io.Source.fromFile
import java.io.File
import scala.collection.mutable.{ListBuffer, Set => MutableSet}

sealed trait Winner
case object FirstPlayer extends Winner
case object SecondPlayer extends Winner
case class GameResult(solution: Int, winner: Winner)
case class GameData(player1: List[Int], player2: List[Int])

def readInputData(file: File): GameData = {
    val player1 = ListBuffer.empty[Int]
    val player2 = ListBuffer.empty[Int]
    var isPlayer1 = true

    fromFile(file).getLines().foreach { line =>
        if (line.startsWith("Player 1")) {
            isPlayer1 = true
        } else if (line.startsWith("Player 2")) {
            isPlayer1 = false
        } else if (line.nonEmpty) {
            val current = line.toInt

            if (isPlayer1)
                player1.append(current)
            else
                player2.append(current)
        }
    }

    GameData(player1.toList, player2.toList)
}

def playGame(player1: ListBuffer[Int], player2: ListBuffer[Int], withRecursion: Boolean): GameResult = {
    val seen = MutableSet.empty[(List[Int], List[Int])]
    var winner: Option[Winner] = None

    while (!winner.isDefined) {
        if (player1.isEmpty) {
            winner = Some(SecondPlayer)
        } else if (player2.isEmpty) {
            winner = Some(FirstPlayer)
        } else if (withRecursion && seen.contains((player1.toList, player2.toList))) {
            winner = Some(FirstPlayer)
        } else {
            seen.add((player1.toList, player2.toList))
            val a = player1.head
            val b = player2.head
            player1.remove(0)
            player2.remove(0)

            val roundWinner = 
                if (withRecursion && player1.size >= a && player2.size >= b) {
                    val subgameResult = playGame(player1.take(a), player2.take(b), withRecursion)
                    subgameResult.winner
                } else if (a > b) 
                    FirstPlayer
                else
                    SecondPlayer
            
            if (roundWinner == FirstPlayer)
                player1.append(a, b)
            else
                player2.append(b, a)
        }
    }

    if (winner == Some(FirstPlayer)) 
        GameResult(processWinner(player1), FirstPlayer)
    else
        GameResult(processWinner(player2), SecondPlayer)
}

def processWinner(queue: ListBuffer[Int]): Int = {
    val size = queue.size
    queue.zipWithIndex.map { case (elem, index) =>
        elem * (size - index)
    }.sum
}

def solveFirstPart(file: File): Int = {
    val data = readInputData(file)
    val player1 = ListBuffer(data.player1:_*)
    val player2 = ListBuffer(data.player2:_*)
    playGame(player1, player2, withRecursion = false).solution
}

def solveSecondPart(file: File): Int = {
    val data = readInputData(file)
    val player1 = ListBuffer(data.player1:_*)
    val player2 = ListBuffer(data.player2:_*)
    playGame(player1, player2, withRecursion = true).solution
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
