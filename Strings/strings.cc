#include <vector>
#include <string>
#include <iostream>

using std::cout;
using std::string;
using std::vector;
using std::prev;
using std::endl;
 
string mergeStrings(const string &a, const string &b){
  if(a.empty()){
    return b;
  }
  else if(b.empty()){
    return a;
  }
  else if(a.empty() && b.empty()){
    perror<<"both strings empty";
  }
  else {
    string::const_iterator ait=a.begin(),bit=b.begin(),cit=c.begin();    
    while(ait!=a.end() && bit!=b.end()){
      c.pushback(*ait);
      ait++;
      c.pushback(*bit);
      bit++;
    }
    if(ait==prev(str.end())){
      while(bit!=b.end()){
	c.pushback(*bit);
	bit++;
      }
    }
    if(bit==prev(str.end())){
      while(bit!=b.end()){
	c.pushback(*bit);
	bit++;
      }
    }
    return c;
  }
}


int main(){
  string a="abc";
  string b="def";

  string c=mergeStrings(a,b);
  cout<<"after merging : "<<c<<endl;
  

  return 0;
}
