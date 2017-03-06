#include <iostream>
#include <string>
#include "rbbst.h"

using namespace std;

int main()
{
	RedBlackTree<int, string> tester;
	tester.insert(make_pair(10,"cs104"));
	tester.insert(make_pair(20,"cs104"));
	tester.insert(make_pair(30,"cs104"));
	tester.insert(make_pair(15,"cs104"));
	tester.insert(make_pair(25,"cs104"));
	tester.insert(make_pair(12,"cs104"));
	tester.insert(make_pair(5,"cs104"));
	tester.insert(make_pair(3,"cs104"));
	tester.insert(make_pair(8,"cs104"));
	tester.print(); 
	return 0;
}