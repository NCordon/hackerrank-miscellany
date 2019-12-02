
package object collection {

  class LinkedHashMapSyntax[A, B](val map: LinkedHashMap[A, B]) extends AnyVal {

    def isEmpty: Boolean = {
      LinkedHashMap.isEmpty(map)
    }

    def apply[A, B](elems: (A, B)*): LinkedHashMap[A, B] = {
      LinkedHashMap(elems:_*)
    }

    def get(a: A): Option[B] = {
      LinkedHashMap.get(map, a)
    }

    def iterator: Iterator[A] = {
      LinkedHashMap.iterator(map)
    }

    def add(a: A, b: B): LinkedHashMap[A, B] = {
      LinkedHashMap.add(map, a, b)
    }

    def remove(a: A): LinkedHashMap[A, B] = {
      LinkedHashMap.remove(map, a)
    }
  }

  implicit def mapSyntax[A, B](map: LinkedHashMap[A, B]) = new LinkedHashMapSyntax(map)
}
