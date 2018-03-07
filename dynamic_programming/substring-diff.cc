//https://www.hackerrank.com/challenges/substring-diff/problem
#include <bits/stdc++.h>
using namespace std;

int max_diff_fixed_second(string first_word, string second_word, int max_errors){
  int length;
  int max_length = 0;
  int errors;
  int last_diff;
  int i,j;
  
  //helloworld yellomarin 3
  
  for(int k = 0; k < first_word.size(); k++){
    length = 0;

    i = k;
    j = 0;
    errors = 0;
    queue<int> last_diff;
    
    while(i < first_word.size() && j < second_word.size()){
      if(first_word[i] == second_word[j])
        length++;
      else{
        errors++;
        
        if(errors > max_errors){
          length = (last_diff.empty()?0:i - last_diff.front());
          errors--;
          last_diff.pop();
        }
        else
          length++;

        last_diff.push(i);
      }

      if(length > max_length)
        max_length = length;

      i++;j++;
    }
  }
  return max_length;
}


int main(){
  int T, S;
  string first_word, second_word;
  cin >> T;
  
  for(int a0 = 0; a0 < T; a0++){
    cin >> S >> first_word >> second_word;
    
    // Explore upper-diagonals and lower-diagonals and take the maximum
    cout << max(max_diff_fixed_second(first_word, second_word, S),
                max_diff_fixed_second(second_word, first_word, S)) << endl;
  }
  return 0;
}
