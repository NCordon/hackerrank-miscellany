import scala.collection.immutable.TreeSet

object Solution {

  // Complete the shortestReach function below.
  def shortestReach(n: Int, edges: Vector[Vector[Int]], s: Int): Vector[Int] = {
    val init = Vector.fill(n + 1)(Map.empty[Int, Int])

    val d = edges.foldLeft(init) { case (current, Vector(u, v, w)) =>
      current
        .updated(u, current(u) + ((v, w)))
        .updated(v, current(v) + ((u, w)))
    }
    
    @annotation.tailrec
    def solve(
      queue: TreeSet[(Int, Int)],
      dist: Vector[Int],
      computed: Vector[Boolean]
    ): Vector[Int] = {
      if (queue.isEmpty) {
        return dist
      } else {
        val (w, x) = queue.min

        val (nextQueue, nextDist, nextComputed) = {
          if (!computed(x)) {

            val (qq, dd) = d(x).foldLeft((queue, dist)) { case((queue, dist), (z, dxz)) =>
              if (!computed(z) && dist(x) + dxz < dist(z)) {
                (queue + ((dist(z), z)), dist.updated(z, dist(x) + dxz))
              } else {
                (queue, dist)
              }
            }

            (qq, dd, computed.updated(x, true))
          } else {
            (queue, dist, computed)
          }
        }

        solve(nextQueue - ((w, x)), dist, nextComputed)
      }
    }

    val initDist = Vector.fill(n + 1)(Int.MaxValue).updated(s, 0)
    val initQueue = TreeSet[(Int, Int)]((0, s))
    val initComputed = Vector.fill(n + 1)(false)
    val result = solve(initQueue, initDist, initComputed)
    result
  }
}
