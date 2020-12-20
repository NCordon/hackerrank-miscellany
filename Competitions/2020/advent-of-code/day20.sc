// :( spaghetti code
import scala.io.Source.fromFile
import scala.collection.mutable.ListBuffer
import java.io.File

case class Tile(num: Int, content: List[String], borders: TileBorders)
case class TileBorders(upper: String, right: String, bottom: String, left: String)

final val monster = List(
    "                  # ",
    "#    ##    ##    ###",
    " #  #  #  #  #  #   "
)

final val sharpsInMonster = monster.foldLeft(0) { 
    case (res, row) => res + row.count(_ == '#') 
}

def extractBorders(tile: List[String]): TileBorders = {
    TileBorders(
        tile.head,
        tile.map(_.last).mkString,
        tile.last.reverse,
        tile.map(_.head).mkString.reverse
    )
}

def computeBorderTiles(tiles: List[Tile]): List[Tile] = {
    val borders = tiles.map(_.borders).map(b => Set(b.upper, b.right, b.bottom, b.left))

    // Border tiles are the ones that have 2 free sides (don't fit other tiles)
    val borderTiles = borders.zipWithIndex.flatMap { case (b, i) =>
        // rest of tiles
        val rest = borders.take(i) ++ borders.drop(i + 1)
        val restAndRotated = rest.flatMap { b =>
            b ++ b.map(_.reverse)
        }.toSet

        val numMatches = b.size - b.diff(restAndRotated).size
        if (numMatches == 2) Some(tiles(i)) else None
    }
    
    borderTiles
}

def getTiles(lines: Iterator[String]): List[Tile] = {
    val tiles = ListBuffer.empty[Tile]
    var currentTile = ListBuffer.empty[String]
    var tileNum = 0

    lines.foreach { line =>
        if (line.nonEmpty) {
            if (line.startsWith("Tile ")) {
                tileNum = line.stripPrefix("Tile ").stripSuffix(":").toInt
                currentTile = ListBuffer.empty
            } else {
                currentTile += line
                if (currentTile.size == 10) {
                    val tile = currentTile.toList
                    tiles += Tile(tileNum, tile, extractBorders(tile))
                }
            }
        }
    }

    tiles.toList
}

def borderMatches(target: String)(tile: Tile): Boolean = {
    def matches(border: String, target: String) = 
       border == target || border.reverse == target

    val borders = tile.borders
    
    matches(borders.upper, target) || 
    matches(borders.right, target) ||
    matches(borders.bottom, target) ||
    matches(borders.left, target)
}

def flipContentTile(content: List[String]) = {
    content.reverse
}

def flipTile(tile: Tile): Tile = {
    val flippedContent = flipContentTile(tile.content)
    Tile(tile.num, flippedContent, extractBorders(flippedContent))
}

def rotateContentTile(content: List[String]) = {
    List.tabulate(content.head.size) { i =>
        content.map(_(i)).mkString
    }.map(_.reverse)
}

def rotateTile(tile: Tile): Tile = {
    val rotatedContent = rotateContentTile(tile.content)
    Tile(tile.num, rotatedContent, extractBorders(rotatedContent))
}

