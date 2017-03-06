#include <iostream>
#include <sstream>
#include <string>
#include "twiteng.h"
#include <QApplication>
#include <QPushButton>
#include "multiwin.h"
#include <stdexcept>


using namespace std;

void displayTweets(vector<Tweet*>& hits);



int main(int argc, char* argv[])
{
  
  if(argc < 2){
    cerr << "Please provide the twitter data file" << endl;
    return 1;
  }
  TwitEng twit;
  
  
  if ( twit.parse(argv[1]) ){
    cerr << "Unable to parse " << argv[1] << endl;
    return 1;
  }
  twit.dumpFeeds();
  twit.initializeTarj();
  
  QApplication app(argc, argv);
  Multiwin w(&twit);
  w.show();
  
//   cout << "=====================================" << endl;
//   cout << "Menu: " << endl;
//   cout << "  AND term term ...                  " << endl;
//   cout << "  OR term term ...                   " << endl;
//   cout << "  TWEET username tweet_text" << endl;
//   cout << "  QUIT (and write feed files)        " << endl;
//   cout << "=====================================" << endl;

  
  

//   bool showmenu = true;
//   while(showmenu){
//     cout << "Enter Command: " << endl;
//     cout << endl;
//     string selection;
//     cin >> selection;

//     if(selection=="AND"){
//       vector<string> hashtags;
//       vector<Tweet*> tweets;
//       string tags;
//       getline(cin, tags);
//       stringstream line(tags);
//       while(!line.eof()){
//         string temp;
//         line >> temp;
//         hashtags.push_back(temp);
//       }
//       tweets = twit.search(hashtags, 0);
//       if(tweets.size()==0){
//         cout << "No matches found." << endl;
//       }
//       else{
//         if(tweets.size()==1){
//           cout << tweets.size() << " match: " << endl;
//         }
//         else{
//           cout << tweets.size() << " matches: " << endl;
//         }
//         for(unsigned int i=0; i<tweets.size(); i++){
//           cout << *tweets[i] << endl;
//         }
//       }
//       cout << endl;
//       continue;
//     }
//     else if(selection=="OR"){
//       vector<string> hashtags;
//       vector<Tweet*> tweets;
//       string tags;
//       getline(cin, tags);
//       stringstream line(tags);
//       while(!line.eof()){
//         string temp;
//         line >> temp;
//         hashtags.push_back(temp);
//       }
//       tweets = twit.search(hashtags, 1);
//       if(tweets.size()==0){
//         cout << "No matches." << endl;
//       }
//       else{
//         if(tweets.size()==1){
//           cout << tweets.size() << " match: " << endl;
//         }
//         else{
//           cout << tweets.size() << " matches: " << endl;
//         }
//         for(unsigned int i=0; i<tweets.size(); i++){
//           cout << *tweets[i] << endl;
//         }
//       }
//       cout << endl;
//       continue;
//     }
//     else if(selection=="TWEET"){
//       string username;
//       cin >> username;
//       string tweet;
//       getline(cin, tweet);
//       DateTime dt;
//       try{
//         twit.addTweet(username, dt, tweet);
//       }
//       catch(out_of_range){
//         cout << "Username not found." << endl;
//       }
//       cout << endl;
//       continue;  
//     }
//     else if(selection=="QUIT"){
//       twit.dumpFeeds();
//       showmenu = false;
//     }
//     else{
//       cout << "Bad input" << endl;
//       continue;
//   }







// }
return app.exec();
}


