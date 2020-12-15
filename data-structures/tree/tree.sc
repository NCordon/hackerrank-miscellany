//https://www.hackerrank.com/challenges/swap-nodes-algo/problem

case class Children(val left: Int, val right: Int)

def swapNodes(indexes: Array[Array[Int]], queries: Array[Int]): Array[Array[Int]] = {
    var graph = MutableMap.empty[Int, Children]
    
    for (i <- 1 to indexes.size) {
        val Array(a, b) = indexes(i - 1)
        graph(i) = Children(a, b)
    }
    
    queries.map { k =>
        val result = MutableArray.empty[Int]
        
        def traverse(node: Int, depth: Int): Unit = {
            if (node != -1) {
                if (depth % k == 0) {
                    val current = graph(node)
                    graph(node) = Children(current.right, current.left)
                }
                
                traverse(graph(node).left, depth + 1)
                result += node
                traverse(graph(node).right, depth + 1)
            }
        }
        
        traverse(node = 1, depth = 1)
        result.toArray
    }
}