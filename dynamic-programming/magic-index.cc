//CTCI, 8.3
#include <bits/stdc++.h>
#include <iterator>
#include <iostream>
using namespace std;

int magic_index(vector<int>& my_vector){
  int left = 0;
  int right = my_vector.size() - 1;
  int middle;
  int magic_index = -1;

  if(!my_vector.empty()){
    if(my_vector[left] == left)
      magic_index = left;
    else if(my_vector[right] == right)
      magic_index = right;
  }
  
  while(left < right && magic_index == -1){
    middle = (left + right) / 2;
    
    if(middle == my_vector[middle])
      magic_index = middle;
    else if(my_vector[middle] < middle){
      left = middle + 1;
      
      if(my_vector[left] == left)
        magic_index = left;
    }
    else{
      right = middle - 1;

      if(right >= 0 && my_vector[right] == right)
        magic_index = right;
    }
    
  }
 
  return magic_index;
}



int magic_index_nd(vector<int>& my_vector){
  int left = 0;
  int right = my_vector.size() - 1;
  int middle;
  int magic_index = -1;
  int i;
  
  if(right >= 0){
    if(my_vector[left] == left)
      magic_index = left;
    else if(my_vector[right] == right)
      magic_index = right;
  }
  
  while(left < right && magic_index == -1){
    middle = (left + right) / 2;
    
    if(middle == my_vector[middle])
      magic_index = middle;
    else if(my_vector[middle] < middle){
      i = middle;

      while(i > left && magic_index == -1){
        i = my_vector[i];
        if(i > 0 && my_vector[i] == i)
          magic_index = i;
      }
      
      left = middle + 1;
      
      if(my_vector[left] == left)
        magic_index = left;
    }
    else{
      right = middle - 1;

      if(right >= 0 && my_vector[right] == right)
        magic_index = right;
    }

  }
 
  return magic_index;
}


int main(){
  vector<int> test_A{0,2,3,4};
  vector<int> test_B;
  vector<int> test_C{-1,0,1,2,3,5,9};
  vector<int> test_D{-10,-5,2,2,2,3,4,8,9,12,13};

  cout << magic_index(test_A) << endl;
  cout << magic_index(test_B) << endl;
  cout << magic_index(test_C) << endl;
  cout << magic_index(test_D) << endl; // Does not work
  cout << magic_index_nd(test_D) << endl;
}
