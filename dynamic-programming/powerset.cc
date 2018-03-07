//CTCI, 8.4
#include <bits/stdc++.h>
#include <iterator>
#include <iostream>
using namespace std;

bool size_comparison(list<int>& a, list<int>& b){
  return a.size() <= b.size();
}

vector<list<int> > powerset(vector<int>& my_set){
  // Sort my_set so we add all elements in order
  sort(my_set.begin(), my_set.end());
  vector<list<int> > result;
  list<int> subset;
  result.push_back(list<int>());
  int length;
  
  for(int element : my_set){
    length = result.size();
    for(int j = 0; j < length; j++){
      subset = result[j];
      subset.push_back(element);
      result.push_back(subset);
    }
  }

  // Order subsets by size
  sort(result.begin(), result.end(), size_comparison);
  return result;
}


int main(){
  vector<int> test{1,4,7,2};
  vector<list<int> > test_ps = powerset(test);

  for(auto it = test_ps.begin(); it != test_ps.end(); it++){
    cout << "{ ";
    copy(it->begin(), it->end(), ostream_iterator<int>(cout, " "));
    cout << "}";
    cout << endl;
  }
}
