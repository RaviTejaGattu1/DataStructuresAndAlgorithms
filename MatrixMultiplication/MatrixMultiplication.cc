/* SYSTEM HEADER DECLARATIONS */
#include<iostream>
#include<fstream>
#include<string>
#include<sstream>
#include<vector>


/* ANTI-COBRA MEASURES X[.·´¯·.´¯·.¸¸.·´¯·>]X :) */
using std::cerr;
using std::cout;
using std::ifstream;
using std::getline;
using std::istringstream;
using std::vector;
using std::string;
using std::endl;


/* FUNCTION DECLARATIONS */
/* Showing only overview upon first interaction.*/
/* Only after acquaintance=>share details.
/* Function definitions located post main block */
int matMulCom(string ,string ); //MATrix MULtiplication COMpatibility check
vector<vector<int>> matrixFile2Vector(const string& ); //Making vector matrix out of data from the file
void printVector(const vector<vector<int>>& ); //Printing a vector
vector<vector<int>> matrixMultiplication(vector<vector<int>> , vector<vector<int>> ); //Matrix Multiplication
void printInstructions(); //User guide wherever required


/* MAIN */
int main(int argc, char *argv[]){
  if(argc!=5){
    cerr<<"Error: Missing data in command line.\nExpected format:\n\t $./<programname> -m <multiplicand-containing-filename>.txt -M <Multiplier-containing-filename>.txt\n";
    printInstructions();
    return 1;
  }
  else {
    string mdcheck1=argv[1];
    string mdcheck2=argv[3];
    string multiplicand;
    string multiplier;
    //Enabling user friendliness by providing flexible matrix order in command line
    if((mdcheck1=="-m") && (mdcheck2=="-M")){ 
      multiplicand=argv[2];
      multiplier=argv[4];
    }
    else if((mdcheck2=="-m") && (mdcheck1=="-M")){
      multiplicand=argv[4];
      multiplier=argv[2];
    }
    else {
      cerr<<"Error: Wrong command line input.\nExpected format:\n\t $./<programname> -m <multiplicand-containing-filename>.txt -M <Multiplier-containing-filename>.txt\n";
      printInstructions();
      return 1;
    }

    if(matMulCom(multiplicand,multiplier)==0){
      vector<vector<int>> matrixproduct=matrixMultiplication(matrixFile2Vector(multiplicand),matrixFile2Vector(multiplier));
      printVector(matrixproduct);
    }//error condition handled in function itself
   
  }
  return 0;
}


/* FUNCTION DEFINITIONS */

// checking MATrix MULtiplication COMpatibility
int matMulCom(string A,string B){
  int sizem1[2],sizem2[2];
  string line1,line2;
  
  //fetch row, column of matrix 1
  ifstream openFile1(A);
  if(openFile1.fail()){
    cerr<<"Error: File "<< A <<" cant be opened. Please check the file name or its presence & retry.\n";
    printInstructions();
    return 1;
  }
  else {
    getline(openFile1,line1);
    istringstream readline1(line1);
    readline1>>sizem1[0]>>sizem1[1];
  }

  //fetch row, column of matrix 2
  ifstream openFile2(B);
  if(openFile2.fail()){
    cerr<<"Error: File "<< B <<" cant be opened. Please check the file name or its presence & retry.\n";
    printInstructions();
    return 1;
  }
  else {
    getline(openFile2,line2);
    istringstream readline2(line2);
    readline2>>sizem2[0]>>sizem2[1];
  }


  if( sizem1[1] == sizem2[0] ){ //checking possibility of matrix multiplication
    return 0;
  }
  else {
    cerr<<"Error: Matrices incompatible for multiplication.\nMake sure column size of multiplicand == row size of Multiplier.\n";
    printInstructions();
    return 1;
  }
}

// Fetching matrix from the file name specified
vector<vector<int>> matrixFile2Vector(const string& matfname) {
    vector<vector<int>> matrixVector;
    ifstream matfetch(matfname);
    string line;
    int firstline=1;
    
    while (getline(matfetch, line)) { //Skipping 1st line read from file to avoid matrix size values from loading into matrix data.
      if(firstline==1){
	firstline=0;
	continue;
      }
        istringstream fline(line);
        vector<int> matrixrow;
        int intholder;
        while (fline>>intholder){
            matrixrow.push_back(intholder);
        }
        matrixVector.push_back(matrixrow);
    }
    return matrixVector;
}

// Printing a Matrix (vector)
void printVector(const vector<vector<int>>& pvec){
  for (int i=0;i<pvec.size();i++){
    for (int j=0;j<pvec[i].size();j++){
      cout<<pvec[i][j]<<" ";
    }
    cout<<endl;
  }
}

// Matrix Multiplication
vector<vector<int>> matrixMultiplication(vector<vector<int>> matrixone, vector<vector<int>> matrixtwo) {
  vector<vector<int>> productmatrix(matrixone.size(), vector<int>(matrixtwo[0].size()));

  for (int i=0;i<matrixone.size();++i) {
        for (int j=0;j<matrixtwo[0].size();++j) {
            for (int k=0; k<matrixtwo.size();++k) {
                productmatrix[i][j]+=matrixone[i][k]*matrixtwo[k][j];
	    }
        }
  }

  return productmatrix;
}

// Printing Instructions
void printInstructions(){
  cout<<"\n";
  cout<<"----------\n";
  cout<<"Hola Amigo!\nFacing problem finding matrix product? Dont worry!\nFollow these instructions for a successful output.\n";
  cout<<"\nInstructions\n* Make sure your command line input is in this format:"<<"\033[1;93m"<<"\n\t $./<programname> -m <multiplicand-containing-filename>.txt -M <Multiplier-containing-filename>.txt\n"<<"\033[0m";
  cout<<"* Dont worry about the order, as long as you specify both matrices & your preference of multiplicand & Multiplier, I will give you the output ;)\n";
  cout<<"* Make sure the files exist in the directory before you run\n";
  cout<<"* Make sure you enter the right file names. I need the right name to find the correct data\n";
  cout<<"* Please enter the size of matrix in first lines of files you provide. The first number is considered row size & the second number as Column Size.\n";
  cout<<"* Hence I expect only 2 values in 1st line of all files you specify.\n";
  cout<<"* If the size values I expect are > 2 => I will ignore everything beyond the 2nd value. I'm a user friendly program :)\n";
  cout<<"* If the size values I expect are < 2 => I will consider the missing size value to be 0.\n* Be mindful that this will impact your effort in getting the product.\n";
  cout<<"* Therefore, even if your matrices are correctly present in file,\n  and column size of multiplicand nor the row size of Multiplier provided => No Multiplication\n----------\n";
}
