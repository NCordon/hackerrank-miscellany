// https://leetcode.com/problems/task-scheduler/description/
#include <bits/stdc++.h>

class Solution {
public:
  int leastInterval(vector<char>& tasks, int cool_time) {
    unordered_map<char, int> task_count;
    vector<pair<int, char> > remaining_tasks;
    int result = 0;
    int wait_time;
    bool keep_looking;
        
    for (char t : tasks) {
      if (task_count.count(t) == 0)
        task_count[t] = 0;

      ++task_count[t];
    }

    for (auto t : task_count) {
      remaining_tasks.push_back({t.second, t.first});
    }
    
    sort (remaining_tasks.begin(), remaining_tasks.end(), greater<pair<int, char> >());
        
    while (remaining_tasks[0].first > 0) {
      wait_time = cool_time + 1;
        
      keep_looking = true;
          
      for (int i = 0; i < remaining_tasks.size() && wait_time > 0 && keep_looking; i++) {
        if (remaining_tasks[i].first > 0) {
          remaining_tasks[i].first--;
          ++result;
          --wait_time;
        } else {
          keep_looking = false;
        }
      }
          
      sort (remaining_tasks.begin(), remaining_tasks.end(), greater<pair<int, char> >());
        
      if (remaining_tasks[0].first > 0)
        result += wait_time;
    }

    return result;
  }
};
