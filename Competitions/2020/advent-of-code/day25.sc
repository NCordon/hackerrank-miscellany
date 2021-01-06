import scala.io.Source.fromFile
import scala.collection.mutable.{Set => MutableSet, Map => MutableMap}
import java.io.File

def computeLoopSize(target: Long): Long = {
    @annotation.tailrec
    def solve(current: Long, exp: Long): Long = {
        if (current == target)
            exp
        else {
            solve(current * 7L % 20201227, exp + 1)
        }
    }

    solve(current = 1, exp = 0)
}

def expMod(num: Long, exp: Long): Long = {
    @annotation.tailrec
    def solve(result: Long, currentExp: Long): Long = {
        if (currentExp == exp)
            result
        else {
            solve(result * num % 20201227, currentExp + 1)
        }
    }

    solve(result = 1, currentExp = 0)
}

def solveFirstPart(list: List[Long]): Long = {
    list match {
        case List(x, y) =>
            val loopSize = computeLoopSize(x)
            expMod(y, loopSize)
    }
}

@main
def main(args: String*) = {
    println(solveFirstPart(List(16915772, 18447943)))
}
