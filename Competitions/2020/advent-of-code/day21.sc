import scala.io.Source.fromFile
import java.io.File
import scala.collection.mutable.{Set => MutableSet, Map => MutableMap}
import scala.collection.mutable.ListBuffer
import scala.collection.immutable.Set.Set1

def solve(file: File): Unit = {
    val allIngredients = ListBuffer.empty[String]
    val allAllergens = MutableMap.empty[String, Set[String]]
    
    fromFile(file).getLines().foreach { line =>
        val Array(ingredientsStr, allergensStr) = line.stripSuffix(")").split("""( \(contains )""")

        val ingredients = ingredientsStr.split(" ").toSet
        val allergens   = allergensStr.split("(, )")
        allIngredients ++= ingredients

        allergens.foreach { allergen =>
            allAllergens(allergen) = allAllergens
                .get(allergen)
                .fold(ingredients) { current => current.intersect(ingredients) }
        }
    }

    val haveAllergenes = allAllergens.values.flatten.toSet
    val doNotContainAllergens = allIngredients.filterNot(haveAllergenes.contains)

    // Solution to the first part
    println(doNotContainAllergens.size)
    // Solution to the second part
    println(resolveAllergens(allAllergens.toMap).mkString(","))
}

def resolveAllergens(allergens: Map[String, Set[String]]): Array[String] = {
    val withOne = MutableMap.empty[String, String]
    val allAllergens = MutableMap.apply(allergens.seq.toSeq:_*)

    while (allAllergens.nonEmpty) {
        val toRemove = MutableSet.empty[String]

        allAllergens.foreach { case (k, vs) =>
            vs.diff(withOne.values.toSet).toSeq match {
                case Seq(v) => 
                    withOne += (k -> v)
                    toRemove.add(k)
                case _ => ()
            }
        }
        
        toRemove.foreach(allAllergens.remove)
    }

    withOne.toArray
        .sortBy { case (allergen, _) => allergen }
        .map { case (_, ingredient) => ingredient }
}

@main
def main(args: String*) = {
    if (args.size == 0) {
        System.err.println("Your script requires the first argument to be the input file")
        exit(-1)
    }
    val inputFile = new File(args(0))
    solve(inputFile)
}
