#include <vector>
#include <string>
#include <fstream>
#include <sstream>
#include <iostream>

using namespace std;

void readWords(char* filename, vector<vector<string> >& words);

// client interface
void generateSentences(vector<vector<string> >& words, ofstream& ofile);

// recursive helper function
void genHelper(vector<vector<string> >& words,
	       ofstream& ofile,
	       int currentOption,
	       string sentence,
	       int& numSentences);

void readWords(char* filename,vector<vector<string> >& words){
  //Read in the file
  ifstream file(filename);

  //Generate loop to read in each line 
  for(int i=0; i<4; i++){
    
    //store each line as a loop
    string line;
    getline(file, line);
    vector<string> buff;

    //store the line in a stringstream to further parse
    stringstream pos(line);
    string temp;

    //store each word
    while(!pos.eof()){
      pos >> temp;
      buff.push_back(temp);
    }

    //store each vector
    words.push_back(buff);
  }
}

void generateSentences(vector<vector<string> >& words, ofstream& ofile)
{
  int y=0;
  //First case (subject after "The")
  genHelper(words, ofile, 1, "The", y);
  //Second case (Adjective after "The")
  genHelper(words, ofile, 0, "The", y);
  //Output number of sentences
  ofile << y  << " sentences." << endl;
}

void genHelper(vector<vector<string> >& words, ofstream& ofile, int currentOption, 
                string sentence, int& numSentences)
{
  //Create a temp variable to hold version for current iteration
  string temp = sentence;
  sentence=sentence+temp;

  //base case (adverb)
  if(currentOption==3){
    for (unsigned int i=0; i<words[3].size(); i++){
      //Add the word to the sentence along with a period
      sentence=temp + " " + words[3][i] + ".";
      //Print it to the file
      ofile << sentence << endl;
      //increment number of sentences
      numSentences++;
    }

  }
  //recursive case (Verb)
  else if(currentOption==2){
    for (unsigned int i=0; i<words[2].size(); i++){
      sentence=temp + " " + words[2][i];
      ofile << sentence << "." << endl;
      numSentences++;
      genHelper(words, ofile, 3, sentence, numSentences);
    }
  }
  //recursive case (subject)
 else if(currentOption==1){
    for(unsigned int i=0; i<words[1].size(); i++){
      sentence=temp + " " + words[1][i];
      genHelper(words, ofile, 2, sentence, numSentences);
    }
  }
  //recursive case (Adjective)
  else{
    for(unsigned int i=0; i<words[0].size(); i++){
      sentence=temp + " " + words[0][i];
      genHelper(words, ofile, 1, sentence, numSentences);
    }
  }
  
}

int main(int argc, char* argv[])
{
  if(argc < 3){
    cerr << "Usage ./sentences input_file output_file" << endl;
  }
  vector<vector<string> > words;

  // Parse the file
  readWords(argv[1], words);

  // Check the status of parsing
  if(words.size() < 4){
    cerr << "Input file requires 4 lines of words" << endl;
    return 1;
  }

  // Open the output file
  ofstream ofile(argv[2]);
 
  // generate all the sentence options writing them to ofile
  generateSentences(words, ofile);


  ofile.close();

  return 0;
}
