#include <iostream>
#include "card.h"
#include <gtest\gtest.h>
using namespace std;

TEST(cardTest, testCardDefault)
{
	Card *cd = new Card();
	EXPECT_EQ(-1, cd->getId());
	EXPECT_EQ('n', cd->getTop());
	EXPECT_EQ('n', cd->getRight());
	EXPECT_EQ('n', cd->getBot());
	EXPECT_EQ('n', cd->getLeft());
}

TEST(cardTest, testCardId)
{
	for (int i = 0; i < 24; i++)
	{
		Card *cd = new Card(i);
		EXPECT_EQ(i, cd->getId());
	}
}

TEST(cardTest, testCardEdges)
{
	for (int i = 0; i < 24; i++)
	{
		Card *cd = new Card(i);
		// mark top of card depending on card i
		if (i == 17 || i == 2 || i == 1 || i == 23 || i == 10 || i == 13) {          // card with field top
			//top = 'f';
			EXPECT_EQ('f', cd->getTop());
		}
		else if (i == 7 || i == 16) {                                                     // card with road top
			//top = 'r';
			EXPECT_EQ('r', cd->getTop());
		}
		else {                                                                              // card with city top
			//top = 'c';
			EXPECT_EQ('c', cd->getTop());
		}

		// mark right of card depending on card i
		if (i == 18 || i == 5 || i == 19 || i == 9 || i == 20 || i == 1 || i == 23) {          // card with city right
			//right = 'c';
			EXPECT_EQ('c', cd->getRight());
		}
		else if (i == 15 || i == 22 || i == 14 || i == 0 || i == 3) {                          // card with road right
			//right = 'r';
			EXPECT_EQ('r', cd->getRight());
		}
		else {                                                                                      // card with field right
			//right = 'f';
			EXPECT_EQ('f', cd->getRight());
		}

		// mark bot of card depending on card i
		if (i == 18 || i == 6) {                                                           // card with city bot
			//bot = 'c';
			EXPECT_EQ('c', cd->getBot());
		}
		else if (i == 17 || i == 5 || i == 19 || i == 12 || i == 21 || i == 1
			|| i == 23 || i == 4 || i == 8 || i == 3) {                            // card with field bot
			//bot = 'f';
			EXPECT_EQ('f', cd->getBot());
		}
		else {                                                                              // card with road bot
			//bot = 'r';
			EXPECT_EQ('r', cd->getBot());
		}

		// mark left of card depending on card i
		if (i == 18 || i == 5 || i == 19 || i == 9 || i == 20 || i == 12
			|| i == 21 || i == 15 || i == 22 || i == 1 || i == 23 || i == 4) {          // card with city left
			//left = 'c';
			EXPECT_EQ('c', cd->getLeft());
		}
		else if (i == 11 || i == 0 || i == 3 || i == 10 || i == 13 || i == 16) {    // card with road left
			//left = 'r';
			EXPECT_EQ('r', cd->getLeft());
		}
		else {                                                                              // card with field left
			//left = 'f';
			EXPECT_EQ('f', cd->getLeft());
		}
	}
}

TEST(cardTest, testCardRotate)
{
	for (int i = 0; i < 24; i++)
	{
		Card *cd = new Card(i);
		char oldTop = cd->getTop();
		char oldBot = cd->getBot();
		char oldLeft = cd->getLeft();
		char oldRight = cd->getRight();

		for (int j = 0; j < 4; j++)
		{
			cd->rotate();
			if (j == 0)
			{
				EXPECT_EQ(oldTop, cd->getRight());
				EXPECT_EQ(oldRight, cd->getBot());
				EXPECT_EQ(oldBot, cd->getLeft());
				EXPECT_EQ(oldLeft, cd->getTop());
			}

			else if (j == 1)
			{
				EXPECT_EQ(oldTop, cd->getBot());
				EXPECT_EQ(oldRight, cd->getLeft());
				EXPECT_EQ(oldBot, cd->getTop());
				EXPECT_EQ(oldLeft, cd->getRight());
			}

			else if (j == 2)
			{
				EXPECT_EQ(oldTop, cd->getLeft());
				EXPECT_EQ(oldRight, cd->getTop());
				EXPECT_EQ(oldBot, cd->getRight());
				EXPECT_EQ(oldLeft, cd->getBot());
			}

			else if (j == 3)
			{
				EXPECT_EQ(oldTop, cd->getTop());
				EXPECT_EQ(oldRight, cd->getRight());
				EXPECT_EQ(oldBot, cd->getBot());
				EXPECT_EQ(oldLeft, cd->getLeft());
			}
		}
	}
}


int main(int argc, char* argv[])
{
	::testing::InitGoogleTest(&argc, argv);
	RUN_ALL_TESTS();
	cin.get();
	return 0;
}
