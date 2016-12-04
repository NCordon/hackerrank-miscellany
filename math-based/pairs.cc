#include <cmath>
#include <cstdio>
#include <vector>
#include <iostream>
#include <algorithm>
#include <utility>
#include <unordered_set>
using namespace std;

void divisors(int n, vector<int> &divs){
  divs.clear();
  
  for(int i=1; i<=n/2; i++)
    if(n%i == 0)
      divs.push_back(i);
    
  divs.push_back(n);
}

struct SimpleHash {
    size_t operator()(const pair<int,int> &p) const {
        return p.first ^ p.second;
    }
};

int main() {
  unordered_set<pair<int,int>, SimpleHash> satisfactories; 
  vector<pair<int,int>> init; 
  //  unordered_set<pair<int,int>>::iterator it;
  vector<int> divs_first;
  vector<int> divs_second;
  pair<int,int> current, next;
  bool smaller;
  int n;
  cin >> n;
  
  for(int i=1; i<n; i++)
    init.push_back(pair<int,int>(i,n-i));
  
  
  for(auto it = init.begin(); it!= init.end(); it++){
    current = *it;
    
    // Calculate divisors for first
    divisors(current.first, divs_first);
    divisors(current.second, divs_second);
    
    for(vector<int>::iterator i = divs_first.begin(); i!=divs_first.end(); i++){
      smaller = true;
      for(vector<int>::iterator j = divs_second.begin(); j!=divs_second.end() and smaller; j++){
        next = pair<int,int>(current.first/(*i), current.second/(*j));
        
        if(next.first < next.second)
          satisfactories.insert(next).second;
        else if(next.second > next.first)
          satisfactories.insert(pair<int,int>(next.second, next.first)).second;
      }
    }
  }
  
  cout << satisfactories.size();
  
  return 0;
}
