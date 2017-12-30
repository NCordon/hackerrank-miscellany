// https://www.hackerrank.com/challenges/equal
#include <bits/stdc++.h>

using namespace std;

int compute_solution(vector<int>& arr, int minimum){
  int result = 0;
  int cipher;
  vector<int> ciphers_cost{0, 1, 1, 2, 2};
  
  for(int i = 0; i < arr.size(); i++){
    cipher = arr[i] - minimum;

    result += abs(cipher / 5);
    result += ciphers_cost[cipher % 5];
  }
  return result;
}

int equal(vector<int> arr) {  
  int result = 0;
  int minimum = *(min_element(arr.begin(), arr.end()));
  int maximum = *(max_element(arr.begin(), arr.end()));
  
  if(minimum != maximum){
    result = min(compute_solution(arr, minimum),
                 min(compute_solution(arr, minimum - 1),
                     compute_solution(arr, minimum - 2)));
  }
  return result;
}

int main() {
  int t;
  cin >> t;
  for(int a0 = 0; a0 < t; a0++){
    int n;
    cin >> n;
    vector<int> arr(n);
    for(int arr_i = 0; arr_i < n; arr_i++){
      cin >> arr[arr_i];
    }
    int result = equal(arr);
    cout << result << endl;
  }
  return 0;
}
