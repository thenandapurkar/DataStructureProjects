#include <iostream>
#include <fstream>
#include <string>

using namespace std;

int main (int argc, char * argv[]){

	//Read in the input file and designate an output file to write to 
	ifstream numbers(argv[1]);
	ofstream outputs(argv[2]);

	//Get and store the number of integers to follow
	//string thisMany;
	int size = 0;
	numbers >> size;
	if(numbers.fail()){
		cout << 0 << endl;
		numbers.close();
	}
	//int size = stoi(thisMany);
	    
	//Dynamically allocate an array to hold the integers in size 
	int *nums = new int[size];

	for (int i=0; i<size; i++){
		//string temp;
		int num=0;
		numbers >> num;
		nums[i]=num;
	}

	//Add the  numbers and print them to the file 
	int first = 0;
	int last = size-1;
	while(first<=last){
		outputs << nums[first]+nums[last] << endl;
		first++;
		last--;
	}

	//Delete the memory
	delete[] nums;
}
