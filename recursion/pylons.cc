#include <stack>
#include <vector>
#include <iostream>
#include <numeric>
#include <algorithm>
#include <list>
using namespace std;

bool valid_path(list<pair<int,int>>& path, 
                vector<vector<bool>>& visited,
                int target_length, int R, int C) {
    if (path.size() == target_length)
        return true;
    else {
        bool found = false;
        auto previous = path.back();
        int x = previous.first;
        int y = previous.second;
        
        for (int r = 0; r < R && !found; ++r) {
            if (x != r) {
                for (int c = 0; c < C && !found; ++c) {
                    if (y != c && 
                        (x - y) != (r - c) && 
                        (x + y) != (r + c) &&
                        !visited[r][c]) {
                        
                        path.push_back({r, c});
                        visited[r][c] = true;
                        found = valid_path(path, visited, target_length, R, C);
                    
                        if (!found) {
                            path.pop_back();
                            visited[r][c] = false;
                        }
                    }
                }
            }
        }

        return found;
    }
}

int main() {
    int T, R, C;
    cin >> T;
    bool found;
    stack<pair<int, int>> path;
    
    for (int i = 1; i <= T; ++i) {
        cin >> R >> C;
        found = false;
        vector<vector<bool>> visited(R, vector<bool>(C, false));
        list<pair<int, int>> path;
        
        for (int r = 0; r < R && !found; ++r) {
            for (int c = 0; c < C && !found; ++c) {
                path.push_back({r, c});
                visited[r][c] = true;
                found = valid_path(path, visited, R * C, R, C);
                
                if (!found) {
                    path.pop_back();
                    visited[r][c] = false;
                }
            }
        }
        
        if (found) {
            cout << "Case #" << i << ": " << "POSSIBLE" << endl;
            
            for (auto pair : path)
                cout << pair.first + 1 << " " << pair.second + 1<< endl;
        } else {
            cout << "Case #" << i << ": " << "IMPOSSIBLE" << endl;
        }
    }
}
