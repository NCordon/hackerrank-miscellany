// https://leetcode.com/problems/prefix-and-suffix-search/
// If we have n words, since words are of length at most 10,
// and f is going to be called at most n times, then
// algorithmicic complexity is O(n) and space consumption is O(n)
class WordFilter(_words: Array[String]) {
  import scala.collection.mutable.{Map => MutableMap}
  type Trie = MutableMap[String, Int]
  val trie = computeTrie(_words)

  def computeTrie(words: Array[String]): Trie = {
    val m = MutableMap[String, Int]().withDefaultValue(0)

    @annotation.tailrec
    def weightsPrefixSuffix(suffix: String, prefix: String, word: String, i: Int): Unit = {
      if (suffix.length <= word.length) {
        val current = prefix + "#" + suffix
        m(current) = i + 1

        if (suffix.length < word.length) {
          val index = word.length - 1 - suffix.length
          weightsPrefixSuffix(word(index) + suffix, prefix, word, i)
        }
      }
    }

    @annotation.tailrec
    def weightsPrefix(prefix: String, word: String, i: Int): Unit = {
      if (prefix.length <= word.length) {
        weightsPrefixSuffix("", prefix, word, i)
        val index = prefix.length

        if (index < word.length) {
          weightsPrefix(prefix + word(index), word, i)
        }
      }
    }

    words.zipWithIndex.foreach { case (word, i) =>
      weightsPrefix("", word, i)
    }

    return m
  }


  def f(prefix: String, suffix: String): Int = {
    return trie(prefix + "#" + suffix) - 1
  }

}