def computeGrid(tls: List[Tile], borderTiles: List[Tile]): Array[Array[Tile]] = {
    var upperTopTile = borderTiles.head
    var tiles = tls.toSet
    val restOfBorders = (tiles - upperTopTile)
        .map(_.borders)
        .map(b => Set(b.upper, b.right, b.bottom, b.left))
        .flatMap(bs => bs ++ bs.map(_.reverse))
    
    while (restOfBorders.contains(upperTopTile.borders.upper) || restOfBorders.contains(upperTopTile.borders.left)) {
        upperTopTile = rotateTile(upperTopTile)
    }

    // eugh :(
    val width = math.sqrt(tiles.size).toInt
    val grid = Array.fill(width)(Array.fill[Tile](width)(null))

    // We know for each border there are at most two tiles that match it
    def searchTile(prevjTile: Option[Tile], previTile: Option[Tile]): Tile = {
        val prevjBorder = prevjTile.map(_.borders.right)
        val previBorder = previTile.map(_.borders.bottom)

        (prevjBorder, previBorder) match {
            case (None, None) =>
                upperTopTile
            case (_, Some(target)) =>
                val tile = tiles.find(borderMatches(target))
                // eugh :(
                tile.head
            case (Some(target), _) =>
                val tile = tiles.find(borderMatches(target))
                // eugh :(
                tile.head
        }
    }

    def adjustTile(tile: Tile, prevjTile: Option[Tile], previTile: Option[Tile]): Tile = {
        val prevjBorder = prevjTile.map(_.borders.right)
        val previBorder = previTile.map(_.borders.bottom)
        var t = tile

        (prevjBorder, previBorder) match {
            case (None, None) =>
                tile // upperTopTile
            case (_, Some(target)) =>
                while (t.borders.upper != target.reverse) {
                    if (t.borders.upper == target) {
                        t = flipTile(t)
                    } else {
                        t = rotateTile(t)
                    }
                }

                t
            case (Some(target), _) =>
                while (t.borders.left != target.reverse) {
                    if (t.borders.left == target) {
                        t = flipTile(t)
                    } else {
                        t = rotateTile(t)
                    }
                }
                t
        }
    }
    
    def fillGrid(i: Int, j: Int): Unit = {
        if (j >= width) {
            fillGrid(i + 1, 0)
        } else if (i < width) {
            val previ = i - 1
            val prevj = j - 1

            val prevjBorder = if (prevj >= 0) Some(grid(i)(prevj)) else None
            val previBorder = if (previ >= 0) Some(grid(previ)(j)) else None

            val tile = searchTile(prevjBorder, previBorder)
            tiles = tiles - tile
            grid(i)(j) = adjustTile(tile, prevjBorder, previBorder)
            // fill same row, next column
            fillGrid(i, j + 1)
        }
    }

    fillGrid(0, 0)
    grid
}

def removeBorders(tile: Tile): Tile = {
    val content = tile.content
    val modifiedContent = content.drop(1).dropRight(1).map { row =>
        row.drop(1).dropRight(1)
    }
    Tile(tile.num, modifiedContent, extractBorders(modifiedContent))
}

def computeNumMonsters(grid: List[String]): Int = {
    val auxCoords = monster.zipWithIndex.flatMap { case (row, i) =>
        row.zipWithIndex.flatMap { case (elem, j) =>
            if (elem == '#') Some((i, j)) else None
        }
    }
    val relative = auxCoords.head
    // Make the monster coordinates relative to a sharp
    val monsterCoords = auxCoords
        .map { case (a, b) => (a - relative._1, b - relative._2) }
        .toSet

    val allSharps = grid.zipWithIndex.flatMap { case (row, i) =>
        row.zipWithIndex.flatMap { case (elem, j) =>
            if (elem == '#') Some((i, j)) else None
        }
    }.toSet

    var numMonsters = 0

    allSharps.foreach { case (a, b) =>
        val targetCoords = monsterCoords.map { case (c, d) =>
            (a + c, b + d)
        }

        if (targetCoords.forall(coord => allSharps.contains(coord))) {
            numMonsters += 1
        }
    }

    numMonsters
}

def adjustAndComputeNumMonsters(g: List[String]): Int = {
    var rotations = 0
    var grid = g
    var numMonsters = computeNumMonsters(grid)

    while (numMonsters == 0) {
        if (rotations < 4) {
            grid = rotateContentTile(grid)
            rotations += 1
        } else {
            grid = flipContentTile(grid)
            rotations = 0
        }
        numMonsters = computeNumMonsters(grid)
    }

    numMonsters
}

def solve(file: File): Unit = {
    val tiles = getTiles(fromFile(file).getLines())
    val borderTiles = computeBorderTiles(tiles)
    val grid = computeGrid(tiles, borderTiles)
    var gluedGrid = grid.flatMap{ row =>
        val tiles = row.map(removeBorders)
        val content = tiles.map(_.content).reduce { (a, b) =>
            a.zip(b).map { case (aRow, bRow) => aRow ++ bRow}
        }
        content
    }.toList

    var numMonsters = adjustAndComputeNumMonsters(gluedGrid)
    val totalSharps = gluedGrid.foldLeft(0) { case (res, row) =>
        res + row.count(_ == '#')
    }

    // Solution to the first part
    // Multiply border tiles identifiers
    println(borderTiles.foldLeft(1L) { case (res, current) => res * current.num })
    // Solution to the second part
    println(totalSharps - numMonsters * sharpsInMonster)
}

@main
def main(args: String*) = {
    if (args.size == 0) {
        System.err.println("Your script requires the first argument to be the input file")
        exit(-1)
    }
    val inputFile = new File(args(0))
    solve(inputFile)
}
