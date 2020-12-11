import scala.io.Source.fromFile
import java.io.File
import scala.util.matching.Regex
import scala.collection.mutable.{Map => MutableMap, Set => MutableSet}

def solvePuzzle(file: File): Unit = {
    type CheckAdjacent = (Array[String], Int, Int, Int, Int) => Char

    val input = fromFile(file).getLines().toArray
    val numRows = input.size
    val numCols = input(0).size
    val occupied = '#'
    val empty = 'L'
    val floor = '.'

    def isEmpty(seat: Char) = seat == empty
    def isOcuppied(seat: Char) = seat == occupied
    def isFloor(seat: Char) = seat == floor
    def isValidRow(r: Int) = 0 <= r && r < numRows
    def isValidCol(c: Int) = 0 <= c && c < numCols
    val indexes = Seq((-1,0), (-1,1), (-1,-1), (0,1), (0,-1), (1,0), (1,-1), (1,1))

    // Visibility options
    @annotation.tailrec
    def firstVisibleSeat(seats: Array[String], i: Int, j: Int, r: Int, c: Int): Char = {
        val ii = i + r
        val jj = j + c

        if (isValidRow(ii) && isValidCol(jj)) {
            val seat = seats(ii)(jj)
            if (!isFloor(seat)) seat else (firstVisibleSeat(seats, ii, jj, r, c))
        } else {
            floor
        }
    }

    def moveDiagonally(seats: Array[String], i: Int, j: Int, r: Int, c: Int): Char = {
        val ii = i + r
        val jj = j + c
        if (isValidRow(ii) && isValidCol(jj)) seats(ii)(jj) else empty
    }

    // Mutate a row of seats based on adjacent ones
    def mutateRow(seats: Array[String], i: Int, row: String, checkAdjacent: CheckAdjacent, minOccupied: Int): String = {
        new String(
            row.zipWithIndex.map { case (seat, j) =>
                if (isEmpty(seat)) {
                    indexes.foldLeft(occupied) { case (res, (r, c)) =>
                        if (res == occupied) {
                            val visibleSeat = checkAdjacent(seats, i, j, r, c)
                            if (isOcuppied(visibleSeat)) empty else res
                        } else {
                            empty
                        }
                    }           
                } else if (isOcuppied(seat)) {
                    val numOccupied = indexes.foldLeft(0) { case (res, (r, c)) =>
                        val visibleSeat = checkAdjacent(seats, i, j, r, c)
                        if (isOcuppied(visibleSeat)) res + 1 else res
                    }

                    if (numOccupied >= minOccupied) empty else occupied
                } else {
                    seat
                }
            }.toArray
        )
    }
    
    // Main loop
    @annotation.tailrec
    def recSolve(seats: Array[String], checkAdjacent: CheckAdjacent, minOccupied: Int): Int = {
        val next = seats.zipWithIndex.map { case (row, i) =>
            mutateRow(seats, i, row, checkAdjacent, minOccupied)
        }
        if (seats.sameElements(next))
            seats.foldLeft(0) { case (count, row) => count + row.count(_ == '#') }
        else 
            recSolve(next, checkAdjacent, minOccupied)
    }

    println(s"Sol to first part: ${recSolve(input, moveDiagonally _, minOccupied = 4)}")
    println(s"Sol to second part: ${recSolve(input, firstVisibleSeat _, minOccupied = 5)}")
}

@main
def main(args: String*) = {
    if (args.size == 0) {
        System.err.println("Your script requires the first argument to be the input file")
        exit(-1)
    }
    val inputFile = new File(args(0))
    println(solvePuzzle(inputFile))
}