import scala.io.Source.fromFile
import java.io.File
import scala.util.matching.Regex
import scala.collection.mutable.{Map => MutableMap}

def applyMask(value: Long, mask: String): Long = {
    mask.zipWithIndex.foldLeft(value) { case (value, (current, i)) =>
        if (current == '1')
            value | (1L << (35 - i))
        else if (current == '0')
            value & (Long.MaxValue ^ (1L << (35 - i)))
        else
            value
    }
}

def solveFirstPart(file: File): Long = {
    val memory = MutableMap.empty[Long, Long]

    val mask = """mask = ([1|0|X]+)""".r
    val mem = """mem\[([0-9]+)\] = ([0-9]+)""".r
    var currentMask = ""

    fromFile(file).getLines().foreach { case line =>
        line match {
            case mask(m) => 
                currentMask = m
            case mem(addr, value) =>
                memory(addr.toLong) = applyMask(value.toLong, currentMask)
        }
    }

    memory.values.sum

}

/*
This decodes an address as the address we are currently trying to write with
the mask applied. For example if we have the following input:

mask = 000000000000000000000000000000X1001X
mem[42] = 100

the result would be:

mask   = 000000000000000000000000000000X1001X
addr   = 000000000000000000000000000000101010
result = 000000000000000000000000000000X1101X
*/

def decodeAddress(addr: Long, mask: String): String = {
    mask.zipWithIndex.foldLeft(mask) { case (currentMask, (bit, i)) =>
        if (bit == 'X') {
            currentMask
        } else if (bit == '1') {
            currentMask.updated(i, '1')
        } else { // bit == '0'
            val bit = addr & (1L << (35 - i))
            currentMask.updated(i, if (bit == 0) '0' else '1')
        }
    }
}

/* Compute the intersection between 2 masks 
   The intersection is guaranteed to be another single mask
*/
def intersectAddresses(a: String, b: String): Option[String] = {
    @annotation.tailrec
    def recSolve(i: Int, sol: String): Option[String] = {
        if (i == a.size)
            Some(sol)
        else {
            if (a(i) == b(i))
                recSolve(i + 1, sol.updated(i, b(i)))
            else if (a(i) == 'X' && b(i) != 'X')
                recSolve(i + 1, sol.updated(i, b(i)))
            else if (a(i) != 'X' && b(i) == 'X')
                recSolve(i + 1, sol.updated(i, a(i)))
            else
                None
        }
    }

    recSolve(0, a)
}

case class Address(addr: String, value: Long)

def solveSecondPart(file: File): BigInt = {
    val mask = """mask = ([1|0|X]+)""".r
    val mem = """mem\[([0-9]+)\] = ([0-9]+)""".r
    var currentMask = ""

    /* Idea behind this solution:
    We have A, B and C, sets of numbers we want to apply the mask to

    We process A, then B:
    A   -> nA
    B   -> nB
    A^B -> -nA

    We process C:
    A     -> nA
    B     -> nB
    A^B   -> -nA
    A^C   -> -nA
    B^C   -> -nB
    A^B^C -> +nA (because we had subtracted nA twice, in A^B and A^C)
    C     -> nC

    This is inclusion-exclusion principle https://en.wikipedia.org/wiki/Inclusion-exclusion_principle
    */
    val finalMemory = fromFile(file).getLines().foldLeft(List.empty[Address]) { case (memory, line) =>
        line match {
            case mask(m) => 
                currentMask = m
                memory
            case mem(aaddr, vvalue) =>
                val addr = aaddr.toLong
                val value = vvalue.toLong
                val newAddr = decodeAddress(addr, currentMask)
                
                val intersections = memory.flatMap { current =>
                    intersectAddresses(current.addr, newAddr).map(Address(_, -current.value))
                }

                (Address(newAddr, value) +: memory) ++ intersections
        }
    }

    finalMemory.foldLeft(BigInt(0)) { case (sol, current) =>
        val numUndefined = current.addr.count(_ == 'X')
        sol + (1 << numUndefined) * current.value
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