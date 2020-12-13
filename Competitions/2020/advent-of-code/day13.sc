import scala.io.Source.fromFile
import java.io.File
import scala.util.matching.Regex

def solveFirstPart(file: File): Int = {
    val input = fromFile(file).getLines().toArray

    val departure = input(0).toInt
    val frequencies = input(1).split(",").filter(_ != "x").map(_.toInt)

    var solution = 0
    var waitingTime = Int.MaxValue

    for (freq <- frequencies) {
        val current = (freq - (departure % freq)) % freq

        if (waitingTime >= current) {
            waitingTime = current
            solution = waitingTime * freq
        }
    }

    solution
}

case class Equation(coeff: Long, rest: Long)

def findInverse(b: Long, a: Long) = {
    @annotation.tailrec
    def recSolve(current: Long): Long = {
        if ((b * current) % a == 1)
            current
        else
            recSolve(current + 1)
    }

    recSolve(2)
}

def simplifyEquations(aEq: Equation, bEq: Equation): Equation = {
    val a = aEq.coeff
    val b = bEq.coeff

    if (a > b)
        simplifyEquations(bEq, aEq)
    else {
        // a < b
        val bInv = findInverse(b, a)
        val p = aEq.rest
        val q = bEq.rest
        val r = ((bInv * (p - q)) % a + a) % a
        val c = a * b
        val rr = ((b * r + q) % c + c) % c
        Equation(c, rr)
    }
}

def solveSecondtPart(file: File): Long = {
    val input = fromFile(file).getLines().toArray
    val eqs = input(1).split(",").zipWithIndex.filter(_._1 != "x").map { 
        case (num, index) => 
            val coeff = num.toInt
            Equation(coeff, coeff - index)
    }
    
    val result = eqs.reduce(simplifyEquations _)
    result.rest
}

@main
def main(args: String*) = {
    if (args.size == 0) {
        System.err.println("Your script requires the first argument to be the input file")
        exit(-1)
    }
    val inputFile = new File(args(0))
    println(solveFirstPart(inputFile))
    println(solveSecondtPart(inputFile))
}