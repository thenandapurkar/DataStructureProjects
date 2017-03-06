#include "twiteng.h"
#include <iostream>
#include <sstream>
#include <fstream>
#include <algorithm>
#include <stdexcept>


using namespace std;


TwitEng::TwitEng(){}


TwitEng::~TwitEng(){
  for (map<string, User*>::iterator it=master.begin(); it!=master.end(); ++it){
    delete it->second;
  }
}
/**
* Parses the Twitter database and populates internal structures
* @param filename of the database file
* @return true if there is an error, false if successful
*/
bool TwitEng::parse(char* filename){
  
  ifstream ifile(filename);
  
  string dummy;
  int numUsers;

  getline(ifile, dummy);
  stringstream first(dummy);
  first >> numUsers;

  if(first.fail()){
    return true;
  }

  for(int i=0; i<numUsers; i++){
    string temp;

    getline(ifile, temp);
    stringstream line(temp);

    string curruser;
    line >> curruser;
    if(line.fail()){
      return true;
    }

    User *curr;
    map<string,User*>::iterator it;
    it = master.find(curruser);
    if(it!=master.end()){
      curr = it->second;
    }
    else{
      curr = new User(curruser);
      master.insert(pair<string, User*>(curruser, curr));
    }
    while(!line.eof()){
      string nextuser;
      line >> nextuser;
      if(line.fail()){
        return true;
      }
      map<string,User*>::iterator it;
      it = master.find(nextuser);
      if(it!=master.end()){
        curr->addFollowing(master.find(nextuser)->second);
        master.find(nextuser)->second->addFollower(curr);
      }
      else{
        User *next = new User(nextuser);
        master.insert(pair<string, User*>(nextuser, next));
        curr->addFollowing(next);
        next->addFollower(curr);  
      } 
    }
  }

    while(!ifile.eof()){
      string line;
      getline(ifile, line);
      if(line.empty()){
        
      }
      else{
        stringstream tweetline(line);
        
        DateTime dt;
        string text;
        string user;

        tweetline >> dt;
        if(tweetline.fail()){
          return true;
        }

        tweetline >> user;
        if(tweetline.fail()){
          return true;
        }
        getline(tweetline, text);
        addTweet(user, dt, text);
    }

  }   
  return false;
  
}

/**
* Allocates a tweet from its parts and adds it to internal structures
* @param username of the user who made the tweet
* @param timestamp of the tweet
* @param text is the actual text of the tweet as a single string
*/
void TwitEng::addTweet(std::string& username, DateTime& t, std::string& text){
  map<string,User*>::iterator it;
  it = master.find(username);
  if(it==master.end()){
    throw out_of_range("Username not found");
  }
  User *u = master.find(username)->second;
  size_t firstpos = text.find_first_not_of(" \t");
  text = text.substr(firstpos, text.size());
  Tweet *tw = new Tweet(u, t, text);
  tw->setbeginsWithMention(false);
  //check if first word is mention and handle
  if(text[0]=='@'){
    stringstream f(text);
    string name;
    f >> name;
    name = name.substr(1,name.size()-1); 
    User *m = master.find(name)->second;
    tw->setbeginsWithMention(true);
  
    //check if they follow each other
    set<User*>::iterator it;
    it = m->following().find(u);
    set<User*>::iterator it2;
    it2 = u->following().find(m);
    if(it!=m->following().end()&&it2!=u->following().end()){
      m->addMention(tw);
      u->addTweet(tw);
    }
    else{
      m->addMention(tw);
      u->addTweet(tw);
    }
  }

  //check if there are mentions anywhere else
  stringstream fullt(text);
  while(!fullt.eof()){
    string word;
    fullt >> word;
    if(word[0]=='@'&& tw->beginsWithMention()==false){
      word = word.substr(1,word.size()-1); 
      User *m = master.find(word)->second;
      m->addMention(tw);
    }
  }






  
  set<string> one = tw->hashTags();
  for(set<string>::iterator it=one.begin(); it!=one.end(); ++it){
    map<string,set<Tweet*> >::iterator iter;
    iter = hashtagmap.find(*it);
    if(iter!=hashtagmap.end()){
      iter->second.insert(tw);
    }
    else{
      set<Tweet*> temp;
      temp.insert(tw);
      hashtagmap.insert(pair<string,set<Tweet*> >(*it, temp));
    }
  }
  

if(tw->beginsWithMention()==false){
  u->addTweet(tw);
}

}

// *
// * Searches for tweets with the given words and strategy
// * @param words is the hashtag terms in any case without the '#'
// * @param strategy 0=AND, 1=OR
// * @return the tweets that match the search

