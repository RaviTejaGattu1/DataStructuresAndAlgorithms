#include <vector>
#include <string>
#include <iostream>

using std::cout;
using std::string;
using std::vector;
using std::prev;
using std::endl;
using std::cerr;
 
string mergeStrings(const string &a, const string &b){
  string c;
  if(a.empty()){
    return b;
  }
  else if(b.empty()){
    return a;
  }
  else if(a.empty() && b.empty()){
    cerr<<"both strings empty";
  }
  else {
    string::const_iterator ait=a.begin(),bit=b.begin(),cit=c.begin();    
    while(ait!=a.end() && bit!=b.end()){
      c.push_back(*ait);
      ait++;
      c.push_back(*bit);
      bit++;
    }
    while(ait!=a.end()){
      c.push_back(*ait);
      ait++;
    }
    while(bit!=b.end()){
      c.push_back(*bit);
      bit++;
    }
  }
  return c;
}


int main(){
  string a="123";
  string b="efgh";

  string c=mergeStrings(a,b);
  cout<<"after merging : "<<c<<endl;
  
  return 0;
}

