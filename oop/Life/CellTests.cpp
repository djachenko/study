#include "gtest/include/gtest/gtest.h"
#include "Cell.h"

TEST(constructor,default)
{
	Cell a;

	a.born();

	EXPECT_NE(a.getState(),0);
	EXPECT_EQ(1,a.getState());
}

TEST(constructor, copy)
{
	Cell a;

	a.born();

	EXPECT_NE(a.getState(),0);
	EXPECT_EQ(1,a.getState());

	Cell b=a;

	EXPECT_EQ(a.getState(), b.getState());
}

TEST(born, default)
{
	Cell a;

	EXPECT_EQ(a.alive(), false);
	
	a.born();
	a.update();

	EXPECT_EQ(a.alive(), true);
}

TEST(die, default)
{
	Cell a;

	a.born();
	a.update();

	EXPECT_EQ(a.dead(), false);

	a.die();
	a.update();

	EXPECT_EQ(a.dead(), true);
}

TEST(update, default)
{
	Cell a;

	EXPECT_EQ(a.alive(), false);

	a.born();

	EXPECT_EQ(a.alive(), false);

	a.update();

	EXPECT_EQ(a.alive(), true);
}

TEST(alive, default)
{
	Cell a;

	EXPECT_EQ(a.alive(), false);

	a.born();
	a.update();

	EXPECT_EQ(a.alive(), true);
}

TEST(dead, default)
{
	Cell a;

	a.born();
	a.update();
	
	EXPECT_EQ(a.dead(), false);

	a.die();
	a.update();

	EXPECT_EQ(a.dead(), true);
}

TEST(getState, default)
{
	Cell a;

	EXPECT_EQ(a.getState(), 0);

	a.born();

	EXPECT_EQ(a.getState(), 1);

	a.update();

	EXPECT_EQ(a.getState(), 2);

	a.die();

	EXPECT_EQ(a.getState(), 3);

	a.update();

	EXPECT_EQ(a.getState(), 0);
}

int main(int argc, char ** args)
{
	::testing::InitGoogleTest(&argc, args);

	return RUN_ALL_TESTS();
}
