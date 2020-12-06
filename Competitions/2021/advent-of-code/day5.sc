import scala.io.Source.fromFile
import java.io.File

case class Interval(l: Int, u: Int)

def seatId(boardingPass: String): Int = {
    val encodedRow = boardingPass.slice(0, 7)
    val encodedCol = boardingPass.slice(7, 10)

    def narrowInterval(interval: Interval, r: Char): Interval = {
        val l = interval.l
        val u = interval.u

        if (r == 'F' || r == 'L')
            Interval(l, (l + u) / 2)
        else
            Interval((l + u) / 2 + 1, u)
    }

    val row = encodedRow.foldLeft(Interval(0, 127))(narrowInterval _)
    val col = encodedCol.foldLeft(Interval(0, 7))(narrowInterval _)
    row.l * 8 + col.l
}

def allSeats(file: File): Set[Int] = {
    fromFile(file).getLines().map(seatId).toSet
}

@main
def main(args: String*) = {
    if (args.size == 0) {
        System.err.println("Your script requires the first argument to be the input file")
        exit(-1)
    }
    val inputFile = new File(args(0))
    val seats = allSeats(inputFile)
    
    // Solution to the first part
    println(seats.max)

    // All seats are in [0, (127 * 8 +7)] interval. Our seat is the only one missing
    // in the middle of the list missing. O(n) solution
    for (s <- seats.min to seats.max)
        if (!seats.contains(s))
            println(s)
}