#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <ctype.h>

/* Range of the numbers to be checked: if user provides anything out of this
interval,
* we should error out with the proper message. */
#define MIN_NUMBER 1
#define MAX_NUMBER 39

/* Limit and sizes */
#define NUMBERS_SIZE 5
#define MAX_FILE_NAME_SIZE 255
#define MAX_NUMBERS_TO_CHECK 100
#define SUCCESS_CODE 0
#define ERROR_CODE 1

/* GLOBAL VARIABLE DECLARATIONS */
int numbers_to_check[MAX_NUMBERS_TO_CHECK][NUMBERS_SIZE];
char *filename;
//int numbers_to_check[][NUMBERS_SIZE];
int numbers[NUMBERS_SIZE];

/* FUNCTION DECLARATIONS */
void userHelpInfo();
int parseArguments(int argc, char *argv[], int numbers[], char filename[]);
int readFile(char *filename, int numbers_to_check[][NUMBERS_SIZE], int numbers[]);
int checkNumber(int numbers_to_check[][NUMBERS_SIZE], int your_number_hash[], int a);
int rowSum(int arr[][MAX_NUMBERS_TO_CHECK], int row);
void printWinners(int winners[][MAX_NUMBERS_TO_CHECK],int numbers_to_check[MAX_NUMBERS_TO_CHECK][NUMBERS_SIZE]);

			
int main(int argc, char *argv[]) {

	int numbers[NUMBERS_SIZE];
	char filename[MAX_FILE_NAME_SIZE];

	if(parseArguments(argc, argv, numbers, filename)==SUCCESS_CODE) {
	
		int n=readFile(filename, numbers_to_check, numbers);
		if (n == 0) { 
			/* As n is linenumber, if its 0, inform the user of an error reading the numbers from the file */
			printf("\nYour file should also not be empty.\nHence, no lines read from the input file.\nPlease check and rerun\n");
			userHelpInfo();
			return ERROR_CODE;
		}

		else {
			int your_numbers_hash[MAX_NUMBER + 1] = {0};
			for (int i = 0; i < NUMBERS_SIZE; i++) {
			your_numbers_hash[numbers[i]] = 1; /* Set hash to 1 for each number you are checking */
		}


		/* At this point you have read n sets of numbers from the file and you should
		check them against your numbers */

		/* The following array tracks what numbers are winners with x matches */
		int winners[NUMBERS_SIZE][MAX_NUMBERS_TO_CHECK];
	
		for (int q = 0; q < NUMBERS_SIZE; q++) {
			for (int r = 0; r < MAX_NUMBERS_TO_CHECK; r++) {
				winners[q][r] = 0;
			}
		}

		/* Find and track winners: i.e. if the first set of numbers matches 5 of your
		numbers
		* winners[5-1][0] = 1
		*/
		for (int i = 0; i < n; i++) {
			int j = checkNumber(numbers_to_check,your_numbers_hash,i);
		
			if (j >= 2) {
				winners[j-1][i] = 1; /* Records the winner number */
			}
		}

		printWinners(winners,numbers_to_check);
	
		}
		
	}

	return 0;
}




/* FUNCTION DEFINITIONS */

/* Function : parseArguments()
* This function must parse the arguments passed to your program and
* return the set of numbers you provided in the arguments as an array of
* integers and the file name provided as an argument in the filename string.
* Upon failure the function must return ERROR CODE.
*/
int parseArguments(int argc, char *argv[], int numbers[], char filename[]){
	
	if (argc!=5) { 
		fprintf(stderr,"\nYou have not correctly entered all required command line inputs.\nPlease check & retry.\n"); 
		userHelpInfo();
		return ERROR_CODE;					                        
	}
	
	else {
		char *numlistcsv=argv[2];
		int count=0;
		
		for (int i=0; numlistcsv[i]!='\0'; i++) {
			if (numlistcsv[i]==',') { //checking if all input lottery key is properly entered on command line
				count++;												            
			}			                              
		}	
		
		if (count!=4) {
			fprintf(stderr, "\nYou have entered invalid lottery key to check with.\nPlease modify & retry\n");
			userHelpInfo();
			return ERROR_CODE;   
		}  
				                                  
		else {
			int dummyintholder = sscanf(argv[2],"%d,%d,%d,%d,%d",&numbers[0],&numbers[1],&numbers[2],&numbers[3],&numbers[4]);
                /* sscanf code inspired from textbook [The C Programming Language by Kernighan & Ritchie, Chapter 7.4 Formatted Input - Scanf ] */
				
			for(int i=0; i<5;i++) {
				//checking if digits entered are in expected range
				if((numbers[i]>MAX_NUMBER)||(numbers[i]<MIN_NUMBER)) {
					fprintf(stderr,"\nNumbers of lottery key should be between 1 to 39.\nPlease modify and retry\n");
					userHelpInfo();
					return ERROR_CODE;
				}
			}
				
			strncpy(filename, argv[4], MAX_FILE_NAME_SIZE - 1); //storing filename from command line input
			filename[MAX_FILE_NAME_SIZE - 1] = '\0'; // being sure of terminating
			/* strncpy usage inspired from Textbook:The C Programming Language by Kernighan & Ritchie, Chapter 8.6 */
		
			return SUCCESS_CODE;	 
		}								 
	}
	
	return SUCCESS_CODE;
}


