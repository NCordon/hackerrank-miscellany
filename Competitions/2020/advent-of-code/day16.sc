import scala.io.Source.fromFile
import java.io.File
import scala.util.matching.Regex
import scala.collection.mutable.{Map => MutableMap}

case class FieldRule(name: String, a: Long, b: Long, c: Long, d: Long)

def solveFirstPart(file: File): Int = {
    val fieldRule = """([a-z ]+): ([0-9]+)-([0-9]+) or ([0-9]+)-([0-9]+)""".r
    val lines = fromFile(file).getLines().toArray
    
    val rules = lines.flatMap { case line =>
        line match {
            case fieldRule(name, a, b, c, d) => 
                Some(FieldRule(name, a.toInt, b.toInt, c.toInt, d.toInt))
            case _ =>
                None
        }
    }

    val nearbyTickets = lines.dropWhile(!_.startsWith("nearby tickets")).tail
    val errors = nearbyTickets.map(_.split(",").map(_.toInt)).flatMap { fields =>
        fields.filterNot { field =>
            rules.exists { case FieldRule(_, a, b, c, d) => 
                (a <= field && b >= field) || (c <= field && d >= field)
            }
        }
    }

    val errorRate = errors.sum
    errorRate
}

def simplifyRules(rules: Array[Set[FieldRule]]): Array[Set[FieldRule]] = {
    var explored = scala.collection.mutable.Set.empty[FieldRule]

    @annotation.tailrec
    def recSolve(rules: Array[Set[FieldRule]]): Array[Set[FieldRule]] = {
        rules.find(r => r.size == 1 && !explored.contains(r.head)) match {
            case Some(rule) =>
                explored.add(rule.head)

                val newRules = rules.map { current =>
                    if (current.size > 1)
                        current -- rule
                    else
                        current
                }
                recSolve(newRules)
            case None => rules
        }
    }

    recSolve(rules)
}

def solveSecondPart(file: File): Long = {
    val fieldRule = """([a-z ]+): ([0-9]+)-([0-9]+) or ([0-9]+)-([0-9]+)""".r
    val lines = fromFile(file).getLines().toList
    
    val rules = lines.flatMap { case line =>
        line match {
            case fieldRule(name, a, b, c, d) => 
                Some(FieldRule(name, a.toInt, b.toInt, c.toInt, d.toInt))
            case _ =>
                None
        }
    }.toSet

    val nearbyTickets = lines.dropWhile(!_.startsWith("nearby tickets")).tail.map(_.split(",").map(_.toInt))
    val validRulesPerField = Array.fill(nearbyTickets.head.size)(rules)

    // Preserve only valid tickets
    nearbyTickets.foreach { f => 
        val newRules = f.map { field =>
            rules.filter { case FieldRule(_, a, b, c, d) => 
                (a <= field && b >= field) || (c <= field && d >= field)
            }
        }
        
        if (newRules.forall(_.nonEmpty))
            validRulesPerField.zipWithIndex.map { case (value, index) => 
                validRulesPerField(index) = value.intersect(newRules(index))
            }
    }

    val myTicket = lines.dropWhile(!_.startsWith("your ticket"))(1).split(",")
    val filteredRules = simplifyRules(validRulesPerField)

    val departureValues = filteredRules.zipWithIndex.flatMap { case (rules, index) =>
        rules.headOption.collect { 
            case rule if rule.name.startsWith("departure") => {
                myTicket(index).toLong
            }
        }
    }

    departureValues.reduce(_ * _)
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