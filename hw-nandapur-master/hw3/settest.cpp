#include "setstr.h"
#include "gtest/gtest.h"

class SetTest : public testing::Test {
protected:

	SetTest() {
	
	}

	virtual ~SetTest() {
			
	}

	
	virtual void SetUp() {
		// add to different lists
		one.insert("Ting");
		one.insert("Ethan");
		one.insert("Anderson");
		one.insert("Jonah");

		two.insert("Elaina");
		two.insert("Alex");
		two.insert("Julieann");
		two.insert("Annie");

		three.insert("Elaina");
		three.insert("Margaret");
		three.insert("Annie");

		
	}

	virtual void TearDown() {
		
		one.remove("Ting");
		one.remove("Ethan");
		one.remove("Anderson");
		one.remove("Jonah");

		two.remove("Elaina");
		two.remove("Alex");
		two.remove("Julieann");
		two.remove("Annie");

		three.remove("Elaina");
		three.remove("Margaret");
		three.remove("Annie");


	}

	
	SetStr one;
	SetStr two;
	SetStr three;
	SetStr uSet;
	SetStr iSet;

	
};

TEST_F(SetTest, Exists) {
	EXPECT_TRUE(one.exists("Ting"));
	EXPECT_TRUE(one.exists("Ethan"));
	EXPECT_TRUE(one.exists("Anderson"));
	EXPECT_TRUE(one.exists("Jonah"));
	
}

TEST_F(SetTest, insert) {
	//Expect 0th element to be 1st name etc.
	EXPECT_TRUE(one.exists("Ting"));
	EXPECT_TRUE(one.exists("Ethan"));
	EXPECT_TRUE(one.exists("Anderson"));
	EXPECT_TRUE(one.exists("Jonah"));

	one.insert("Ethan");

	EXPECT_EQ(4, one.size());
}

TEST_F(SetTest, remove) {

	one.remove("Ethan");
	one.remove("Ting");

	EXPECT_TRUE(one.exists("Anderson"));
	EXPECT_TRUE(one.exists("Jonah"));

	EXPECT_FALSE(one.exists("Ethan"));
	EXPECT_FALSE(one.exists("Ting"));

	one.remove("Zander");
	EXPECT_EQ(2, one.size());
}

TEST_F(SetTest, unionT) {
	uSet = one.setUnion(two);

	EXPECT_TRUE(uSet.exists("Ting"));
	EXPECT_TRUE(uSet.exists("Ethan"));
	EXPECT_TRUE(uSet.exists("Anderson"));
	EXPECT_TRUE(uSet.exists("Jonah"));
	EXPECT_TRUE(uSet.exists("Elaina"));
	EXPECT_TRUE(uSet.exists("Annie"));
	EXPECT_TRUE(uSet.exists("Julieann"));
	EXPECT_TRUE(uSet.exists("Alex"));
	EXPECT_EQ(8, uSet.size());

}

TEST_F(SetTest, intersection){
	iSet = two.setIntersection(three);


	EXPECT_TRUE(iSet.exists("Elaina"));
	EXPECT_TRUE(iSet.exists("Annie"));
	EXPECT_FALSE(iSet.exists("Julieann"));
	EXPECT_FALSE(iSet.exists("Alex"));
	EXPECT_FALSE(iSet.exists("Margaret"));

	EXPECT_EQ(2, iSet.size());

}





