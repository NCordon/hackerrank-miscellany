import scala.io.Source.fromFile
import scala.util.matching.Regex
import java.io.File

def partOne(file: File): Unit = {
    val regex: Regex = "([0-9]+)-([0-9]+) ([a-z]{1}): (.*)".r
    
    val result = fromFile(file).getLines().foldLeft(0) { case (acc, line) =>
        val regex(lStr, uStr, letterStr, pass) = line
        val l = lStr.toInt
        val u = uStr.toInt
        val letter = letterStr.head

        val count = pass.count(_ == letter)
        if (count >= l && count <= u) acc + 1 else acc
    }

    println(result)
}

def partTwo(file: File): Unit = {
    val regex: Regex = "([0-9]+)-([0-9]+) ([a-z]{1}): (.*)".r
    
    val result = fromFile(file).getLines().foldLeft(0) { case (acc, line) =>
        val regex(lStr, uStr, letterStr, pass) = line
        val i = lStr.toInt - 1
        val j = uStr.toInt - 1
        val letter = letterStr.head

        if (pass(i) == letter ^ pass(j) == letter) acc + 1 else acc
    }

    println(result)
}

@main
def main(args: String*) = {
    if (args.size == 0) {
        System.err.println("Your script requires the first argument to be the input file")
        exit(-1)
    }
    val inputFile = new File(args(0))
    partOne(inputFile)
    partTwo(inputFile)
}
