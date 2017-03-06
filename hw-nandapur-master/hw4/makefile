CXXFLAGS = -g -Wall -c


twitter: twitter.cpp twiteng.o user.o tweet.o datetime.o 
	g++ -g -Wall twitter.cpp tweet.o user.o twiteng.o datetime.o -o $@

twiteng.o: twiteng.cpp twiteng.h
	g++ $(CXXFLAGS) twiteng.cpp -o $@

tweet.o: tweet.cpp tweet.h
	g++ $(CXXFLAGS) tweet.cpp -o $@

user.o: user.cpp user.h
	g++ $(CXXFLAGS) user.cpp -o $@

datetime.o: datetime.cpp datetime.h
	g++ $(CXXFLAGS) datetime.cpp -o $@

