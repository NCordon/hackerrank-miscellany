import scala.io.Source.fromFile
import java.io.File
import scala.util.matching.Regex

case class Pointer(numValid: Int, current: Set[String])

def extractFields(passportLine: String): Set[String] = {
    @annotation.tailrec
    def recSol(i: Int, prev: Int, sol: Set[String]): Set[String] = {
        if (i < passportLine.size) {
            if (passportLine(i) == ':') {
                val field = passportLine.slice(prev, i)
                recSol(i + 1, -1, sol + field)
            } else if (passportLine(i) == ' ') {
                recSol(i + 1, -1, sol)
            } else {
                if (prev == -1)
                    recSol(i + 1, i, sol)
                else
                    recSol(i + 1, prev, sol)
            }
        } else {
            sol
        }
    }

    recSol(0, -1, Set.empty)
}

def extractAndValidateFields(passportLine: String): Set[String] = {
    val byr = "byr:([0-9]{4})".r
    val iyr = "iyr:([0-9]{4})".r
    val eyr = "eyr:([0-9]{4})".r
    val hgtCm = "hgt:([0-9]{3})cm".r
    val hgtIn = "hgt:([0-9]{2})in".r
    val hcl = "hcl:#([0-9a-f]{6})".r
    val ecl = "ecl:(amb|blu|brn|gry|grn|hzl|oth)".r
    val pid = "pid:([0-9]{9})".r
    val cid = "cid:(.*)".r

    @annotation.tailrec
    def recSol(i: Int, prev: Int, sol: Set[String]): Set[String] = {
        if (i <= passportLine.size) {
            if (i == passportLine.size || passportLine(i) == ' ') {
                val field = passportLine.slice(prev, i)
                
                val validated = field match {
                    case byr(y) if (y.toInt >= 1920 && y.toInt <= 2002) => Set("byr")
                    case iyr(y) if (y.toInt >= 2010 && y.toInt <= 2020) => Set("iyr")
                    case eyr(y) if (y.toInt >= 2020 && y.toInt <= 2030) => Set("eyr")
                    case hgtCm(cm) if (cm.toInt >= 150 && cm.toInt <= 193) => Set("hgt")
                    case hgtIn(in) if (in.toInt >= 59 && in.toInt <= 76) => Set("hgt")
                    case hcl(_) => Set("hcl")
                    case ecl(_) => Set("ecl")
                    case pid(_) => Set("pid")
                    case cid(_) => Set("cid")
                    case _ => Set.empty[String]
                }
                recSol(i + 1, i + 1, sol ++ validated)
            } else {
                recSol(i + 1, prev, sol)
            }
        } else {
            sol
        }
    }

    recSol(0, 0, Set.empty)
}

def solution(file: File, validateFields: String => Set[String]): Unit = {
    val passport = Set("byr", "iyr", "eyr", "hgt", "hcl", "ecl", "pid")

    val result = fromFile(file).getLines().foldLeft(Pointer(0, Set.empty)) { case (sol, passportLine) =>
        val numValid = sol.numValid
        val current = sol.current
        val newCurrent = if (passportLine.isEmpty() || passportLine == "\n") Set.empty[String] else current ++ validateFields(passportLine)

        if (passport.diff(newCurrent).isEmpty)
            Pointer(numValid + 1, Set.empty)
        else
            Pointer(numValid, newCurrent)
    }

    println(result.numValid)
}

@main
def main(args: String*) = {
    if (args.size == 0) {
        System.err.println("Your script requires the first argument to be the input file")
        exit(-1)
    }
    val inputFile = new File(args(0))
    solution(inputFile, extractFields _)
    solution(inputFile, extractAndValidateFields _)
}
