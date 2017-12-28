//https://www.hackerrank.com/challenges/ctci-merge-sort/problem

#include <bits/stdc++.h>

using namespace std;

long count_inversions_and_merge(int array[], long size){
  int i = 0;
  int j = size/2;
  int k = 0;
  vector<int> sorted(size);
  long inversions = 0;
  int num_inverted = 0;

  while(i < size/2 || j < size){
    if((array[i] <= array[j] || j == size) && i < size/2){
      sorted[k] = array[i];
      i++;
    }
    else{
      inversions += j - i - num_inverted;
      sorted[k] = array[j];
      j++;
      num_inverted++;
    }
    k++;
  }

  for(k = 0; k < size; k++)
    array[k] = sorted[k];

  return inversions;    
}

long count_inversions_and_sort(int array[], long size){
  if(size <= 1)
    return 0;
  
  long inversions;
  inversions = count_inversions_and_sort(array, size/2);
  inversions += count_inversions_and_sort(array + size/2, size - size/2);
  inversions += count_inversions_and_merge(array, size);
    
  return inversions;
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
    long result = count_inversions_and_sort(&arr[0], n);
    cout << result << endl;
  }
  return 0;
}
