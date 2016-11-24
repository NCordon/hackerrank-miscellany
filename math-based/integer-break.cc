// Solution to: https://leetcode.com/problems/integer-break/

class Solution {
public:
    int integerBreak(int n) {
        int result = 1;
        
        if(n==1){
            return 1;
        }
        else if(n==2){
            return 1;
        }
        else if(n==3){
            return 2;
        }
        else{
            for(int i=0; i<n/3; i++)
                result *= 3;
            
            if((n+1)%3 == 0)
                result *= 2;
            else if((n-1)%3 == 0){
                result /= 3;
                result *= 4;
            }
        }
        
        return result;
    }
};
