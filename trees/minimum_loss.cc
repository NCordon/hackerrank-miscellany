//https://www.hackerrank.com/contests/womens-codesprint-2/challenges/minimum-loss/
#include <bits/stdc++.h>
using namespace std;
typedef multiset<long, less<long> >::iterator ms_it;


long minimum_loss(vector <long> price){
  long min_loss = numeric_limits<long>::max();
  long current_loss;
  // Increasing ordered
  multiset<long, less<long> > remaining_prices(price.begin(), price.end());
  ms_it pos_lbound, prev_lbound;
  
  /*
  For each price, find it in the set of rear prices
  and compute the difference between that price and 
  its left one (the maximum of the minimums of rear prices)
  Then erase price from the set of rear prices
  */
  for(int i = 0; i < price.size() - 1; i++){
    pos_lbound = remaining_prices.lower_bound(price[i]);
    
    if(pos_lbound != remaining_prices.begin()){
      prev_lbound = pos_lbound;
      prev_lbound--;
      current_loss = price[i] - *prev_lbound;
      
      if(current_loss < min_loss && current_loss > 0)
        min_loss = current_loss;
      
      // lower_bound == price[i] in this case
      remaining_prices.erase(pos_lbound);
    }
  }
  
  return min_loss;
}

int main(){
    int n;
    cin >> n;
    vector<long> price(n);
    for(int price_i = 0; price_i < n; price_i++){
       cin >> price[price_i];
    }
    int result = minimum_loss(price);
    cout << result << endl;
    return 0;
}
