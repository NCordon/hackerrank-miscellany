// https://www.hackerrank.com/challenges/the-quickest-way-up/
#include <bits/stdc++.h>

using namespace std;

typedef unordered_map<int,int>::iterator hashmap_it;
typedef vector<int>::iterator vector_it;

struct Node{
  int length_path;
  int square;
  
  Node(int square, int length_path){
    this->length_path = length_path;
    this->square = square;
  }
  Node(){}
};

int quickest_way_up(unordered_map<int,int>& ladders, unordered_map<int,int>& snakes){
  vector<stack<int> >adjacencies(101);
  hashmap_it pos_ladder, pos_snake;
  queue<Node> to_explore;
  to_explore.push(Node(1,0));
  Node current;
  int shortest_path = -1;
  int adjacent;
  
  for(int i = 1; i < 100; i++){
    for(int j = 1; j <= 6 && i+j <= 100; j++){
      pos_ladder = ladders.find(i + j);
      pos_snake = snakes.find(i + j);
    
      // If and adjacent square is the start point of a ladder or a snake, 
      // add its end point
      if(pos_ladder != ladders.end())
        adjacencies[i].push(pos_ladder->second);
      else if(pos_snake != snakes.end())
        adjacencies[i].push(pos_snake->second);
      else
        adjacencies[i].push(i + j);
    }
  }
  
  while(!to_explore.empty() && shortest_path == -1){
    current = to_explore.front();
    to_explore.pop();
    int i = current.square;
    int adjacent;
    
    while(!adjacencies[i].empty() && shortest_path == -1){
      adjacent = adjacencies[i].top();
      to_explore.push(Node(adjacent, current.length_path + 1));
      adjacencies[i].pop();
      
      if(adjacent == 100)
        shortest_path = current.length_path + 1;
    }
  }
  
  return shortest_path;
}
int main(){
  int num_cases, num_snakes, num_ladders;
  int start_point, end_point;
  // Read number of test cases
  cin >> num_cases;
  
  for(int i = 0; i < num_cases; i++){
    unordered_map<int,int> ladders, snakes;
  
    // Read ladders
    cin >> num_ladders;
    for(int j = 0; j < num_ladders; j++){
      cin >> start_point >> end_point;
      ladders[start_point] = end_point;
    }
    
    // Read snakes
    cin >> num_snakes;
    for(int j = 0; j < num_snakes; j++){
      cin >> start_point >> end_point;
      snakes[start_point] = end_point;
    }
    
    cout << quickest_way_up(ladders, snakes) << endl;
  }
}
