// https://www.hackerrank.com/challenges/almost-sorted/problem
#include <bits/stdc++.h>
using namespace std;

bool is_range_sorted(vector<int>& arr, int left, int right){
  bool sorted = true;
  
  for(int i = left; i <= right && sorted; i++){
    if(i - 1>= 0)
      sorted &= arr[i] > arr[i - 1];
    if(i + 1 < arr.size())
      sorted &= arr[i] <  arr[i + 1];
  }
  
  return sorted;
}

void swap_elements(vector<int>& arr, int a, int b){
  int aux;
  
  aux = arr[a];
  arr[a] = arr[b];
  arr[b] = aux;
}

void reverse_elements(vector<int>& arr, int i, int j){
  int aux;
  
  while(i <= j){
    aux = arr[i];
    arr[i] = arr[j];
    arr[j] = aux;
    i++; 
    j--;
  }
}

void almost_sorted(vector <int> arr){
  bool sorted = true;
  bool able_to_swap;
  bool able_to_reverse = true;
  int left_wrong = -1, right_wrong;
  
  for(int i = 1; i < arr.size(); i++){
    if(arr[i] < arr[i-1]){
      if(left_wrong == -1){
        left_wrong = i - 1;  
        right_wrong = i;
        sorted = false;
      }
      else
        right_wrong = i;
    }
  }
  
  if(sorted){
    cout << "yes" << endl;
  }
  else{
    // if not sorted, we swap elements and check if
    // range is sorted
    swap_elements(arr, left_wrong, right_wrong);
    able_to_swap = is_range_sorted(arr, left_wrong, right_wrong);
    swap_elements(arr, left_wrong, right_wrong);
    
    if(able_to_swap){
      cout << "yes" << endl << "swap " << left_wrong + 1 
           << " " << right_wrong + 1 << endl;    
    }
    else{
      // if not able to swap, try reverse
      reverse_elements(arr, left_wrong, right_wrong);
      able_to_reverse = is_range_sorted(arr, left_wrong, right_wrong);
      
      if(able_to_reverse){
        cout << "yes" << endl << "reverse " << left_wrong + 1 
             << " " << right_wrong + 1 << endl;
      }
      else{
        cout << "no" << endl;
      }
    }
  }
}

int main(){
  int n;
  cin >> n;
  vector<int> arr(n);
  for(int arr_i = 0; arr_i < n; arr_i++){
    cin >> arr[arr_i];
  }
  almost_sorted(arr);
  return 0;
}
