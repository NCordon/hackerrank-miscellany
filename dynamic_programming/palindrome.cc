// https://www.hackerrank.com/challenges/short-palindrome/problem
#include <bits/stdc++.h>
using namespace std;
long long MOD = 1E9 + 7;

/*
Test cases:
  ghhggh
  kkkkkkz
*/
long long short_palindrome(string s){
  unordered_map<char, long long> front_counts, rear_counts;
  unordered_map<char, unordered_map<char, long long> > front_edges;
  long long result = 0;

  for(int i = 0; i < s.size(); i++){
    if(!front_edges.count(s[i]))
      front_edges[s[i]] = unordered_map<char, long long>();
    
    for(auto prev_element : front_counts){
      auto edge_pos = (front_edges[s[i]]).find(prev_element.first);
      
      if(edge_pos != (front_edges[s[i]]).end()){
        (front_edges[s[i]])[prev_element.first] = 
          (edge_pos->second + prev_element.second) % MOD;
      }
      else{
        (front_edges[s[i]])[prev_element.first] = prev_element.second;
      }
    }

    auto char_pos = front_counts.find(s[i]);

    if(char_pos != front_counts.end())
      char_pos->second = (char_pos->second + 1) % MOD;
    else
      front_counts[s[i]] = 1;
  }
  
    
  for(int i = s.size() - 1; i >= 0; i--){
    front_counts[s[i]]--;

    if(front_edges.count(s[i])){
      auto edge_pos = front_edges[s[i]].begin();
      
      while(edge_pos != front_edges[s[i]].end()){
        edge_pos->second = (edge_pos->second -  
                          front_counts[edge_pos->first] + MOD) % MOD;
      
        if(edge_pos->second == 0)
          edge_pos = front_edges[s[i]].erase(edge_pos);
        else
          edge_pos++;
      }
    }
    
    if(front_edges.count(s[i])){  
      for(auto rear_element : rear_counts){
        if((front_edges[s[i]]).count(rear_element.first)){          
          result = (result + rear_element.second * 
                   (front_edges[s[i]])[rear_element.first]) % MOD;
        }
      }
    }

    auto char_pos = rear_counts.find(s[i]);

    if(char_pos != rear_counts.end())
      char_pos->second = (char_pos->second + 1) % MOD;
    else
      rear_counts[s[i]] = 1;

  }

  return result;
}

int main(){
  string s;
  cin >> s;
  long long result = short_palindrome(s);
  cout << result << endl;
  return 0;
}
