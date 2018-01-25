#include <bits/stdc++.h>
using namespace std;

int sherlock_and_minimax(vector <int> arr, int p, int q){
  sort(arr.begin(), arr.end());
  int M = p;
  int maxmin = 0;
  int current_maxmin = 0;
  int mid_point;
  bool in_interval = true;


  if(!arr.empty() && p <= arr.front()){
    maxmin = arr.front() - p;
    M = p;
  }

  // Test cases:
  //    All elements lower or equal than P:   [5,8,14], p = 15, q = 16
  //    All elements greater or equal than Q: [5,8,14], p = 2, q = 4
  //                                          [5,8,14], p = 4, q = 9
  for(int i = 0; i < arr.size() - 1 && in_interval; i++){
    mid_point = (arr[i] + arr[i + 1]) / 2;

    if(mid_point < p){
      mid_point = p;
      current_maxmin = arr[i + 1] - mid_point;
    }
    else{
      if(mid_point > q){
        in_interval = false;
        mid_point = q;
      }
      current_maxmin = mid_point - arr[i];
    }

    if(current_maxmin > maxmin){
      maxmin = current_maxmin;
      M = mid_point;
    }
  }

  if(!arr.empty() && q >= arr.back()){
    current_maxmin = q - arr.back();
    
    if(current_maxmin > maxmin){
      maxmin = current_maxmin;
      M = q;
    }
  }

  return M;
}
 


int main(){
  int n;
  cin >> n;
  vector<int> arr(n);
  for(int arr_i = 0; arr_i < n; arr_i++){
    cin >> arr[arr_i];
  }
  int p;
  int q;
  cin >> p >> q;
  int result = sherlock_and_minimax(arr, p, q);
  cout << result << endl;
  return 0;
}
