import scala.io.Source.fromFile
import java.io.File
import scala.util.matching.Regex
import scala.collection.mutable.{Map => MutableMap, Set => MutableSet}

def solveFirstPart(file: File): Set[String] = {
    val lines = fromFile(file).getLines().toList
    val bagRegex = """([0-9]+) (.*) (bag|bags|bag\.|bags\.)""".r
    // Directed graph
    // b is child for a (and the map contains b -> a in that case) if the bag b can be contained in a
    val graph = MutableMap.empty[String, Set[String]]

    lines.map { line => 
        val elems = line.split(" contain ")
        val container = elems(0).mkString.stripSuffix(" bags").stripSuffix(" bag")
        val contained = elems(1).split(", ")

        contained.foreach { bagLine =>
            bagLine match {
                case bagRegex(_, c, _) => 
                    graph += (c -> (graph.get(c).getOrElse(Set.empty[String]) + container))
                case _ => ()
            }
        }
    }

    // Traverse the graph back
    def recSolve(sol: Set[String], current: String): Set[String] = {
        graph.get(current).getOrElse(Set.empty).foldLeft(sol) { case (currentSol, child) =>
            if (currentSol.contains(child))
                currentSol
            else
                recSolve(currentSol + child, child)
        }
    }

    recSolve(Set.empty, "shiny gold")
}

def solveSecondPart(file: File): BigInt = {
    case class Contents(bag: String, num: Int)
    val lines = fromFile(file).getLines().toList
    val bagRegex = """([0-9]+) (.*) (bag|bags|bag\.|bags\.)""".r
    // Directed graph
    // b is child for a (and the map contains b -> a in that case) if the bag b can be contained in a
    val graph = MutableMap.empty[String, Set[Contents]]

    lines.map { line => 
        val elems = line.split(" contain ")
        val container = elems(0).mkString.stripSuffix(" bags").stripSuffix(" bag")
        val contained = elems(1).split(", ")

        contained.foreach { bagLine =>
            bagLine match {
                case bagRegex(numBags, c, _) => 
                    graph += (container -> (graph.get(container).getOrElse(Set.empty[Contents]) + Contents(c, numBags.toInt)))
                case _ => ()
            }
        }
    }

    // Traverse the graph
    def recSolve(sol: BigInt, current: String, multiplier: BigInt): BigInt = {
        graph.get(current).getOrElse(Set.empty).foldLeft(sol) { case (currentSol, contents) =>
            val newSol = currentSol + multiplier * contents.num
            recSolve(newSol, contents.bag, multiplier * contents.num)
        }
    }

    recSolve(0, "shiny gold", multiplier = 1)
}

@main
def main(args: String*) = {
    if (args.size == 0) {
        System.err.println("Your script requires the first argument to be the input file")
        exit(-1)
    }
    val inputFile = new File(args(0))
    println(solveFirstPart(inputFile).size)
    println(solveSecondPart(inputFile))
}