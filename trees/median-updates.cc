// https://www.hackerrank.com/challenges/median/problem
#include <map>
#include <set>
#include <list>
#include <cmath>
#include <ctime>
#include <deque>
#include <queue>
#include <stack>
#include <bitset>
#include <cstdio>
#include <limits>
#include <vector>
#include <cstdlib>
#include <numeric>
#include <sstream>
#include <iostream>
#include <algorithm>
using namespace std;
/* Head ends here */

void median(vector<char> s,vector<int> X){  
  multiset<long int> current;
  bool wrongly_erased;
  multiset<long int>::iterator median, next_median;
  // Fix precission to print
  cout << fixed;
  cout.precision(1);
  
  for(int i = 0; i < s.size(); i++){
    wrongly_erased = false;

    if(current.empty())
      median = current.end();

    // If add instruction, insert value and update mean
    if(s[i] == 'a'){
      current.insert(X[i]);

      if(current.size()%2 == 1){
        if(X[i] >= *median || median == current.end())
          median++;
      }
      else if(X[i] < *median)
        median--;
    }
    else{
      // If erase instruction, try to search value on currently stored
      multiset<long int>::iterator to_erase = current.find(X[i]);
      wrongly_erased = to_erase == current.end();

      // If found, update mean and erase value
      if(!wrongly_erased){
        if(current.size()%2 == 0){
          if(X[i] <= *median)
            median++;
          
          current.erase(to_erase);
        }
        else{
          if(X[i] != *median){
            if(X[i] > *median)
              median--;

            current.erase(to_erase);
          }
          else if(X[i] == *median){
            to_erase = median;
            median--;
            
            current.erase(to_erase);          
          }
        }        
      }
    }

    
    if(wrongly_erased || current.empty())
      cout << "Wrong!" << endl;
    else if(current.size()%2 == 0){
      next_median = median;
      next_median++;
      long int result = *median + *next_median;
      
      if (result%2 == 0)
        cout << result/2 << endl;
      else
        cout << result/2.0 << endl;
    }
    else
      cout << *median << endl;
  } 
    
}
int main(void){

//Helpers for input and output

  int N;
  cin >> N;
   
  vector<char> s;
  vector<int> X;   
  char temp;
  int tempint;
  
  for(int i = 0; i < N; i++){
    cin >> temp >> tempint;
    s.push_back(temp);
    X.push_back(tempint);
  }
   
  median(s,X);
  return 0;
}
