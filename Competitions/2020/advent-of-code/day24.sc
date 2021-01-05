import scala.io.Source.fromFile
import scala.collection.mutable.{Set => MutableSet, Map => MutableMap}
import java.io.File

case class Tile(sw: Int, se: Int, nw: Int, ne: Int, w: Int, e: Int)

def parseTiles(lines: List[String]): List[Tile] = {
    @annotation.tailrec
    def parseTile(result: Tile, i: Int, line: String): Tile = {
        if (i >= line.size)
            result
        else {
            val (nextTile, nexti) = {
                if (line(i) == 's' && line(i + 1) == 'e')
                    (result.copy(se = result.se + 1), i + 2)
                else if (line(i) == 's' && line(i + 1) == 'w')
                    (result.copy(sw = result.sw + 1), i + 2)
                else if (line(i) == 'n' && line(i + 1) == 'e')
                    (result.copy(ne = result.ne + 1), i + 2)
                else if (line(i) == 'n' && line(i + 1) == 'w')
                    (result.copy(nw = result.nw + 1), i + 2)
                else if (line(i) == 'e')
                    (result.copy(e = result.e + 1), i + 1)
                else // line(i) == 'w'
                    (result.copy(w = result.w + 1), i + 1)
            }

            parseTile(nextTile, nexti, line)
        }
    }

    val initTile = Tile(0, 0, 0, 0, 0, 0)
    val tiles = lines.map { line =>
        parseTile(initTile, 0, line)
    }

    tiles
}

/* For the first part, flip-flop the black tiles, 
   keeping relative coordinates */
def processTiles(tiles: List[Tile], secondPart: Boolean): Int = {
    val explored = MutableSet.empty[(Int, Int)]

    @annotation.tailrec
    def processTile(tile: Tile, x: Int, y: Int): Unit = {
        tile match {
            case Tile(sw, se, nw, ne, w, e) =>
                if (sw != 0)
                    processTile(Tile(0, se, nw, ne, w, e), x, y - sw)
                else if (se != 0)
                    processTile(Tile(0, 0, nw, ne, w, e), x + se, y - se)
                else if (nw != 0)
                    processTile(Tile(0, 0, 0, ne, w, e), x - nw, y + nw)
                else if (ne != 0)
                    processTile(Tile(0, 0, 0, 0, w, e), x, y + ne)
                else if (w != 0)
                    processTile(Tile(0, 0, 0, 0, 0, e), x - w, y)
                else if (e != 0)
                    processTile(Tile(0, 0, 0, 0, 0, 0), x + e, y)
                else {
                    if (explored.contains((x, y)))
                        explored.remove((x, y))
                    else
                        explored.add((x, y))
                }
        }
    }

    tiles.foreach { tile =>
        processTile(tile, x = 0, y = 0)
    }

    if (secondPart) {
        evolveDays(explored.toSet, numDays = 100)
    } else {
        explored.size
    }
}

/* For the second part, keep the number of black adjacent tiles, 
   distinguishing between white and black tiles */
def evolveDays(blackTiles: Set[(Int, Int)], numDays: Int): Int = {

    @annotation.tailrec
    def evolveDay(day: Int, blackTiles: Set[(Int, Int)]): Int = {
        if (day >= numDays) {
            blackTiles.size
        } else {
            val blackAdjacentToBlack = MutableMap.empty[(Int, Int), Int]
                .withDefaultValue(0)
            val blackAdjacentToWhite = MutableMap.empty[(Int, Int), Int]
                .withDefaultValue(0)
            val initMove: Rotation = E

            def markAdjacent(x: Int, y: Int): Unit = {
                @annotation.tailrec
                def recNumBlack(move: Rotation): Unit = {
                    val (a,b) = makeMove(move, x, y)
                    if (blackTiles.contains((a, b)))
                        blackAdjacentToBlack((a, b)) += 1
                    else
                        blackAdjacentToWhite((a, b)) += 1
                    
                    val nextMove = rotateRight(move)
                    if (nextMove != initMove)
                        recNumBlack(nextMove)
                }

                recNumBlack(initMove)
            }
            
            blackTiles.foreach(current => markAdjacent(current._1, current._2))

            val nextBlackTiles = 
                blackAdjacentToBlack.filter { case (_, numBlackAdjacent) => 
                    numBlackAdjacent == 1 || 
                    numBlackAdjacent == 2 
                }.keySet.toSet ++
                blackAdjacentToWhite.filter { case (_, numBlackAdjacent) => 
                    numBlackAdjacent == 2 
                }.keySet.toSet

            evolveDay(day + 1, nextBlackTiles)
        }
    }

    evolveDay(0, blackTiles)
}

sealed trait Rotation
case object E  extends Rotation
case object W  extends Rotation
case object NW extends Rotation
case object SW extends Rotation
case object NE extends Rotation
case object SE extends Rotation

def makeMove(move: Rotation, x: Int, y: Int): (Int, Int) =
    move match {
        case W => (x - 1, y)
        case NW => (x - 1, y + 1)
        case NE => (x, y + 1)
        case E => (x + 1, y)
        case SE => (x + 1, y - 1)
        case SW => (x, y - 1)
    }

def rotateRight(rot: Rotation): Rotation =
    rot match {
        case W => NW
        case NW => NE
        case NE => E
        case E => SE
        case SE => SW
        case SW => W
    }

def solveFirstPart(file: File): Int = {
    val lines = fromFile(file).getLines().toList
    val tiles = parseTiles(lines)
    processTiles(tiles, secondPart = false)
}

def solveSecondPart(file: File): Int = {
    val lines = fromFile(file).getLines().toList
    val tiles = parseTiles(lines)
    processTiles(tiles, secondPart = true)
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