/* Function : readFile()
* This function reads lines from the file named filename and places each group
* of 5 numbers in a row of the numbers_to_check[][] array.
* On failures, this function returns zero.
* On success, this function returns the number of 5 number lines read from the
file.
* Must handle error like lines with more or less than 5 numbers, numbers that are
not
* in the appropriate range, filename having more lines that your max numbers to
check.
*/
int readFile(char *filename, int numbers_to_check[][NUMBERS_SIZE], int numbers[]) {
	FILE *fp = fopen(filename,"r");	
	char dummy[MAX_NUMBERS_TO_CHECK];
	
	if (fp==NULL) {
		printf("\nFile not found.\nIncorrect file name or file not present in current directory.\nPlease modify and retry\n");
		return 0;	
	}

	else {
	
		int linenumber=0, errcount=0;
		while (fgets(dummy,MAX_NUMBERS_TO_CHECK,fp) != NULL) {
	/* reading each line from file & storing each line from file to dummy char arrays and simultaneously traversing through the file's lines 	plus checking if its end of file using NULL */			
			int dummyintholder = sscanf(dummy, "%d %d %d %d %d", &numbers_to_check[linenumber][0],&numbers_to_check[linenumber][1],&numbers_to_check[linenumber][2],&numbers_to_check[linenumber][3],&numbers_to_check[linenumber][4]); 
			for(int i=0;i<5;i++){
				if((numbers_to_check[linenumber][i]>MAX_NUMBER)||(numbers_to_check[linenumber][i]<MIN_NUMBER)){
					errcount++;
					fprintf(stderr,"\nIn input File, Line:%d Element:%d Value is %d which is not in expected range [%d to %d]",linenumber+1,i+1,numbers_to_check[linenumber][i],MIN_NUMBER,MAX_NUMBER);
				}
			}
			
			linenumber++;
		}
		
		if (errcount>0){
				printf("\nBut don't worry!\nAs I am a user friendly program :\n\t* If there are missing digits in file, I will add 0's in place of them.\n\t* If a number in file is >39 or <1, That number alone in that line wont be considered for matching.\nThis way, your valid entries will be considered and your effort in making those lines wont go waste :)\nNext time, please adhere to 5 numbers per line in file provided in range of [1 to 39].\n");
				userHelpInfo();		
			}
			
		if (linenumber>100){
			fprintf(stderr,"\n!LIMIT EXCEEDED!\nLines in file : %d (Only %d Lines Allowed)\nPlease reduce lines in file & try again.\n",linenumber,MAX_NUMBERS_TO_CHECK);
			userHelpInfo();
			return ERROR_CODE;
		}
	
		fclose(fp);
		return linenumber;
	
	}
	
}


/* Function : checkNumber()
* This function will go over numbers_to_check[] array and compare with
* your_number_hash[]
* to quickly determine how many matches in the numbers_to_check and return the
* number of
* matches.
*/
int checkNumber(int numbers_to_check[][NUMBERS_SIZE], int your_number_hash[], int a) {
	int b;
	int numberofmatches=0;
	
	for (int b=0; b<NUMBERS_SIZE;b++){
		if ( your_number_hash[numbers_to_check[a][b]]==1 )
			numberofmatches++;
	} 
	
	
	return numberofmatches;
	
}


/* Function : rowSum()
* This function checks how many matches are found in each row of input file & the lottery key of 5 numbers user inputs on command line
*/
int rowSum(int arr[][MAX_NUMBERS_TO_CHECK], int row) {
    int sum = 0;
    
    for (int j = 0; j < MAX_NUMBERS_TO_CHECK; j++) {
        sum += arr[row][j];
    }
    
    return sum;
}


/* Function : printWinners()
* This function displays match-count wise output of lottery entries we fed using the input file, in decreasing order of no-of-matches found
*/
void printWinners(int winners[][MAX_NUMBERS_TO_CHECK],int numbers_to_check[MAX_NUMBERS_TO_CHECK][NUMBERS_SIZE]) {	
	//printf("\n %d matches\n");
	printf("\n");
	for(int i=NUMBERS_SIZE; i>0;i--) {
		int matchcount=rowSum(winners,i);
		
		if (matchcount>0 && ((i+1)<6) && ((i+1)>=2)){	
			printf("%d matches:",(i+1));
			
			for (int colnum=0;colnum<(MAX_NUMBERS_TO_CHECK);colnum++) {
			
				if (winners[i][colnum]==1) {
					printf(" {%d,%d,%d,%d,%d}",numbers_to_check[colnum][0],numbers_to_check[colnum][1],numbers_to_check[colnum][2],numbers_to_check[colnum][3],numbers_to_check[colnum][4]);
				}
				
			}
			
			printf("\n");	
		}		
	}		
}


/* Function userHelpInfo()
* This function must tell the user the format of the arguments and
* how to use the command.
*/
void userHelpInfo() {
	printf("\nHola!\nFacing problems?\nFollow these instructions for a clean run next time:\n-> Please enter command line input in this format:\n\t$ ./<PROGRAM NAME> -n N1,N2,N3,N4,N5 -f <FILE NAME.FORMAT EXTENSION>\n-> Make sure you enter 5 numbers separated by a comma (,) in command line & they range between 1 & 39.\n-> The set of numbers given on command line will be considered as the lottery key to compare with entries present in file name specified.\n-> In case of any row having <5 digits in input file, missing value(s) will be considered as a zero.\n-> In case of any row having >5 digits in input file, values beyond the 5th number wont be considered.\n-> Make sure all numbers within a line are separated by spaces in file provided, range between 1 to 39 and don't exceed 100 Lines.\nThat's all it would take! HAPPY RUNNING!\n");
}
