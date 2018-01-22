// https://www.hackerrank.com/challenges/pylons/
#include <bits/stdc++.h>

using namespace std;

int pylons(int k, vector <int> arr){
  int i = 0;
  int last_tower;
  int dist = 0;
  int result = 0;
  bool doable = true;
  bool last_interval = false;
  
  while(i < arr.size() && doable){
    last_tower = -1;
    
    while(dist < k && i < arr.size()){
      if(arr[i] == 1){
        last_tower = i;
        if(i + k >= arr.size())
          last_interval = true;
      }
      
      dist++;
      i++;
    }
    if(last_tower == -1)
      doable = false;
    else{
      dist = -k + 1;
      if(!last_interval)
        i = last_tower + 1;
      else
        i = arr.size();

      result++;
    }
  }
  
  
  if(!doable)
    result = -1;
  
  return result;
}

int main() {
  int n;
  int k;
  cin >> n >> k;
  vector<int> arr(n);
  for(int arr_i = 0; arr_i < n; arr_i++){
    cin >> arr[arr_i];
  }
  int result = pylons(k, arr);
  cout << result << endl;
  return 0;
}
