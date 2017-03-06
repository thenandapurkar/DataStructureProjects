#include "stackint.h"
#include "llistint.h"
#include <fstream>
#include <iostream>
#include <string>

using namespace std;

int main(int argc, char* argv[]) {

	ifstream laundry(argv[1]);
	ofstream pickups(argv[2]);

	StackInt hamper;

	//initialize towel to something it can never be
	int towel = -2;
	int size = 0;
	while(!laundry.eof()){
		laundry >> towel;

		if(towel == 0){
			hamper.push(0);
			size++;
		}
		else if(towel == -1){
			hamper.push(-1);
			size++;
		}
		else if(towel > 0){
			if (towel > size){
				for(int i=0; i<size; i++){
					if(hamper.top()==0){
						pickups << "Black ";
						hamper.pop();
					}
					else{
						pickups << "White ";
						hamper.pop();

					}
					size--;
				}
			}
			else{
				for(int i=0; i<towel; i++){
					if(hamper.top() == 0){
						pickups << "Black ";
						hamper.pop();
					}
					else{
						pickups << "White ";
						hamper.pop();
					}
					size--;
				}	
		}
	pickups << endl;
	}
}
}