// https://www.hackerrank.com/challenges/sherlock-and-cost
#include <bits/stdc++.h>

using namespace std;

// The solution will only contain B's elements or 1s
//   Given the solution for n elements that maximizes S, 
//      starting by 1 or B_i, resp.
//   then the solution for n + 1 elements maximizing S can
//      be constructed from those two, adding a 1 or B_{i-1}
//      to the front
int cost(vector <int> arr){
  int n = arr.size();
  int max_one_starting = 0;
  int max_B_starting = 0;
  int old_one_starting;
  
  for(int i = n - 1; i > 0; i--){
    old_one_starting = max_one_starting;
    max_one_starting = max(max_one_starting, max_B_starting + arr[i] - 1);
    max_B_starting = max(old_one_starting + arr[i - 1] - 1, 
                         max_B_starting + abs(arr[i] - arr[i - 1])); 
  }
  
  return max(max_one_starting, max_B_starting);
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
        int result = cost(arr);
        cout << result << endl;
    }
    return 0;
}
