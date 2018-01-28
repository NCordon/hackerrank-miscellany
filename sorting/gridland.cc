// https://www.hackerrank.com/challenges/gridland-metro
#include <bits/stdc++.h>

using namespace std;

typedef unsigned long long ull;

struct Track{
  ull row;
  ull start;
  ull end;
};

// Lexicographical comparison
struct trackcomp{
  bool operator()(const Track& lhs, const Track& rhs) const{
    bool lower;
    
    if(lhs.row == rhs.row){
      if(lhs.start == rhs.start)
        lower = (lhs.end < rhs.end);
      else
        lower = (lhs.start < rhs.start);
    }
    else{
      lower = (lhs.row < rhs.row);
    }
    
    return lower;
  }
};

ull gridland_metro(ull n, ull m, ull k, vector<Track> tracks){
  // Insert tracks ordered lexicographically
  set<Track, trackcomp> ordered_tracks(tracks.begin(), tracks.end());
  set<Track, trackcomp>::iterator it;
  ull prev_row, prev_end;
  ull current_start, current_end, current_row;
  ull free_spots = n * m;
  
  for(it = ordered_tracks.begin(); it != ordered_tracks.end(); it++){
    current_row = it->row;
    current_start = it->start;
    current_end = it->end;
    
    if(it != ordered_tracks.begin()){
      if(current_row == prev_row){
        if(current_start <= prev_end){
          current_end = max(current_end, prev_end);
          current_start = prev_end + 1;
        }
      }
    }
    
    free_spots -= current_end - current_start + 1;
    prev_row = current_row;
    prev_end = current_end;
  }
  
  return free_spots;
}

int main() {
  ull n;
  ull m;
  ull k;
  cin >> n >> m >> k;
  vector<Track> tracks;
  
  for(int track_i = 0; track_i < k; track_i++){
    Track current;
    cin >> current.row >> current.start >> current.end;
    
    tracks.push_back(current);
  }
  
  ull result = gridland_metro(n, m, k, tracks);
  cout << result << endl;
  return 0;
}
