// https://leetcode.com/explore/interview/card/google/59/array-and-strings/436/
// Uses a list as a queue to store characters until consumed
// Forward declaration of the read4 API.
int read4(char *buf);

class Solution {
  list<char> intermediate;
  char read_buffer[4];
  
  void buffered_read() {
    int num_read = read4(read_buffer);

    for (int i = 0; i < num_read; ++i)
      intermediate.push_back(read_buffer[i]);
  }
public:
  /**
   * @param buf Destination buffer
   * @param n   Number of characters to read
   * @return    The number of actual characters read
   */
  int read(char *buf, int n) {
    int count = 0;
    
    if (intermediate.empty())
      buffered_read();
    
    while (!intermediate.empty() && count < n) {
      while (!intermediate.empty() && count < n) {
        buf[count] = intermediate.front();
        intermediate.pop_front();
        ++count;
      }

      buffered_read();
    }

    return count;
  }
};
