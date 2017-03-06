#include "datetime.h"
#include <iostream>
#include <ctime>
#include <sstream>



using namespace std;




/**
   * Default constructor for current system time/date
   */
  DateTime::DateTime(){
  	time_t currentTime;
  	struct tm *localTime;

  	time( &currentTime );                   // Get the current time
  	localTime = localtime( &currentTime );  // Convert the current time to the local time

  	day    = localTime->tm_mday;
  	month  = localTime->tm_mon + 1;
  	year   = localTime->tm_year + 1900;
  	hour   = localTime->tm_hour;
  	min    = localTime->tm_min;
  	sec    = localTime->tm_sec;
  }

  /**
   * Alternative constructor 
   */
  DateTime::DateTime(int hh, int mm, int ss, int yy, int mo, int dd){
  	hour=hh;
  	min=mm;
  	sec=ss;
  	year=yy;
  	month=mo;
  	day=dd;
  }

  /**
   * Return true if the timestamp is less-than other's
   *
   * @return result of less-than comparison of timestamp
   */
  bool DateTime::operator<(const DateTime& other) const{
  	if(this->year < other.year){
  		return true;
  	}
  	else if(this->year == other.year){
  		if(this->month < other.month){
  			return true;
  		}
  		else if(this->month == other.month){
  			if(this->day < other.day){
  				return true;
  			}
  			else if(this->day == other.day){
  					if(this->hour < other.hour){
  						return true;
  					}
  					else if(this->hour == other.hour){
  						if(this->min < other.min){
  							return true;
  						}
  						else if(this->min == other.min){
  							if(this->sec <= other.sec){
  								return true;
  							}
  							else {
  								return false;
  							}
  						}
  						else {
  							return false;
  						}
  					}
  					else{
  						return false;
  					}
  			}
  		
  			else{
  				return false;
  			}
  		}
  		else{
  			return false;
  		}
	}
  	else{
  		return false;
  	}
  }

  void DateTime::setToDefault(){
    time_t currentTime;
    struct tm *localTime;

    time( &currentTime );                   // Get the current time
    localTime = localtime( &currentTime );  // Convert the current time to the local time

    day    = localTime->tm_mday;
    month  = localTime->tm_mon + 1;
    year   = localTime->tm_year + 1900;
    hour   = localTime->tm_hour;
    min    = localTime->tm_min;
    sec    = localTime->tm_sec;
  }
  	
  	

  /**
   * Outputs the timestamp to the given ostream in format:
   *   YYYY-MM-DD HH::MM::SS
   *
   * @return the ostream passed in as an argument
   */
  std::ostream& operator<<(std::ostream& os, const DateTime& other){
  	os << other.year << "-";
    if(other.month == 0 || other.month < 10){
      os << 0 << other.month << "-";
    }
    else{
      os << other.month << "-";
    }
    if(other.day == 0 || other.day < 10){
      os << 0 << other.day << " ";
    }
    else{
      os << other.day << " ";
    }
    if(other.hour == 0 || other.hour < 10){
  		os << 0 << other.hour << ":";
  	}
    else{
      os << other.hour << ":";
    }
    if(other.min == 0 || other.min < 10){
      os << 0 << other.min << ":";
    }
    else{
      os << other.min << ":";
    }
    if(other.sec == 0 || other.sec < 10){
      os << 0 << other.sec;
    }
    else{
  	 os << other.sec;
    }
  	return os;
  }



  

  /**
   * Inputs the timestamp to the given istream expecting the format:
   *   YYYY-MM-DD HH::MM::SS
   *  Returns if an error in the format with the DateTime set to the
   *   current system time/date
   *   
   *
   * @return the istream passed in as an argument
   */
  std::istream& operator>>(std::istream& is, DateTime& dt){
  	char t;
    string fulldate;
    is >> fulldate;
  
    stringstream full(fulldate);

    string fulltime;
    is >> fulltime;
    stringstream full2(fulltime);

    
    if(full.fail()){
      dt.setToDefault();
      return is;
    }
    
    if(full2.fail()){
      dt.setToDefault();
      return is;
    }
    
    if(fulldate[4]!='-' || fulldate[7]!='-'){
      dt.setToDefault();
      return is;
    }

    if(fulltime[2]!=':' || fulltime[5]!=':'){
      dt.setToDefault();
      return is;
    }
    if(fulldate.length()!=10){
      dt.setToDefault();
      return is;
    }
    if(fulltime.length()!=8){
      dt.setToDefault();
      return is;
    }

  	full >> dt.year >> t >> dt.month >> t >> dt.day;
  	full2 >> dt.hour >> t >> dt.min >> t >> dt.sec;
    
  
  	return is;
  }

