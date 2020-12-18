import scala.io.Source.fromFile
import java.io.File
import scala.collection.mutable.ListBuffer

sealed trait Operation {
    def reduce(a: BigInt, b: BigInt): BigInt
}
case object Sum extends Operation {
    override def reduce(a: BigInt, b: BigInt): BigInt = a + b
}
case object Product extends Operation {
    override def reduce(a: BigInt, b: BigInt): BigInt = a * b
}

case class Result(value: BigInt, endParenthesis: Int)

def processLine(line: String): Result = {
    val nums = Seq('0', '1', '2', '3', '4', '5', '6', '7', '8', '9')

    def solve(index: Int): Result = {
        var acc: BigInt = 0
        var op: Operation = Sum
        var i = index

        while (i < line.size) {
            val c = line(i)

            if (nums.contains(c)) {
                acc = op.reduce(acc, c - '0')
            } else if (c == '+') {
                op = Sum
            } else if (c == '*') {
                op = Product
            } else if (c == '(') {
                val res = solve(i + 1)
                acc = op.reduce(acc, res.value)
                i = res.endParenthesis
            } else if (c == ')') {
                return Result(acc, i)
            }
            
            i +=1
        }
    
        Result(acc, i)
    }

    solve(0)
}

def processPrecedingSum(line: String): Result = {
    val nums = Seq('0', '1', '2', '3', '4', '5', '6', '7', '8', '9')

    def solve(index: Int): Result = {
        var toProcess = ListBuffer.empty[BigInt]
        var ops = ListBuffer.empty[Operation]
        var i = index
        var endParenthesis = false

        // Remove parentheses, leave only sums and products
        while (i < line.size && !endParenthesis) {
            val c = line(i)

            if (nums.contains(c)) {
                toProcess += c - '0'
            } else if (c == '+') {
                ops += Sum
            } else if (c == '*') {
                ops += Product
            } else if (c == '(') {
                val res = solve(i + 1)
                i = res.endParenthesis
                toProcess += res.value
            } else if (c == ')') {
                endParenthesis = true
                // Adjustment for next 
                i -= 1
            }
            
            i += 1
        }
    
        var products = ListBuffer.empty[BigInt]
        var current = toProcess(0)

        // Process only sums
        for (i <- 0 to (ops.size - 1)) {
            val op = ops(i)
            
            if (op == Sum) {
                current += toProcess(i + 1)
            } else {
                products += current
                current = toProcess(i + 1)
            }
        }

        // Adjust for the last element
        products += current

        // Process products
        Result(products.reduce(_ * _), i)
    }

    solve(0)
}

def solveFirstPart(file: File): BigInt = {
    fromFile(file).getLines().foldLeft(BigInt(0)) { case (sum, line) =>
        sum + processLine(line).value
    }
}

def solveSecondPart(file: File): BigInt = {
    fromFile(file).getLines().foldLeft(BigInt(0)) { case (sum, line) =>
        sum + processPrecedingSum(line).value
    }
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