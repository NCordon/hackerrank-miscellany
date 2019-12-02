package collection

import org.scalatest.prop.TableDrivenPropertyChecks._
import collection._
import org.scalatest._

class LinkedHashMapTest extends org.scalatest.FunSuite with Matchers {

  val mapTests =
    Table(
      ("map", "toAdd", "toRemove", "expected"),
      ( LinkedHashMap(1 -> 1, 2 -> 2),
        Seq((4 -> 5), (5 -> 6)),
        Seq(1, 2, 3, 4, 5),
        LinkedHashMap[Int, Int]()
      ),
      ( LinkedHashMap(1 -> 1, 2 -> 2),
        Seq(),
        Seq(1, 2, 3, 4, 5),
        LinkedHashMap[Int, Int]()
      ),
      ( LinkedHashMap[Int, Int](),
        Seq(1 -> 2, 2 -> 3),
        Seq(),
        LinkedHashMap[Int, Int](1 -> 2, 2 -> 3)
      )
    )

  test("map tests") {
    forAll (mapTests) { (map, toAdd, toRemove, expected) =>
      val withAdditions = toAdd.foldLeft(map) { case (current, (a, b))  =>
        current.add(a, b)
      }

      val withRemoval = toRemove.foldLeft(withAdditions) { case (current, a) =>
        current.remove(a)
      }

      withRemoval shouldBe expected
    }
  }

}
