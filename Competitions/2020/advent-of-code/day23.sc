import scala.collection.mutable.{Map => MutableMap}
import scala.collection.mutable.ListBuffer

case class Node(val value: Int, var next: Node)

class CircularList {
    val nodes = MutableMap.empty[Int, Node]
    var firstNode: Node = null
    var lastNode: Node = null
    var max: Int = Int.MinValue
    var min: Int = Int.MaxValue

    def getNode(node: Int): Node =
        nodes(node)

    def addNode(node: Int): Unit = {
        if (firstNode == null) {
            firstNode = Node(node, null)
            firstNode.next = firstNode
            lastNode = firstNode
            nodes(node) = firstNode
        } else {
            val newNode = Node(node, firstNode)
            lastNode.next = newNode
            lastNode = newNode
            nodes(node) = newNode
        }

        min = math.min(min, node)
        max = math.max(max, node)
    }

    def getNextNodes(node: Node, numNext: Int): List[Node] = {
        var num = numNext
        var current = node

        val (result, _) = (1 to numNext).foldLeft((ListBuffer.empty[Node], node)) { case ((list, current), _) =>
            list += current.next
            (list, current.next)
        }

        result.toList
    }
}

def crabCups(list: CircularList, numMoves: Int): CircularList = {
    val max = list.max
    val min = list.min

    @annotation.tailrec
    def playMove(i: Int, current: Node): CircularList = {
        if (i >= numMoves) {
            list
        } else {
            val nextThree = list.getNextNodes(current, 3)
            val nextThreeValues = nextThree.map(_.value)
            var destination = current.value - 1

            if (destination < min)
                destination = max
            
            while (nextThreeValues.contains(destination)) {
                destination -= 1
                if (destination < min)
                    destination = max
            }

            val destinationLast = list.getNode(destination)
            val destinationHead = nextThree.last.next

            current.next = destinationHead
            nextThree.last.next = destinationLast.next
            destinationLast.next = nextThree.head

            playMove(i + 1, current.next)
        }
    }

    playMove(0, list.firstNode)
}

object CircularList {
    def apply(elems: Int*): CircularList = {
        val circularList = new CircularList
        elems.foreach(circularList.addNode)
        circularList
    }
}

@main
def main(args: String*) = {
    // Solution to the first part
    val firstPart = crabCups(
        CircularList(Seq(3,6,4,2,8,9,7,1,5):_*),
        numMoves = 100
    )
    val firstPartResult = firstPart
        .getNextNodes(firstPart.getNode(1), 8)
        .map(_.value).mkString
    println(firstPartResult)

    // Solution to the second part
    val secondPart = crabCups(
        CircularList((Seq(3,6,4,2,8,9,7,1,5) ++ Seq.tabulate(1000000 - 9)(_ + 10)):_*),
        numMoves = 10000000
    )
    val List(a, b) = secondPart
        .getNextNodes(secondPart.getNode(1), 2)
        .map(_.value)
    println(1L * a * b)
}
