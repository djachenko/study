#include "gtest/include/gtest/gtest.h"
#include "HashTable.h"
#include <string>
#include <iostream>

using namespace std;

TEST(Size, default)
{
	HashTable a;
	
	EXPECT_EQ(0, a.size());
	
	struct Value b;
	
	a.insert("key", b);
	
	EXPECT_EQ(1, a.size());
}

TEST(Insert, default)
{
	HashTable a;
	
	struct Value b;
	
	b.age = 10; 
	
	EXPECT_EQ(true, a.insert("key", b));

}

TEST(Erase,default)
{
    HashTable a;
 
    EXPECT_FALSE(a.erase("key"));
}

TEST(Swap, default)
{
	struct Value a[10];
	struct Value b[10];
	
	HashTable aTable;
	HashTable bTable;
	
	string key = "key0";

	for (int i = 0; i < 10; i++)
	{
		a[i].age = i;
		b[i].age = i * 2;
		
		key[3] = '0' + i;
		
		aTable.insert(key, a[i]);
		bTable.insert(key, b[i]);
	}
	
	aTable.swap(bTable);
	
	for (int i = 0; i < 10; i++)
	{
		key[3] = '0' + i;
		
		EXPECT_EQ(b[i].age, aTable[key].age);
		EXPECT_EQ(a[i].age, bTable[key].age);
	}
}

int main(int argc, char **argv)
{
	::testing::InitGoogleTest(&argc, argv);
	
	return RUN_ALL_TESTS();
}
