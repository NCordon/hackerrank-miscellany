import scala.io.Source.fromFile
import java.io.File

case class Pointer(x: Int, y: Int, numTrees: BigInt, slope: Slope)
case class Slope(x: Int, y: Int)

def solution(file: File, slopes: List[Slope]): Unit = {
    val result = fromFile(file).getLines().foldLeft(slopes.map(Pointer(0, 0, 0, _))) { case (sols, cords) =>
        sols.map { sol =>
            val slope = sol.slope
            val y = sol.y % cords.size
            val x = sol.x
            val numTrees = sol.numTrees

            if (x % slope.x == 0) {
                if (cords(y) == '#')
                    Pointer(x + 1, y + slope.y, numTrees + 1, slope)
                else
                    Pointer(x + 1, y + slope.y, numTrees, slope)
            } else {
                Pointer(x + 1, y, numTrees, slope)
            }
        }
    }

    println(result.map(_.numTrees).reduce(_*_))
}

@main
def main(args: String*) = {
    if (args.size == 0) {
        System.err.println("Your script requires the first argument to be the input file")
        exit(-1)
    }
    val inputFile = new File(args(0))
    solution(inputFile, slopes = List(Slope(1, 3)))
    solution(inputFile, slopes = List(Slope(1, 1), Slope(1, 3), Slope(1, 5), Slope(1, 7), Slope(2, 1)))
}