std::vector<Tweet*> TwitEng::search(std::vector<std::string>& terms, int strategy){
  vector<Tweet*> final;
  

    if(strategy==0){
      set<Tweet*> intersection;
      for(unsigned int i=0; i<terms.size(); i++){
        string term = terms[i];
        //search for uppercase only
        for(unsigned int i=0; i<term.length(); i++){
          term[i] = toupper(term[i]);
        }
        
        map<string,set<Tweet*> >::iterator iter;
        iter = hashtagmap.find(term);
        if(iter!=hashtagmap.end()){
          if(intersection.size()==0){
            intersection = iter->second;
          }
          else{
            set<Tweet*> temp1 = iter->second;
            set<Tweet*> temp2;
            set_intersection(intersection.begin(),intersection.end(),temp1.begin(),temp1.end(),
                    std::inserter(temp2,temp2.begin()));
            intersection = temp2;
          }
        }
        else{
          vector<Tweet*> c;
          return c;
        }
      }
      vector<Tweet*> v; 
      v.reserve(intersection.size()); 
      v.insert(v.end(), intersection.begin(), intersection.end());
      return v;
    }


    else{
      set<Tweet*> tweetunion;
      for(unsigned int i=0; i<terms.size(); i++){
        string term = terms[i];
        //search for uppercase only
        for(unsigned int i=0; i<term.length(); i++){
          term[i] = toupper(term[i]);
        }
        map<string,set<Tweet*> >::iterator iter;
        iter = hashtagmap.find(term);
        if(iter!=hashtagmap.end()){
          set<Tweet*> temp = iter->second;
          for(set<Tweet*>::iterator it=temp.begin(); it!=temp.end(); ++it){
            tweetunion.insert(*it);
          } 
        }
      }
      vector<Tweet*> v; 
      v.reserve(tweetunion.size()); 
      v.insert(v.end(), tweetunion.begin(), tweetunion.end());
      return v;
    
    }
  
  return final;
}

// /**
// * Dump feeds of each user to their own file
// */
void TwitEng::dumpFeeds(){
  for (map<string, User*>::iterator it=master.begin(); it!=master.end(); ++it){
    vector<Tweet*> feed = it->second->getFeed();
    string filename = it->first + ".feed";
    ofstream ofile(filename.c_str());
    ofile << it->first << endl;
    for(int i=feed.size()-1; i>=0; i--){
      ofile << *feed[i] << endl;
    }
  } 
}

vector<string> const TwitEng::getUsers(){
  std::vector<string> full;
  for (map<string, User*>::iterator it=master.begin(); it!=master.end(); ++it){
    full.push_back(it->first);
  }
  return full;
}

vector<User*> const TwitEng::getUsers2(){
  std::vector<User*> full;
  for (map<string, User*>::iterator it=master.begin(); it!=master.end(); ++it){
    full.push_back(it->second);
  }
  return full;
}

map<string, User*> const TwitEng::getUserMap(){
  return master;
}


void TwitEng::initializeTarj(){
  users = getUsers2();
  index = 0; 
  //initialize all of the indexes and lowlinks to undefined values to start
  for (vector<User*>::iterator it=users.begin(); it!=users.end(); ++it){
    indexes.insert(pair<User*, int>(*it, -1));
  }
  //-1 is the integer undefined value
  for (vector<User*>::iterator it=users.begin(); it!=users.end(); ++it){
    lowlinks.insert(pair<User*, int>(*it, -1));
  }
}

void TwitEng::tarjanAlgorithm(){
  for (vector<User*>::iterator it=users.begin(); it!=users.end(); ++it){
    //call strongConnect if user value is still undefined
    if(indexes[*it] == -1){
      strongConnect(*it);
    }
  }
}

void TwitEng::strongConnect(User*& u){
  //set index to smallest unused index
  indexes[u] = index;
  lowlinks[u] = index;
  //increment the index by one
  index=index+1;
  //push the current user onto the stack
  s.push(u);
  //insert into set in order to search later
  onstack.insert(u);
  set<User*> getfollowing = u->following();
  for (set<User*>::iterator it = getfollowing.begin(); it != getfollowing.end(); ++it){
    User* followed = *it;
    if (indexes[followed] == -1){
      //not yet visited...recurse
      strongConnect(followed);
      lowlinks[u] = std::min(lowlinks[u], lowlinks[followed]);
    }
    else if (onstack.find(followed) != onstack.end()){
      //in stack and SCC
      lowlinks[u] = std::min(lowlinks[u], lowlinks[followed]);
    }
  }
  // If v is a root node, pop the stack and generate an SCC
  if (lowlinks[u] == indexes[u]){
    //start a new SCC
    vector<string> connected;
    User* top;
    //needs to run at least once, then excecute while loop
    do
    {
      top = s.top();
      s.pop();
      onstack.erase(top);
      connected.push_back(top->name());
    }
    while(top != u); //then instantiate the while loop
    components.push_back(connected);
  }
}

void TwitEng::outputToFile(const char* outfile){
  //set an ofile
  ofstream ofile(outfile);
  int componentnumber = 1;
  //create a component in each file and print
  for (vector< vector<string> >::iterator it = components.begin(); it != components.end(); ++it){
    ofile << "Component " << componentnumber << endl;
    vector<string> temp = *it;
    //loop through each user and print
    for (vector<string>::iterator it = temp.begin(); it != temp.end(); ++it){
      string username = *it;
      ofile << username << endl;
    }
    //print the extra line
    ofile << endl;
    //increment the component number
    componentnumber=componentnumber+1;
  }
}

