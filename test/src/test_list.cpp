#include "stackcollection/ListContainer.hpp"

#include <gtest/gtest.h>

using Containers::List;

TEST(ListTest, DefaultConstructorCreatesEmptyList)
{
    List lst;
    EXPECT_EQ(lst.size(), 0u);
    EXPECT_TRUE(lst.empty());
}

TEST(ListTest, ClearEmptiesTheList)
{
    List lst;
    lst.push_back(1);
    lst.push_back(2);
    lst.push_back(3);

    lst.clear();
    EXPECT_EQ(lst.size(), 0u);
    EXPECT_TRUE(lst.empty());
}

TEST(ListTest, PushBackAddsElementsAtEnd)
{
    List lst;
    lst.push_back(1);
    lst.push_back(2);
    lst.push_back(3);

    EXPECT_EQ(lst.size(), 3u);
    EXPECT_EQ(lst.front(), 1);
    EXPECT_EQ(lst.back(), 3);
    EXPECT_FALSE(lst.empty());
}

TEST(ListTest, PushFrontAddsElementsAtBeginning)
{
    List lst;
    lst.push_back(10);
    lst.push_back(20);
    lst.push_front(5);

    EXPECT_EQ(lst.front(), 5);
    EXPECT_EQ(lst.back(), 20);
    EXPECT_EQ(lst.size(), 3u);
}

TEST(ListTest, PopBackRemovesLastElement)
{
    List lst;
    lst.push_back(1);
    lst.push_back(2);
    lst.push_back(3);

    int val = lst.pop_back();
    EXPECT_EQ(val, 3);
    EXPECT_EQ(lst.back(), 2);
    EXPECT_EQ(lst.size(), 2u);
}

TEST(ListTest, PopFrontRemovesFirstElement)
{
    List lst;
    lst.push_back(10);
    lst.push_back(20);
    lst.push_back(30);

    int val = lst.pop_front();
    EXPECT_EQ(val, 10);
    EXPECT_EQ(lst.front(), 20);
    EXPECT_EQ(lst.size(), 2u);
}

TEST(ListTest, SingleElementListPushAndPop)
{
    List lst;
    lst.push_back(42);

    EXPECT_EQ(lst.size(), 1u);
    EXPECT_EQ(lst.front(), 42);
    EXPECT_EQ(lst.back(), 42);

    int popped = lst.pop_back();
    EXPECT_EQ(popped, 42);
    EXPECT_TRUE(lst.empty());
}

TEST(ListTest, PopFromEmptyListThrows)
{
    List lst;
    EXPECT_THROW(lst.pop_back(), std::out_of_range);
    EXPECT_THROW(lst.pop_front(), std::out_of_range);
}

TEST(ListTest, FrontAndBackReturnReferences)
{
    List lst;
    lst.push_back(10);
    const int& f = lst.front();
    const int& b = lst.back();
    EXPECT_EQ(f, 10);
    EXPECT_EQ(b, 10);
}

TEST(ListTest, CopyConstructorCreatesIndependentCopy)
{
    List lst1;
    lst1.push_back(1);
    lst1.push_back(2);
    lst1.push_back(3);

    List lst2 = lst1;
    EXPECT_EQ(lst2.size(), 3u);
    EXPECT_EQ(lst2.front(), 1);
    EXPECT_EQ(lst2.back(), 3);

    lst2.pop_back();
    EXPECT_EQ(lst2.size(), 2u);
    EXPECT_EQ(lst1.size(), 3u);
}

TEST(ListTest, CopyAssignmentOverwritesContents)
{
    List lst1;
    lst1.push_back(5);
    lst1.push_back(10);

    List lst2;
    lst2.push_back(100);
    lst2 = lst1;

    EXPECT_EQ(lst2.size(), lst1.size());
    EXPECT_EQ(lst2.front(), 5);
    EXPECT_EQ(lst2.back(), 10);

    lst2.pop_front();
    EXPECT_EQ(lst2.front(), 10);
    EXPECT_EQ(lst1.front(), 5);
}

TEST(ListTest, MixedPushPopSequenceMaintainsCorrectOrder)
{
    List lst;
    lst.push_back(1);
    lst.push_front(0);
    lst.push_back(2);
    lst.push_back(3);

    EXPECT_EQ(lst.size(), 4u);
    EXPECT_EQ(lst.front(), 0);
    EXPECT_EQ(lst.back(), 3);

    EXPECT_EQ(lst.pop_front(), 0);
    EXPECT_EQ(lst.pop_back(), 3);
    EXPECT_EQ(lst.size(), 2u);
    EXPECT_EQ(lst.front(), 1);
    EXPECT_EQ(lst.back(), 2);
}

TEST(ListTest, ClearThenReuseList)
{
    List lst;
    lst.push_back(1);
    lst.push_back(2);
    lst.clear();
    EXPECT_TRUE(lst.empty());

    lst.push_front(10);
    EXPECT_EQ(lst.size(), 1u);
    EXPECT_EQ(lst.front(), 10);
    EXPECT_EQ(lst.back(), 10);
}
