#include "tweet.h"
#include "datetime.h"
#include <sstream>



using namespace std;

/**
* Default constructor 
*/
Tweet::Tweet(){}

/**
* Constructor 
*/
Tweet::Tweet(User* user, DateTime& t, std::string& text){
	person = user;
	timestamp = t;
	content = text;
	stringstream fulltweet(content);
	string temp;
	while(!fulltweet.eof()){
		fulltweet >> temp;
		if(temp[0] == '#'){
			temp = temp.substr(1,temp.size()-1);
			//make uppercase
			for(unsigned int i=0; i<temp.length(); i++){
				temp[i] = toupper(temp[i]);
			}
			hashtagwords.insert(temp);
		}
	}
}



/**
* Gets the timestamp of this tweet
*
* @return timestamp of the tweet
*/
DateTime const & Tweet::time() const{
	return timestamp;
}

/**
* Gets the actual text of this tweet
*
* @return text of the tweet
*/
string const & Tweet::text() const{
	return content;
}


/**
* Returns the hashtagged words without the '#' sign
*
*/
set<string> Tweet::hashTags() const{
	return hashtagwords;
}

/* Create any other public or private helper functions you deem 
 necessary */

User* Tweet::user() const{
	return person;
}

/**
* Return true if this Tweet's timestamp is less-than other's
*
* @return result of less-than comparison of tweet's timestamp
*/
bool Tweet::operator<(const Tweet& other) const{
	return this->timestamp < other.timestamp;
} 

/**
* Outputs the tweet to the given ostream in format:
*   YYYY-MM-DD HH::MM::SS username tweet_text
*
* @return the ostream passed in as an argument
*/
std::ostream& operator<<(std::ostream& os, const Tweet& t){
	os << t.timestamp << " ";
	os << t.user()->name() << " ";
	os << t.content;
	return os;
}

