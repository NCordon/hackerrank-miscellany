#include <stack>
#include <vector>
#include <iostream>
#include <numeric>
#include <algorithm>
#include <unordered_set>
#include <unordered_map>
#include <queue>
#include <list>
using namespace std;

class lengthComp {
public:
  lengthComp() {};
  
  bool operator() (const string& x, const string& y) const {
    return (x.size() < y.size());
  }
};

int main() {
    int T, N;
    int p, q;
    cin >> T;
    string shorter, longer, current_word;
    bool match;
    int count;
    int first_found, second_found;
    
    for (int t = 1; t <= T; ++t) {
        cin >> N;
        vector<string> word(N);
        unordered_map<string, unordered_set<int>> terminations;
        priority_queue<string, std::vector<string>, lengthComp> sorted;
        unordered_set<int> used_words;
        unordered_set<string> used_terminations;
        
        for (int n = 0; n < N; ++n)
            cin >> word[n];
        
        for (int i = 0; i < N; ++i) {
            for (int j = i + 1; j < N; ++j) {
                if (word[i].size() < word[j].size()) {
                    p = i;
                    q = j;
                } else {
                    p = j;
                    q = i;
                }
                
                shorter = word[p];
                longer = word[q];
                int last_short = word[p].size() - 1;
                int last_long = word[q].size() - 1;
                string termination;
                match = true;
                
                for (int l = 0; l <= last_short && match; ++l) {
                    match = shorter[last_short - l] == longer[last_long - l];
                    if (match) {
                        termination = shorter[last_short - l] + termination;
                        terminations[termination].insert(i);
                        terminations[termination].insert(j);

                        if (used_terminations.count(termination) == 0) {
                          sorted.push(termination);
                          used_terminations.insert(termination);
                        }
                    }
                }
            }
        }
        
        count = 0;
        
        while (!sorted.empty()) {
            auto current = sorted.top();
            sorted.pop();
            first_found = -1;
            second_found = -1;

            for (auto it = terminations[current].begin();
                 it != terminations[current].end() &&
                           ( first_found < 0 ||
                             second_found < 0 ); ++it) {

              if (used_words.count(*it) == 0) {
                if (first_found < 0)
                  first_found = *it;
                else
                  second_found = *it;
              }
            }
                
            if (first_found >= 0 && second_found >= 0) {
              used_words.insert(first_found);
              used_words.insert(second_found);
              count += 2;
            }
        }

        cout << "Case #" << t << ": " << count << endl;
    }
}
    
