import scala.io.Source.fromFile
import java.io.File
import scala.collection.mutable.{Set => MutableSet}

// O(n) algorithmically, O(n) in space
def partOne(file: java.io.File): Unit = {
    val lines = fromFile(file).getLines()
    val alreadyFound = MutableSet.empty[Int]
  
    lines.foreach { line =>
        if (line.nonEmpty) {
            val value = line.toInt
            alreadyFound.add(value)
            val complementary = 2020 - value
            if (alreadyFound.contains(complementary)) {
                println(complementary * value)
                return
            }
        }
    }
}

// O(n^2) algorithmically, O(n) in space
def partTwo(file: File): Unit = {
    val lines = fromFile(file).getLines()
    val alreadyFound = MutableSet.empty[Int]
    
    lines.foreach { line =>
        if (line.nonEmpty) {
            val value = line.toInt
            alreadyFound.add(value)
        }
    }

    val allValues = alreadyFound.toArray

    for (i <- 0 to allValues.size - 1) {
        for (j <- 0 to allValues.size - 1) {
            val a = allValues(i)
            val b = allValues(j)
            val c = 2020 - a - b

            if (alreadyFound.contains(c)) {
                println(a * b * c)
                return
            }
        }
    }
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