//https://www.hackerrank.com/challenges/angry-children
#include <bits/stdc++.h>

using namespace std;

int angry_children(int k, vector<int> arr){
  sort(arr.begin(), arr.end());
  int maxmin = numeric_limits<int>::max();
  int current;
  
  for(int i = 0; i + k-1 < arr.size(); i++){
    current = arr[i + k-1] - arr[i];
    if(current < maxmin)
      maxmin = current;
  }
  
  return maxmin;
}

int main() {
  int n;
  cin >> n;
  int k;
  cin >> k;
  vector<int> arr(n);
  for(int arr_i = 0; arr_i < n; arr_i++){
    cin >> arr[arr_i];
  }
  int result = angry_children(k, arr);
  cout << result << endl;
  return 0;
}
