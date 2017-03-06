#include "lliststr.h"
#include "gtest/gtest.h"

class LListStrTest : public testing::Test {
protected:
	// You can remove any or all of the following functions if its body is empty.

	LListStrTest() {
		// You can do set-up work for each test here.
	}

	virtual ~LListStrTest() {
		// You can do clean-up work that doesn't throw exceptions here.		
	}

	// If the constructor and destructor are not enough for setting up
	// and cleaning up each test, you can define the following methods:
	virtual void SetUp() {
		// Code here will be called immediately after the constructor (right
		// before each test).
		one.push_back("Ting");
		one.push_back("Ethan");
		one.push_back("Anderson");
		one.push_back("Zander");

		three=one;
	}

	virtual void TearDown() {
		// Code here will be called immediately after each test (right
		// before the destructor).
	}

	// Objects declared here can be used by all tests in the test case.
	LListStr one;
	
	LListStr three;
};

TEST_F(LListStrTest, p_bNominal) {
	//Expect 0th element to be 1st name etc.
	EXPECT_EQ("Ting", one.get(0));
	EXPECT_EQ("Ethan", one.get(1));
	EXPECT_EQ("Anderson", one.get(2));
	EXPECT_EQ("Zander", one.get(3));
	EXPECT_EQ(4, one.size());
}

TEST_F(LListStrTest, CCNominal) {
	// Expect two to be the same as one.
	LListStr two(one);
	EXPECT_EQ("Ting", two.get(0));
	EXPECT_EQ("Ethan", two.get(1));
	EXPECT_EQ("Anderson", two.get(2));
	EXPECT_EQ("Zander", two.get(3));
	EXPECT_EQ(4, two.size());
}

TEST_F(LListStrTest, AONominal) {
	// Expect two to be the same as one.
	EXPECT_EQ("Ting", three.get(0));
	EXPECT_EQ("Ethan", three.get(1));
	EXPECT_EQ("Anderson", three.get(2));
	EXPECT_EQ("Zander", three.get(3));
	EXPECT_EQ(4, three.size());
}
