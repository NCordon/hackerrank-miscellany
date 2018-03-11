// https://leetcode.com/problems/course-schedule/
// O (num_subjects + size of dependencies)
class Solution {
  bool CanCourse(int i, vector<int>& done, vector<int>& discovered, 
                 vector<list<int>>& dependencies) {
    bool can_course = true;
    list<int>::iterator it;
    
    for (it = dependencies[i].begin(); it != dependencies[i].end() && can_course; ++it) {
      if (discovered[*it] && !done[*it]) {
        can_course = false;
      } else if (!done[*it]) {
        discovered[*it] = true;
        can_course = CanCourse(*it, done, discovered, dependencies);
      }
    }
    
    done[i] = true;
    return can_course;
  }
  
public:
  bool canFinish(int num_courses, vector<pair<int, int>>& prerequisites) {
    bool can_finish = true;
    vector<int> done(num_courses, false);
    vector<int> discovered(num_courses, false);
    vector<list<int>> dependencies(num_courses);

    for (auto& req : prerequisites)
      dependencies[req.first].push_back(req.second);

    for (int i = 0; i < num_courses && can_finish; ++i) {
      if (!done[i]) {
        discovered[i] = true;
        can_finish = CanCourse(i, done, discovered, dependencies);
      }
    }

    return can_finish;      
  }
};
