#include "user.h"
#include <algorithm>
#include "tweet.h"



using namespace std;


/**
   * Constructor 
   */
  User::User(std::string name){
  	username_ = name;
  }

  /**
   * Destructor
   */
  User::~User(){
  	for(std::list<Tweet*>::iterator it = tweets_.begin(); it!=tweets_.end(); ++it){
  		delete *it;
      it=tweets_.erase(it);
  	}
  }

  /**
   * Gets the name of the user 
   * 
   * @return name of the user 
   */
  string User::name() const{
  	return username_;
  } 

  /**
   * Gets all the followers of this user  
   * 
   * @return Set of Users who follow this user
   */
  set<User*> User::followers() const{
	return followers_;
  }

  /**
   * Gets all the users whom this user follows  
   * 
   * @return Set of Users whom this user follows
   */
  set<User*> User::following() const{
  	return following_;
  }

  /**
   * Gets all the tweets this user has posted
   * 
   * @return List of tweets this user has posted
   */
  list<Tweet*> User::tweets() const{
  	return tweets_;
  } 

  /**
   * Adds a follower to this users set of followers
   * 
   * @param u User to add as a follower
   */
  void User::addFollower(User* u){
  	followers_.insert(u);
  }

  /**
   * Adds another user to the set whom this User follows
   * 
   * @param u User that the user will now follow
   */
  void User::addFollowing(User* u){
  	following_.insert(u);
  }

  /**
   * Adds the given tweet as a post from this user
   * 
   * @param t new Tweet posted by this user
   */
  void User::addTweet(Tweet* t){
  	tweets_.push_back(t);
  }

  bool TweetComp(Tweet* t1, Tweet* t2){
  	return *t1 < *t2;
  }
  /**
   * Produces the list of Tweets that represent this users feed/timeline
   *  It should contain in timestamp order all the tweets from
   *  this user and all the tweets from all the users whom this user follows
   *
   * @return vector of pointers to all the tweets from this user
   *         and those they follow in timestamp order
   */
  vector<Tweet*> User::getFeed(){
  	
  	list<Tweet*> full;

  	//tweets_.sort();
  	list<Tweet*> ploo = tweets_;
  	full.merge(ploo);

  	for (set<User*>::iterator it=following_.begin(); it!=following_.end(); ++it){
  	 	list<Tweet*> temp = (*it)->tweets();
  	 	full.merge(temp);
  	}

    vector<Tweet*> v; 
    v.reserve(full.size()); 

    for(list<Tweet*>::iterator it=full.begin(); it!=full.end(); ++it){
      if((*it)->user() != this && (*it)->beginsWithMention()==true){
         
      }
      else{
        v.push_back(*it);
      }
    }
    //v.insert(v.end(), full.begin(), full.end()); 
    sort(v.begin(), v.end(), TweetComp);


	return v;
  }

  //new function

  void User::addMention(Tweet* t){
    mentions.push_back(t);
  }


  vector<Tweet*> User::getMentions(){
    return mentions;
  }