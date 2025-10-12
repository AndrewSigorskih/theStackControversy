#include "stackcollection/ArrayContainer.hpp"

#include <gtest/gtest.h>

using Containers::Array;

TEST(ArrayTest, DefaultConstructorCreatesEmptyArray)
{
    Array arr;
    EXPECT_EQ(arr.size(), 0u);
    EXPECT_TRUE(arr.empty());
}

TEST(ArrayTest, SizedConstructorInitializesCapacity)
{
    Array arr(10);
    EXPECT_EQ(arr.size(), 0u);
    EXPECT_GE(arr.capacity(), 10u);
}

TEST(ArrayTest, PushBackIncreasesSizeAndStoresValues)
{
    Array arr;
    arr.push_back(1);
    arr.push_back(2);
    arr.push_back(3);

    EXPECT_EQ(arr.size(), 3u);
    EXPECT_EQ(arr.back(), 3);
    EXPECT_EQ(arr.front(), 1);
    EXPECT_FALSE(arr.empty());
}

TEST(ArrayTest, PushFrontInsertsAtBeginning)
{
    Array arr;
    arr.push_back(10);
    arr.push_back(20);
    arr.push_front(5);

    EXPECT_EQ(arr.front(), 5);
    EXPECT_EQ(arr.back(), 20);
    EXPECT_EQ(arr.size(), 3u);
}

TEST(ArrayTest, PopBackRemovesLastElement)
{
    Array arr;
    arr.push_back(1);
    arr.push_back(2);
    arr.push_back(3);

    int val = arr.pop_back();
    EXPECT_EQ(val, 3);
    EXPECT_EQ(arr.size(), 2u);
    EXPECT_EQ(arr.back(), 2);
}

TEST(ArrayTest, PopFrontRemovesFirstElement)
{
    Array arr;
    arr.push_back(1);
    arr.push_back(2);
    arr.push_back(3);

    int val = arr.pop_front();
    EXPECT_EQ(val, 1);
    EXPECT_EQ(arr.front(), 2);
    EXPECT_EQ(arr.size(), 2u);
}

TEST(ArrayTest, IndexOperatorProvidesAccessToElements)
{
    Array arr;
    arr.push_back(10);
    arr.push_back(20);
    arr.push_back(30);

    EXPECT_EQ(arr[0], 10);
    EXPECT_EQ(arr[1], 20);
    EXPECT_EQ(arr[2], 30);

    arr[1] = 99;
    EXPECT_EQ(arr[1], 99);
}

TEST(ArrayTest, CopyConstructorCreatesDeepCopy)
{
    Array arr1;
    arr1.push_back(1);
    arr1.push_back(2);

    Array arr2 = arr1;
    arr2[0] = 42;

    EXPECT_EQ(arr1[0], 1);
    EXPECT_EQ(arr2[0], 42);
    EXPECT_EQ(arr2.size(), arr1.size());
}

TEST(ArrayTest, CopyAssignmentWorksCorrectly)
{
    Array arr1;
    arr1.push_back(10);
    arr1.push_back(20);

    Array arr2;
    arr2.push_back(99);
    arr2 = arr1;

    EXPECT_EQ(arr2.size(), arr1.size());
    EXPECT_EQ(arr2[0], 10);
    EXPECT_EQ(arr2[1], 20);
}

TEST(ArrayTest, ReserveIncreasesCapacityButNotSize)
{
    Array arr;
    arr.reserve(50);

    EXPECT_GE(arr.capacity(), 50u);
    EXPECT_EQ(arr.size(), 0u);
}

TEST(ArrayTest, ShrinkToFitReducesCapacity)
{
    Array arr;
    for (int i = 0; i < 10; ++i)
        arr.push_back(i);

    size_t oldCap = arr.capacity();
    arr.shrink_to_fit(5);
    EXPECT_LE(arr.capacity(), oldCap);
}

TEST(ArrayTest, ClearEmptiesArray)
{
    Array arr;
    arr.push_back(1);
    arr.push_back(2);
    arr.clear();

    EXPECT_EQ(arr.size(), 0u);
    EXPECT_TRUE(arr.empty());
}

TEST(ArrayTest, PopFromEmptyThrows)
{
    Array arr;
    EXPECT_THROW(arr.pop_back(), std::out_of_range);
    EXPECT_THROW(arr.pop_front(), std::out_of_range);
}
