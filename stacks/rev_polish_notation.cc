// https://leetcode.com/problems/evaluate-reverse-polish-notation/
// O(n) solution algorithmically and in space
typedef int (*Operation)(int a, int b); 

class Solution {
public:
  int eval_rpn(vector<string>& tokens) {
    stack<int> evaluations;   
    Operation ops[] = {
	    [](int a, int b){ return a + b; },
	    [](int a, int b){ return a - b; },
	    [](int a, int b){ return a * b; },
	    [](int a, int b){ return a / b; }
    };
    bool eval;
    int op_index;
    int x, y;
    
    for (string token : tokens) {
      eval = true;
      
      if (token == "+")
        op_index = 0;
      else if (token == "-")
        op_index = 1;
      else if (token == "*")
        op_index = 2;
      else if (token == "/")
        op_index = 3;
      else {
        evaluations.push(stoi(token));
        eval = false;
      }
      
      if (eval) {
        y = evaluations.top();
        evaluations.pop();
        x = evaluations.top();
        evaluations.pop();
        evaluations.push(ops[op_index](x, y));
      }
    }
    
    return evaluations.top();
  }
};
