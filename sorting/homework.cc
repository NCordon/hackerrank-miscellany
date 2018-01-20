// https://www.hackerrank.com/challenges/lilys-homework/problem
#include <bits/stdc++.h>
#include <iterator>
using namespace std;

int min_swaps(vector<int> arr, vector<int> sorted){
  int aux;
  int num_swaps = 0;
  int j;
  int i = 0;
  
  while(i < arr.size()){
    // Find correct position in ordered array and swap both positions
    // Then keep swaping until element in the current position is what
    // it is supposed to be
    if(sorted[i] != arr[i]){
      vector<int>::iterator it = lower_bound(sorted.begin(), sorted.end(), arr[i]);
      j = it - sorted.begin();
      aux = arr[i];
      arr[i] = arr[j];
      arr[j] = aux;
      num_swaps++;
    }
    else
      i++;
  }
  
  return num_swaps;
}

int lilys_homework(vector<int> arr){
  vector<int> sorted(arr);
  int minimum;
  // Try ascendent and descendent order
  sort(sorted.begin(), sorted.end());
  minimum = min_swaps(arr, sorted);
  reverse(arr.begin(), arr.end());
  minimum = min(minimum, min_swaps(arr, sorted));
  
  return minimum;
}

int main() {
  int n;
  cin >> n;
  vector<int> arr(n);
  for(int arr_i = 0; arr_i < n; arr_i++){
    cin >> arr[arr_i];
  }
  int result = lilys_homework(arr);
  cout << result << endl;
  return 0;
}
