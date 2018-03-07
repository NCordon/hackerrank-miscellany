#include <cmath>
#include <cstdio>
#include <vector>
#include <queue>
#include <iostream>
#include <algorithm>
#include <functional>
using namespace std;

bool tuple_comp(pair<long long,long long> a, pair<long long,long long> b){
  return a.first < b.first;
}

long long average_waiting_time(vector<pair<long long,long long>> shop_times){
  long long current_time = 0;
  sort(shop_times.begin(), shop_times.end(), tuple_comp);
  long long i = 0;
  long long j = 0;
  long long serve_time;
  priority_queue<long long, vector<long long>, greater<long long> > customer_queue;
  long long overall_time = 0;
  
  while(j < shop_times.size()){
    // There is idle time until next customer's arrival
    if(customer_queue.empty()){
      current_time = max(current_time, shop_times[i].first);
    }
    // Whenever we have surpassed customers time of entry and there's still customers
    // not queueing, add them to the waiting queue
    while(shop_times[i].first <= current_time && i < shop_times.size()){
      customer_queue.push(shop_times[i].second);
      i++;
    }
    
    serve_time = customer_queue.top();
    customer_queue.pop();
    current_time += serve_time;
    overall_time += current_time - shop_times[j].first;
    j++;
  }
    
  return overall_time / shop_times.size();
}
  
int main() {
  /* Enter your code here. Read input from STDIN. Print output to STDOUT */  
  long long n, t_i, l_i;
  cin >> n;
  vector<pair<long long,long long>> shop_times;
  
  for(int i = 0; i < n; i++){
    cin >> t_i >> l_i;
    shop_times.push_back(make_pair(t_i, l_i));
  }
  
  cout << average_waiting_time(shop_times) << endl;
  
  return 0;
}
