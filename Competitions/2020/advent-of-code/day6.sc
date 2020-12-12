import scala.io.Source.fromFile
import java.io.File

def answersSum(file: File, condition: Set[Char] => Set[Char] => Set[Char]): Int = {
    val lines = fromFile(file).getLines().toList

    @annotation.tailrec
    def recSolve(i: Int, found: Set[Char], sol: Int, newGroup: Boolean = false): Int = {
        if (i < lines.size) {
            val current = lines(i).toSet

            if (current.isEmpty)
                recSolve(i + 1, Set.empty, sol + found.size, newGroup = true)
            // Adjust end of file
            else if (i == (lines.size - 1))
                recSolve(i + 1, Set.empty, sol + condition(found)(current).size)
            else if (newGroup)
                recSolve(i + 1, current, sol)
            else
                recSolve(i + 1, condition(found)(current), sol)
        } else {
            sol
        }
    }
    
    recSolve(0, Set.empty, 0, newGroup = true)
}

@main
def main(args: String*) = {
    if (args.size == 0) {
        System.err.println("Your script requires the first argument to be the input file")
        exit(-1)
    }
    val inputFile = new File(args(0))
    val anyoneYes = answersSum(inputFile, condition = a => b => a ++ b)
    val allYes = answersSum(inputFile, condition = a => b => a intersect b)

    println(anyoneYes)
    println(allYes)
}