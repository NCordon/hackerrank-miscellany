// https://leetcode.com/problems/lfu-cache
// Solution with O(log n) get and put, where n is the capacity
// If puts and gets are equally distributed with m gets and
// m puts, then complexity is O(m log n)
// We need to keep a map from Keys to (Count, Order of use)
// but also a heap ordered by (Count, Order of Use) -> Key to
// be able to compute the LFU element in O(1). Well, in fact in
// Scala according to
// https://docs.scala-lang.org/overviews/collections/performance-characteristics.html
// retrieving the minimum from a TreeMap / TreeSet is O(log n), but
// still is enough. We also care about additions and removals in O(log n)
// from such a tree.
//
// This is an alternative to implementing the LFU with O(1) get and O(n)
// puts (if we cannot compute minimum in less than O(n)), which would
// lead to O(mn) with equally distributed puts and gets.
//
// Also some considerations about the code. Since LeetCode gives this
// class snippet of code, we cannot do it without mutable data structures
// and vars :(((. Also since LeetCode uses Scala 2.11 there is not a mutable
// TreeMap, so we have to use the TreeSet
class LFUCache(_capacity: Int) {
  type Order = (Int, Int)
  var current = 0
  val orders = scala.collection.mutable.TreeSet[(Order, Int)]()
  val cache  = scala.collection.mutable.Map[Int, Order]()
  val values = scala.collection.mutable.Map[Int, Int]()
  
  private def updateCount(key: Int) = {
    current = current + 1
    val order = if (cache.contains(key)) cache(key) else (0, 0)
    val newOrder = (order._1 + 1, current)
    cache.remove(key)
    orders.remove((order, key))
    cache(key) = newOrder
    orders.add((newOrder, key))
  }
  
  def get(key: Int): Int = {
    if (values.contains(key)) {
      updateCount(key)
      values(key)
    } else {
      -1
    }
  }

  def put(key: Int, value: Int) = {
    if (_capacity > 0) {
      if (values.contains(key)) {
        values(key) = value
        updateCount(key)
      } else {
        if (cache.size == _capacity) {
          val toErase = lfu
          val order = cache(toErase)
          values.remove(toErase)
          cache.remove(toErase)
          orders.remove((order, toErase))
        }

        current = current + 1
        cache(key) = (1, current)
        values(key) = value
        orders.add(((1, current), key))
      }
    }
  }
  
  def lfu(): Int = {
    orders.min._2
  }

}
