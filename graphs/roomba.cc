// https://leetcode.com/problems/robot-room-cleaner/
// Backtracking keeping track of all cells already
// cleaned. It has been optimized to do as less turns
// as possible
/**
 * // This is the robot's control interface.
 * // You should not implement it, or speculate about its implementation
 * class Robot {
 *   public:
 *     // Returns true if the cell in front is open and robot moves into the cell.
 *     // Returns false if the cell in front is blocked and robot stays in the current cell.
 *     bool move();
 *
 *     // Robot will stay in the same cell after calling turnLeft/turnRight.
 *     // Each turn will be 90 degrees.
 *     void turnLeft();
 *     void turnRight();
 *
 *     // Clean the current cell.
 *     void clean();
 * };
 */
typedef pair<int, int> Position;
typedef Position Direction;

struct pair_hash {
  int operator () (Position const& pos) const {
    return pos.first ^ pos.second;
  }
};

class Solution {
public:
  
  Direction rotate(Direction direction) {
    return Direction{ direction.second, -direction.first };
  }
  
  Position sumPos(Position pos, Direction direction) {
    int x = pos.first + direction.first;
    int y = pos.second + direction.second;
    
    return Position{x, y};
  }
  
  void recClean(Robot& robot, 
                Position current,
                unordered_set<Position, pair_hash>& cleaned,
                Direction direction) {
    if (cleaned.count(current) == 0) {
      robot.clean();
      cleaned.insert(current);
      Direction dir = direction;
      
      for (int i = 0; i < 4; ++i) {
        if (robot.move()) {
          recClean(robot, sumPos(current, dir), cleaned, dir);
          robot.turnLeft();
        } else {
          robot.turnRight();
        }
        
        dir = rotate(dir);
      }
    }
    
    robot.turnRight();
    robot.turnRight();
    robot.move();
  }
  
  void cleanRoom(Robot& robot) {
    Direction init{0, 1};
    unordered_set<Position, pair_hash> cleaned;
    Position current{0, 0};
    
    recClean(robot, current, cleaned, init);
  }
};
