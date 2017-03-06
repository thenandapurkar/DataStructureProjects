#include <iostream>
#include <string>
#include <iostream>
#include <sstream>
#include <fstream>
#include <vector>
#include "rbbst.h"

using namespace std;

void readInFile(char* filename, RedBlackTree<int,vector<int>* >& intclause, RedBlackTree<int,int>& intstate){
	ifstream ifile(filename);
	int mapsize=0;
	int numclauses=0;
	int counter = 0;
	while(!ifile.eof()){
		string line;
		getline(ifile, line);
		if(line[0]=='c'){}
		else if(line[0]=='p'){
			stringstream l(line);
			string word;
			//"p"
			l >> word;
			//cout << word << endl;
			//"cnf"
			l >> word;
			//cout << word << endl;
			//take in the size
			l >> mapsize;
			//cout << mapsize << endl;
			//take in the number of clauses
			l >> numclauses;
			//cout << numclauses << endl;
		}
		else{
			stringstream l(line);
			
			vector<int> *temp = new vector<int>;
			while(!l.eof()){
				int n=0;
				l >> n;
				if(n!=0){
					//cout << "Adding to Vector" << counter  << ": " << n << endl;
					temp->push_back(n);
				}	
			}
			intclause.insert(make_pair(counter, temp));
			counter++;
			//intclause.print();
		}
	}
	for(int i=1; i<=mapsize; i++){
		intstate.insert(make_pair(i,-1));
	}
	//intstate.print();
}

int testExpression(RedBlackTree<int,vector<int>* >& intclause, RedBlackTree<int,int>& intstate){
	//cout << "Made it to Test expression" << endl;
	int clausestrue=0;
	int count=0;
	intclause.print();
	RedBlackTree<int,vector<int>*>::iterator it = intclause.begin();
	// cout << "Set first iterator to begin" << endl;
	for(it=it; it!=intclause.end(); ++it){
		//cout << "Made it inside the loop" << endl;
		vector<int>* temp = it->second;
		// cout << "Set the temp vector" << endl;
		unsigned int numfalse=0;
		for(unsigned int i=0; i<temp->size(); i++){
			//cout << "Made it inside the inner loop" << endl;
			int ab = abs(temp->at(i));
			// cout << ab << endl;
			// cout << "Value in Vector: " << temp->at(i) << endl;
			// cout << "Find ab->second: " << intstate.find(ab)->second << endl;
			if(temp->at(i)<0 && (intstate.find(ab)->second==0)){
				// cout << "First if" << endl;
				clausestrue++;
				count++;
				break;
			}
			else if(temp->at(i)<0 && (intstate.find(ab)->second==1)){
				// cout << "Second if" << endl;
				numfalse++;
				count++;
			}
			else if((intstate.find(ab)->second==1)){
				// cout << "Third if" << endl;
				clausestrue++;
				count++;
				break;
			}
			else if((intstate.find(ab)->second==0)){
				// cout << "Fourth if" << endl;
				numfalse++;
			 	count++;
			}
			else{
				count++;
			}
		}
		//cout << "Exited inside loop" << endl;
		// cout << "How many false?" << numfalse << endl;
		// cout << "Size of temp " << temp->size() << endl;
		if(numfalse==temp->size()){
			return 0;
		}
	}
	cout << "Next member of intclause" << endl;
	// cout << "Exited outer loop" << endl;
	// cout << "Clausestrue: " << clausestrue << endl;
	// cout << "Count " << count << endl;
	if(clausestrue==count){
		return 1;
	}
	else {
		return -1;
	}
}

void evaluateExpression(bool& finalval, RedBlackTree<int,vector<int>* >& intclause, RedBlackTree<int,int>& intstate, RedBlackTree<int,int>& finalmap){
	//cout << "Made it into evaluateExpression" << endl;
	int result = testExpression(intclause,intstate);
	//cout << "Set Result in evaluate expression" << result << endl;
	if(result==1){
		finalval = true;
		intstate.print();
		for(RedBlackTree<int,int>::iterator it = intstate.begin(); it!=intstate.end(); ++it){
			//cout<<"Got through final iterator" << endl;
			finalmap.insert(make_pair(it->first,it->second));
		}
		return;
	}
	else if(result==0){}
	else if(result==-1){
		RedBlackTree<int,int> newstate1 = intstate;
		RedBlackTree<int,int> newstate2 = intstate;
		cout << "Got to line 139" << endl;
		for(RedBlackTree<int,int>::iterator it = intstate.begin(); it!=intstate.end(); ++it){
			if(it->second == -1){
				newstate1.find(it->first)->second=1;
				evaluateExpression(finalval, intclause,newstate1,finalmap);
				newstate2.find(it->first)->second=0;
				evaluateExpression(finalval, intclause,newstate2,finalmap);
				break;
			}
		}
	}
}



int main(int argc, char *argv[]){

	RedBlackTree<int,vector<int>* > ic;
	RedBlackTree<int,int> is;
	RedBlackTree<int,int> final;
	bool state=false;

	readInFile(argv[1], ic, is);
	//cout << "Read File" << endl;
	evaluateExpression(state, ic, is, final);
	//cout << "got past evaluate expression" << endl;
	ofstream out(argv[2]);
	//cout << "gave it the file" << endl;
	if(state==true){
	//	cout << "in the if statement" << endl;
		for(RedBlackTree<int,int>::iterator it = final.begin(); it!=final.end(); ++it){
			out << "x" << (it->first) + 1 << " = " << it->second << endl;
		}
	}
	else{
		out << "No solution" << endl;
	}

return 0;
}