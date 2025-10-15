#include "stackcollection/RBTreeContainer.hpp"

#include <gtest/gtest.h>

using Containers::rbTree;

TEST(rbTreeTest, DefaultConstructorCreatesEmptyTree)
{
    rbTree tree;
    EXPECT_EQ(tree.size(), 0u);
    EXPECT_TRUE(tree.empty());
}

TEST(rbTreeTest, ClearRemovesAllElements)
{
    rbTree tree;
    tree.insert(1, 10);
    tree.insert(2, 20);
    tree.insert(3, 30);

    tree.clear();
    EXPECT_EQ(tree.size(), 0u);
    EXPECT_TRUE(tree.empty());
    EXPECT_FALSE(tree.search(1).has_value());
}

TEST(rbTreeTest, InsertAndSearchSingleElement)
{
    rbTree tree;
    tree.insert(42, 100);
    EXPECT_EQ(tree.size(), 1u);
    EXPECT_FALSE(tree.empty());

    auto valOpt = tree.search(42);
    ASSERT_TRUE(valOpt.has_value());
    EXPECT_EQ(**valOpt, 100);
}

TEST(rbTreeTest, SearchNonExistingKeyReturnsEmptyOptional)
{
    rbTree tree;
    tree.insert(1, 11);
    EXPECT_FALSE(tree.search(99).has_value());
}

TEST(rbTreeTest, InsertMultipleElementsSearchWorks)
{
    rbTree tree;
    for (int i = 0; i < 10; ++i)
        tree.insert(i, i * 10);

    EXPECT_EQ(tree.size(), 10u);

    for (int i = 0; i < 10; ++i)
    {
        auto valOpt = tree.search(i);
        ASSERT_TRUE(valOpt.has_value());
        EXPECT_EQ(**valOpt, i * 10);
    }
}

TEST(rbTreeTest, PopRemovesExistingElement)
{
    rbTree tree;
    tree.insert(5, 50);
    tree.insert(10, 100);
    tree.insert(15, 150);

    auto popped = tree.pop(10);
    ASSERT_TRUE(popped.has_value());
    EXPECT_EQ(*popped, 100);
    EXPECT_EQ(tree.size(), 2u);
    EXPECT_FALSE(tree.search(10).has_value());
}

TEST(rbTreeTest, PopNonExistingKeyReturnsEmptyOptional)
{
    rbTree tree;
    tree.insert(1, 10);
    auto popped = tree.pop(99);
    EXPECT_FALSE(popped.has_value());
    EXPECT_EQ(tree.size(), 1u);
}

TEST(rbTreeTest, CopyConstructorCreatesDeepCopy)
{
    rbTree t1;
    t1.insert(1, 100);
    t1.insert(2, 200);
    t1.insert(3, 300);

    rbTree t2 = t1;
    EXPECT_EQ(t2.size(), t1.size());

    auto val1 = t2.search(2);
    ASSERT_TRUE(val1.has_value());
    EXPECT_EQ(**val1, 200);

    t2.insert(4, 400);
    EXPECT_EQ(t1.size(), 3u);
    EXPECT_EQ(t2.size(), 4u);
}

TEST(rbTreeTest, AssignmentOperatorWorksProperly)
{
    rbTree t1;
    for (int i = 0; i < 5; ++i)
        t1.insert(i, i + 10);

    rbTree t2;
    t2.insert(100, 1000);

    t2 = t1;
    EXPECT_EQ(t2.size(), t1.size());

    for (int i = 0; i < 5; ++i)
    {
        auto valOpt = t2.search(i);
        ASSERT_TRUE(valOpt.has_value());
        EXPECT_EQ(**valOpt, i + 10);
    }
}

TEST(rbTreeTest, MixedInsertPopSearchSequence)
{
    rbTree tree;
    tree.insert(1, 10);
    tree.insert(2, 20);
    tree.insert(3, 30);

    EXPECT_TRUE(tree.search(2).has_value());
    EXPECT_EQ(**tree.search(2), 20);

    tree.pop(2);
    EXPECT_FALSE(tree.search(2).has_value());
    EXPECT_EQ(tree.size(), 2u);

    tree.insert(4, 40);
    EXPECT_EQ(tree.size(), 3u);
    EXPECT_EQ(**tree.search(4), 40);
}

TEST(rbTreeTest, DuplicateKeyOverwritesValueOrIsHandled)
{
    rbTree tree;
    tree.insert(10, 100);
    tree.insert(10, 200);

    EXPECT_EQ(tree.size(), 1);

    auto valOpt = tree.search(10);
    ASSERT_TRUE(valOpt.has_value());
    EXPECT_TRUE(**valOpt == 200);
}

TEST(rbTreeTest, PopFromEmptyTreeIsSafe)
{
    rbTree tree;
    EXPECT_NO_THROW({
        auto result = tree.pop(10);
        EXPECT_FALSE(result.has_value());
    });
}
