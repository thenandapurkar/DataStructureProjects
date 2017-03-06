#include <map>
#include "setstr.h"
#include <cctype>
#include <iostream>
#include <fstream>
#include <string>
#include <sstream>
#include <cstdio>


using namespace std;

void readInPeople(ifstream& ifile, map<string, SetStr>& fMap){
	while(!ifile.eof()){
		//create string variables to hold name and major
		string name;
		string majors;
		SetStr names;
		
		//grab each line
		getline(ifile, name, ',');
		getline(ifile, majors);

		//put lines into string streams to be further parsed
		stringstream nameline(name);
		stringstream majorline(majors);

		//get the full name (no spaces)
		string full;
		while(!nameline.eof()){
			string temp;
			nameline >> temp;
			full = full+temp + " ";
		}

		//get each major and add the name to each one
		while(!majorline.eof()){
			string temp;
			majorline >> temp;
			//make each major uppercase
			for(unsigned int i=0; i<temp.length(); i++){
				temp[i] = toupper(temp[i]);
			}
			if(fMap.find(temp) != fMap.end()){
				fMap.find(temp)->second.insert(full);
			}
			else{
				SetStr tmp = SetStr();
				tmp.insert(full);
				fMap.insert(make_pair(temp, tmp));
			}
		}
	}
}

void printMajors(ifstream& ifile, ofstream& ofile, map<string, SetStr>& fMap){
	while(!ifile.eof()){
		string line;

		//create a line to hold each major requested
		getline(ifile, line);
		for(unsigned int i=0; i<line.length(); i++){
				line[i] = toupper(line[i]);
			}
		
		//write each major to the file
		stringstream majorline(line);
		ofile << line << endl;

		//in the case of one major output all people
		//in the case of two, output the intersection
		string major;
		majorline >> major;
		SetStr people = SetStr(fMap[major]);
		while(!majorline.eof()){
			majorline >> major;
			SetStr morepeople = SetStr(fMap[major]);
			people = people&morepeople;
		}

		//iterate through each setstr of people and print them to the list
		for(const string* s=people.first(); s!=NULL; s=people.next()){
			ofile << *s << endl;
		}

		ofile << endl;
		ofile << endl;
	}
}

int main(int argc, char* argv[]){
	map<string, SetStr> cool = map<string, SetStr>();
	
	ifstream ffile(argv[1]);
	ifstream gfile(argv[2]);
	ofstream hfile(argv[3]);

	readInPeople(ffile, cool);
	printMajors(gfile, hfile, cool);
}
