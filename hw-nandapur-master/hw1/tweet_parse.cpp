#include <iostream>
#include <fstream>
#include <string>
#include <sstream>
#include <vector>
#include <algorithm>

using namespace std;

int main (int argc, char * argv[]){

	//Read in input and store it in a stream
	ifstream tweets(argv[1]);
	vector<string> people;
	vector<string> hashtags;
	int numTweets=0;

	if(tweets.fail()){
		cout << "Error File Doesn't Exist" << endl;
		return 0;
	}

	//Loop until the no more tweets
	while(!tweets.eof()){
		
		//Create a stream object for each line
		string line;
		getline(tweets, line);

		//Check if line is empty and update number of tweets
		if(!line.empty()){

			//Store the line in a string stream
			stringstream message(line);
			string temp;

			//Loop through each line for People or Hashtags
			while(!message.eof()){
				message >> temp;
				if(temp[0] == '@'){
					//Check to see if item is currently in list or not...This uses linear search
					if (std::find(people.begin(), people.end(), temp.substr(1,temp.size()-1)) == people.end())
						{
							people.push_back(temp.substr(1,temp.size()-1));
						}
					}
				else if(temp[0] == '#'){
					//check for duplicates
					if (std::find(hashtags.begin(), hashtags.end(), temp.substr(1,temp.size()-1)) == hashtags.end())
						{
							hashtags.push_back(temp.substr(1,temp.size()-1));
						}
					}
			}

			//Increment the number of tweets
			numTweets++;
		}

	}
	//Print out the results
		cout << "1. Number of tweets=" << numTweets << endl;
		cout << "2. Unique users" << endl;
		for(unsigned int i=0; i<people.size(); i++){
			cout << people[i] << endl;
		}
		cout << "3. Unique hashtags" << endl;
		for(unsigned int j=0; j<hashtags.size(); j++){
			cout << hashtags[j] << endl;
		}
}