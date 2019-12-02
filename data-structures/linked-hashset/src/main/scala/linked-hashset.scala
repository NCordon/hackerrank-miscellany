package collection

case class LinkedHashMap[A, B](
  val values: Map[A, B],
  val prev: Map[A, A],
  val post: Map[A, A],
  val first: Option[A],
  val last: Option[A]
)

object LinkedHashMap {
  def isEmpty[A, B](map: LinkedHashMap[A, B]): Boolean = {
    map.values.isEmpty
  }

  def apply[A, B](elems: (A, B)*): LinkedHashMap[A, B] = {
    val init = new LinkedHashMap[A, B](Map.empty, Map.empty, Map.empty, None, None)

    elems.foldLeft(init) { case(map, (a, b)) =>
      add(map, a, b)
    }
  }

  def get[A, B](map: LinkedHashMap[A, B], a: A): Option[B] = {
    map.values.get(a)
  }

  def iterator[A, B](map: LinkedHashMap[A, B]): Iterator[A] = {
    map.first match {
      case None =>
        Iterator.empty
      case Some(first) =>
        map.post.foldLeft((first, Iterator[A]())) { case ((prev, it), _) =>
          val newIt = it ++ Iterator(prev)
          val next = map.post(prev)
          (next, newIt)
        }._2
    }
  }

  def add[A, B](map: LinkedHashMap[A, B], a: A, b: B): LinkedHashMap[A, B] = {
    val newValues = map.values + (a -> b)

    if (map.values.contains(a)) {
      new LinkedHashMap(newValues, map.prev, map.post, map.first, map.last)
    } else {
      (map.first, map.last) match {
        case (Some(f), Some(l)) =>
          val newPrev = map.prev + (f -> a) + (a -> l)
          val newPost = map.post + (l -> a) + (a -> f)
          val newLast = Some(a)
          new LinkedHashMap(newValues, newPrev, newPost, map.first, newLast)
        case _ =>
          new LinkedHashMap(newValues, Map(a -> a), Map(a -> a), Some(a), Some(a))
      }
    }
  }

  def remove[A, B](map: LinkedHashMap[A, B], a: A): LinkedHashMap[A, B] = {
    if (map.values.contains(a)) {
      val newValues = map.values - a
      val pprev = map.prev(a)
      val ppost = map.post(a)
      val newPrev  = map.prev + (ppost -> pprev) - a
      val newPost  = map.post + (pprev -> ppost) - a
      val newFirst = if (newValues.isEmpty) Option.empty[A] else if (map.first == a) Some(ppost) else map.first
      val newLast = if (newValues.isEmpty) Option.empty[A] else if (map.last == a) Some(pprev) else map.last
      new LinkedHashMap(newValues, newPrev, newPost, newFirst, newLast)
    } else {
      map
    }
  }
}
