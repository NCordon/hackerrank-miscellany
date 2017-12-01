// https://www.hackerrank.com/challenges/tree-huffman-decoding/problem
/* 
The structure of the node is

typedef struct node
{
    int freq;
    char data;
    node * left;
    node * right;
    
}node;

*/


void decode_huff(node * root,string s){
  string decoded = "";
  node * current = root;
  
  for(std::string::iterator it = s.begin(); it != s.end(); it++){
    if(*it == '0')
      current = current-> left;
    else
      current = current-> right;
    
    // If current node is a leave
    if(current-> left == NULL && current-> right == NULL){
      decoded.push_back(current-> data);
      current = root;
    }
  }
  
  cout << decoded;
}
