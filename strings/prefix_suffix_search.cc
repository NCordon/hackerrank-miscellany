// https://leetcode.com/problems/prefix-and-suffix-search/
// If we have n words, since words are of length at most 10,
// and f is going to be called at most n times, then
// algorithmicic complexity is O(n) and space consumption is O(n)
class WordFilter {
  unordered_map<string, int> word_with;
public:
    WordFilter(vector<string>& words) {
      string prefix, suffix, current;

      for (int i = words.size() - 1; i >= 0; --i) {
        string& word = words[i];
        prefix = "";

        for (int j = 0; j <= word.size(); ++j) {
          suffix = "";

          for (int k = word.size(); k >= 0; --k) {
            if (k < word.size())
              suffix = word[k] + suffix;

            current = prefix + "#" + suffix;

            if (word_with.count(current) == 0)
              word_with[current] = i + 1;
          }

          if (j < word.size())
            prefix = prefix + word[j];
        }
      }
    }

    int f(string prefix, string suffix) {
      return word_with[prefix + "#" + suffix] - 1;
    }
};
