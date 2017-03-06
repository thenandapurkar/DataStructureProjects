GTEST_LL = -I /usr/local/opt/gtest/include/ -l gtest -l gtest_main -pthread

testSet: setstr.o lliststr.o settest.cpp
	g++ -g -Wall setstr.o settest.cpp lliststr.o $(GTEST_LL) -o $@

setstr.o: setstr.cpp setstr.h
	g++ -g -Wall -c setstr.cpp -o $@

llistTest: lliststr.o copytest.cpp
	g++ -g -Wall lliststr.o copytest.cpp $(GTEST_LL) -o $@


lliststr.o: lliststr.cpp lliststr.h
	g++ -g -Wall -c lliststr.cpp -o $@

majors: majors.cpp setstr.o lliststr.o
	g++ -g -Wall setstr.o lliststr.o majors.cpp -o $@

.PHONY: clean copytest settest

copytest: llistTest
	-@./llistTest

settest: testSet
	-@./testSet



