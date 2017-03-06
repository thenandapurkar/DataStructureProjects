#ifndef TWITENG_H
#define TWITENG_H
#include <map>
#include <string>
#include <set>
#include <stack>
#include <vector>
#include "user.h"
#include "datetime.h"
#include "tweet.h"
#include "heap.h"

struct PairComp
{
  bool operator()(std::pair<std::string,int> hash1, std::pair<std::string,int> hash2)
  {
    return (hash1.first < hash2.first);
  }
};
struct ValueComp
{
  bool operator()(std::pair<std::string,int> hash1, std::pair<std::string,int> hash2)
  {
    return (hash1.second > hash2.second);
  }
};

class TwitEng
{
 public:
  TwitEng();
  ~TwitEng();
  /**
   * Parses the Twitter database and populates internal structures
   * @param filename of the database file
   * @return true if there is an error, false if successful
   */
  bool parse(char* filename);

  /**
   * Allocates a tweet from its parts and adds it to internal structures
   * @param username of the user who made the tweet
   * @param timestamp of the tweet
   * @param text is the actual text of the tweet as a single string
   */
  void addTweet(std::string& username, DateTime& time, std::string& text);

  /**
   * Searches for tweets with the given words and strategy
   * @param words is the hashtag terms in any case without the '#'
   * @param strategy 0=AND, 1=OR
   * @return the tweets that match the search
   */
  std::vector<Tweet*> search(std::vector<std::string>& terms, int strategy);

  /**
   * Dump feeds of each user to their own file
   */
  void dumpFeeds();

  /* You may add other member functions */
  std::vector<std::string> const getUsers();
  std::vector<User*> const getUsers2();
  std::map<std::string, User*> const getUserMap();
  vector<pair<string,int> > gettopFive();
  std::map<std::string, std::string> const getLoginInfo();
  void addUser(std::string name, std::string password);

  /**
   * Dump feeds of each user to their own file
   */
  void dumpMentions();


  void initializeTarj();
  void tarjanAlgorithm();
  void strongConnect(User*& u);
  void outputToFile(const char* outfile);
  
  private:
  
  /* Add any other data members or helper functions here  */
  std::map<std::string, User*> master;
  std::map<std::string, std::string> logins;
  std::map<std::string, std::set<Tweet*> > hashtagmap;
  std::map<std::string, int> hashtagtonums;
  Heap<std::pair<string,int>, ValueComp, PairComp >* frequenthashtags; 


  //for tarjan
  std::stack<User*> s;
  std::map<User*, int> indexes;
  int index;
  vector<User*> users;
  vector< vector<std::string> > components;
  std::set<User*> onstack;
  char* outfile;
  std::map<User*, int> lowlinks;


  
};


#endif