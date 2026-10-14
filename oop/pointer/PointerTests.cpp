#include "Pointer.h"
#include "gtest/include/gtest/gtest.h"

TEST(constructor,default)
{
	int a=7;
	int * b=&a;

	Pointer<int> c(&a);

	EXPECT_EQ(*(c.get()),a);
}

int main(int argc, char ** args)
{
	::testing::InitGoogleTest(&argc, args);

	return RUN_ALL_TESTS();
}
