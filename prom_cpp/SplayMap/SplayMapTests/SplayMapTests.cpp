#include "gtest/gtest.h"
#include "../Container/SplayMap.h"
#include <map>

class SplayEmptyTreeTest : public testing::Test {
public:
	SplayMap<int, int> tree;
};

class SplayTreeTest : public SplayEmptyTreeTest {

protected:
	const int value = 17;
	void SetUp() override {
		tree.insert(make_pair(0, value));
	}
};


TEST_F(SplayEmptyTreeTest, CheckEmptyness)
{
	ASSERT_TRUE(tree.empty());
}

TEST_F(SplayTreeTest, CheckEmptyness)
{
	ASSERT_FALSE(tree.empty());
}

TEST_F(SplayEmptyTreeTest, CheckSize)
{
	ASSERT_EQ(0, tree.size());
}

TEST_F(SplayTreeTest, CheckSize)
{
	ASSERT_NE(0, tree.size());
}

TEST_F(SplayEmptyTreeTest, CheckBegin) {
	auto min = RAND_MAX;
	auto minIndex = -1;

	for (auto i = 0; i < 10; ++i) {
		auto randomValue = rand();

		if (min > randomValue) {
			min = randomValue;
			minIndex = i;
		}

		tree.insert(make_pair(randomValue, i));
	}

	auto findResult = tree.begin();

	ASSERT_EQ(minIndex, findResult->second);
}

TEST_F(SplayEmptyTreeTest, CheckInsert)
{
	auto result = tree.insert(make_pair(0, 1));

	ASSERT_TRUE(result.second);
	ASSERT_EQ(tree.find(0), result.first);
}

TEST_F(SplayTreeTest, CheckInsertOverwrite)
{
	ASSERT_EQ(1, tree.size());

	auto result = tree.insert(make_pair(0, 1));

	ASSERT_EQ(1, tree.size());

	ASSERT_FALSE(result.second);
	ASSERT_EQ(tree.find(0), result.first);
}

TEST_F(SplayTreeTest, CheckHintInsert)
{
	auto val = 1;
	auto findResult = tree.find(0);
	auto pairToInsert = make_pair(1, val);

	auto result = tree.insert(findResult, pairToInsert);

	ASSERT_EQ(val, result->second);
}

TEST_F(SplayTreeTest, CheckHintInsertOverwrite)
{
	auto val = value + 1;
	auto result = tree.insert(tree.find(0), make_pair(0, val));

	ASSERT_EQ(value, result->second);
}

TEST_F(SplayEmptyTreeTest, CheckRangeInsert) 
{
	map<int, int> insertValues;

	for (auto i = 0; i < 10; ++i) {
		insertValues[i] = i;
	}

	tree.insert(insertValues.begin(), insertValues.end());

	ASSERT_EQ(insertValues.size(), tree.size());

	auto treeEnd = tree.end();

	for (auto i = 0; i < 10; ++i) {
		auto findResult = tree.find(i);

		ASSERT_NE(treeEnd, findResult);
		ASSERT_EQ(i, findResult->second);
	}
}

TEST_F(SplayTreeTest, CheckFindSuccess)
{
	auto findResult = tree.find(0);

	ASSERT_NE(tree.end(), findResult);
	ASSERT_EQ(value, findResult->second);
}

TEST_F(SplayTreeTest, CheckFindFailure)
{
	ASSERT_EQ(tree.end(), tree.find(1));
}

int main(int argc, char **argv) {
	testing::InitGoogleTest(&argc, argv);
	return RUN_ALL_TESTS();
}