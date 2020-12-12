import scala.io.Source.fromFile
import java.io.File
import scala.util.matching.Regex
import math.{abs, signum}

case class Position(north: Int, east: Int, turns: Int)

def solveFirstPart(file: File): Int = {
    val init = Position(north = 0, east = 0, turns = 0)
    val N = "N([0-9]+)".r
    val S = "S([0-9]+)".r
    val E = "E([0-9]+)".r
    val W = "W([0-9]+)".r
    val L = "L([0-9]+)".r
    val R = "R([0-9]+)".r
    val F = "F([0-9]+)".r


    val finalPos = fromFile(file).getLines().foldLeft(init) { 
        case (Position(north, east, turns), move) =>
            move match {
                case N(units) => Position(north + units.toInt, east, turns)
                case S(units) => Position(north - units.toInt, east, turns)
                case E(units) => Position(north, east + units.toInt, turns)
                case W(units) => Position(north, east - units.toInt, turns)
                case L(units) => Position(north, east, (turns + units.toInt / 90) % 4)
                case R(units) => Position(north, east, (turns - units.toInt / 90) % 4)
                case F(units) => 
                    if (turns == 0) 
                        Position(north, east + units.toInt, turns)
                    else if (abs(turns) == 1) 
                        Position(north + signum(turns) * units.toInt, east, turns)
                    else if (abs(turns) == 2) 
                        Position(north, east - units.toInt, turns)
                    else
                        Position(north - signum(turns) * units.toInt, east, turns)
            }
    }

    abs(finalPos.north) + abs(finalPos.east)
}

case class Waypoint(north: Int, east: Int)
case class Boat(north: Int, east: Int)
case class Solution(boat: Boat, waypoint: Waypoint)

@annotation.tailrec
def rotateLeft(turns: Int, waypoint: Waypoint): Waypoint = {
    if (turns == 0) {
        waypoint
    } else {
        val north = waypoint.north
        val east = waypoint.east
        rotateLeft(turns - 1, Waypoint(east, -north))
    }
}

@annotation.tailrec
def rotateRight(turns: Int, waypoint: Waypoint): Waypoint = {
    if (turns == 0) {
        waypoint
    } else {
        val north = waypoint.north
        val east = waypoint.east
        rotateRight(turns - 1, Waypoint(-east, north))
    }
}

def solveSecondPart(file: File): Int = {
    val init = Solution(Boat(0, 0), Waypoint(1, 10))
    val N = "N([0-9]+)".r
    val S = "S([0-9]+)".r
    val E = "E([0-9]+)".r
    val W = "W([0-9]+)".r
    val L = "L([0-9]+)".r
    val R = "R([0-9]+)".r
    val F = "F([0-9]+)".r


    val finalPos = fromFile(file).getLines().foldLeft(init) { 
        case (Solution(Boat(n, e), Waypoint(x, y)), move) =>
            move match {
                case N(units) => Solution(Boat(n, e), Waypoint(x + units.toInt, y))
                case S(units) => Solution(Boat(n, e), Waypoint(x - units.toInt, y))
                case E(units) => Solution(Boat(n, e), Waypoint(x, y + units.toInt))
                case W(units) => Solution(Boat(n, e), Waypoint(x, y - units.toInt))
                case L(units) => 
                    val turns = (units.toInt / 90) % 4
                    val newWaypoint = rotateLeft(turns, Waypoint(x, y))
                    Solution(Boat(n, e), newWaypoint)
                case R(units) =>
                    val turns = (units.toInt / 90) % 4
                    val newWaypoint = rotateRight(turns, Waypoint(x, y))
                    Solution(Boat(n, e), newWaypoint)
                case F(units) => 
                    val u = units.toInt
                    Solution(Boat(n + u * x, e + u * y), Waypoint(x, y))
            }
    }

    abs(finalPos.boat.north) + abs(finalPos.boat.east)
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