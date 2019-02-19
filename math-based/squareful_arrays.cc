// https://leetcode.com/problems/number-of-squareful-arrays/
// Idea of the algorithm: pair the numbers into unique squareful pairs (those whose sum
// is a pefect square), keeping for a given number, a hash set of other numbers which do it
// a perfect pair.
// For each iteration, keep track of the last elemnt used in the permutation, and do a
// depth first search of the numbers which conform to a squareful pair with that element.
// This idea uses that if an array is squareful, all of its consecutive pairs have to be
// squareful too.
class Solution {
public:
  int squareful_so_far(int last_used, 
                       unordered_map<int, int>& counts,
                       unordered_map<int, unordered_set<int>>& squareful_after,
                       int current_length,
                       int target_length) {
    
    if (current_length == target_length) {
      return 1;
    } else {
      int num_squareful = 0;
      
      for (auto a : squareful_after[last_used]) {
        if (counts[a] > 0) {
          counts[a]--;
          num_squareful += squareful_so_far(a, 
                                            counts, 
                                            squareful_after,
                                            current_length + 1,
                                            target_length);
          counts[a]++;
        }
      }
      
      return num_squareful;
    }
  }
  
  int numSquarefulPerms(vector<int>& A) {
    unordered_map<int, unordered_set<int>> squareful_after;
    unordered_set<int> perfect_squares;
    unordered_map<int, int> counts;
    int maximum = *max_element(A.begin(), A.end());
    int bound = sqrt(2 * maximum) + 1;
    int result;
    
    for (int i = 0; i <= bound; ++i) {
      perfect_squares.insert(i * i);
    }
    
    for (int i = 0; i < A.size(); ++i) {
      counts[A[i]]++;
      
      for (int j = i + 1; j < A.size(); ++j) {
        if (perfect_squares.count(A[i] + A[j]) > 0) {
          squareful_after[A[i]].insert(A[j]);
          squareful_after[A[j]].insert(A[i]);
        }
      }
    }
    
    for (int i = 0; i < A.size(); ++i)
      squareful_after[-1].insert(A[i]);
    
    return squareful_so_far(-1, counts, squareful_after, 0, A.size());
  }
};
