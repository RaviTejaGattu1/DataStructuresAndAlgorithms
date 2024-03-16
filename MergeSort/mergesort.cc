#include"mergevectors.h"
#include<iostream>
#include<vector>

using std::endl;
using std::cout;
using std::vector;

void mergeVectors(const vector<vector<int>> &input, vector<int> &result){
    vector<int> dummy;

    for (int i=0;i<input.size();++i){
      const vector<int>& list_vector = input[i]; //loading each list into a vector A & dummy vector will be considered vector B
      //In every iteration 2 sets of vector lists will be considered and merged in sorted manner.
      //the next vector A would be the next vector list from input and the vector B will be the result of previous merge sort action. and so on.
        
        int m=list_vector.size();
        int n=dummy.size();
        int k=0,j=0;
        
        //considering 2 set of vector lists at a time, comparing their values and loading 
        while (k<m && j<n) {
            if (list_vector[k]<dummy[j]) {
                result.push_back(list_vector[k++]);
            } else {
                result.push_back(dummy[j++]);
            }
	}
 
	//loading remaining values from list a
        while (k<m) {
            result.push_back(list_vector[k]);
	    k++;
        }
        
        //loading remaining values from list b
        while (j<n) {
            result.push_back(dummy[j]);
	    j++;
        }
        
        //loading result into dummy vector
        dummy=result;
        result.clear();
    }
    
    //Printing output of merged resultant vector
    for(auto it=dummy.begin();it!=dummy.end();++it) {
        std::cout<<*it<< " ";
    }
    cout << endl;
}

