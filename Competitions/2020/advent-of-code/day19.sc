// Needs two input files
// Call like: ammonite ./day19.sc ./inputs/day19_rules ./inputs/day19_examples
//   The first file contains only the rules, the second one the possible words in the language
//   where day19_rules includes the modified rules:
//   8: 42 | 42 8
//   11: 42 31 | 42 11 31
import scala.io.Source.fromFile
import java.io.File
import scala.util.matching.Regex

val node  = """([0-9]+): (.*)""".r
val leave = """([0-9]+): \"(.)\"""".r 
sealed trait Rule
case class SimpleRule(rules: List[Int]) extends Rule
case class EitherRule(either: Set[SimpleRule]) extends Rule
case class Leave(value: String) extends Rule

// Read the input rules
def parseRules(rulesFile: File): Map[Int, Rule] = {
    fromFile(rulesFile).getLines().foldLeft(Map.empty[Int, Rule]) { case (map, line) =>
        line match {
            case leave(num, value) =>
                map + (num.toInt -> Leave(value))
            case node(num, rules) =>
                if (rules.contains('|')) {
                    map + (num.toInt -> EitherRule(rules.split('|').map(a => SimpleRule(a.split(' ').filterNot(_.isEmpty).map(_.toInt).toList)).toSet))
                } else {
                    map + (num.toInt -> SimpleRule(rules.split(' ').map(_.toInt).toList))
                }
        }
    }
}

var x = Set.empty[String]
var y = Set.empty[String]
val partialSolutions = scala.collection.mutable.Map.empty[Int, Set[String]]

def fillPartialSolutions(rules: Map[Int, Rule]): Unit = {
    def solveSimpleRule(simpleRule: SimpleRule): Set[String] = {
        val indexes = simpleRule.rules
        indexes.map(solve).reduce { (a, b) => a.flatMap(avalue => b.map(bvalue => avalue + bvalue)) }
    }

    def solve(index: Int): Set[String] = {
        if (!partialSolutions.contains(index)) {
            val sol: Set[String] = 
                rules.get(index) match {
                    case Some(Leave(value)) => Set(value)
                    case Some(s : SimpleRule) => 
                        solveSimpleRule(s)
                    case Some(EitherRule(simpleRules)) =>
                        if (index == 8) {
                            x = solve(42)
                            Set("x")
                        } else if (index == 11) {
                            y = solve(31)
                            Set("xy")
                        } else {
                            simpleRules.flatMap(solveSimpleRule)
                        }
                    case None => Set.empty
                }

            partialSolutions(index) = sol
            sol
        } else {
            partialSolutions(index)
        }
    }

    solve(0)
}

case class MatchDistribution(x: Int, y: Int)

def inLanguage(w: String, rls: List[Set[String]], recursive: Boolean): Boolean = {

    def recInLanguage(word: String, rules: List[Set[String]], dist: MatchDistribution): Boolean =
        (word, rules) match {
            case ("", _)                => rules.isEmpty && dist.x > dist.y
            case (_, List())            => word.isEmpty && dist.x > dist.y
            case (_, rule::restOfRules) =>
                val yMatch = restOfRules.isEmpty
                val nextDist = if (yMatch) dist.copy(y = dist.y + 1) else dist.copy(x = dist.x + 1)

                rule.exists { prefix =>
                    word.startsWith(prefix) && {
                        if (recursive) 
                            recInLanguage(word.stripPrefix(prefix), rules, nextDist) || 
                            recInLanguage(word.stripPrefix(prefix), restOfRules, nextDist)
                        else 
                            recInLanguage(word.stripPrefix(prefix), restOfRules, nextDist)
                    }
                }
        }

    recInLanguage(w, rls, MatchDistribution(0, 0))
}


def solve(rulesFile: File, examplesFile: File): Unit = {
    val rules = parseRules(rulesFile)
    val examples = fromFile(examplesFile).getLines().toList
    // println(rules)
    
    fillPartialSolutions(rules)
    for (recursiveGrammar <- Seq(false, true)) {
        // For the first part solutions are of the form x{2}y{1}
        // For the second part, they are of the form x{N + M}y{N} where N >= 1 is a fixed number
        val sol = examples.foldLeft(0) { case (sum, word) =>
            if (inLanguage(word, List(x, x, y), recursiveGrammar))
                sum + 1
            else
                sum
        }

        println(sol)
    }
}

@main
def main(args: String*) = {
    if (args.size == 0) {
        System.err.println("Your script requires the first argument to be the input file")
        exit(-1)
    }
    val rulesFile = new File(args(0))
    val examplesFile = new File(args(1))
    solve(rulesFile, examplesFile)
}