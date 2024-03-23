#include <stack>
#include <iostream>

using std::cout;
using std::stack;
using std::endl;

int main(){

  stack<int> myStack;
  for(int i=0;i<6;i++){
    myStack.push(i);
  }
  cout<<"stack size before popping :"<<myStack.size()<<endl;

  while(!myStack.empty()){
    cout<<myStack.top()<<" ";
    myStack.pop();
  }
  cout<<endl;
  cout<<"stack size after popping :"<<myStack.size()<<endl;

  return 0;
}
