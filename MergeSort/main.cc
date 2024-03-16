#include"mergevectors.h"
#include<vector>

using std::vector;

int main() {
    vector<vector<int>> input = {{0,3,99,100},{1, 2, 3, 4, 9, 10}, {5, 6, 7, 8},{0,1,1},{1,1,1,1}};
    vector<int> result;

    mergeVectors(input, result);

    return 0;
}
