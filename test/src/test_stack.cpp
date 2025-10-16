#include <memory>

#include "stackcollection/IStack.hpp"
#include "stackcollection/ArrayStack.hpp"
#include "stackcollection/ListStack.hpp"
#include "stackcollection/RBTreeStack.hpp"

#include <gtest/gtest.h>

template <typename StackImpl>
class StackTest : public ::testing::Test {
public:
    std::unique_ptr<IStack> makeStack() { return std::make_unique<StackImpl>(); }
};

using Implementations = ::testing::Types<ArrayStack, ListStack, RBTreeStack>;
TYPED_TEST_SUITE(StackTest, Implementations);

TYPED_TEST(StackTest, InitiallyEmpty)
{
    auto s = this->makeStack();
    EXPECT_TRUE(s->empty());
    EXPECT_EQ(s->size(), 0u);
}

TYPED_TEST(StackTest, PushIncreasesSizeAndTopIsLastPushed)
{
    auto s = this->makeStack();
    s->push(10);
    EXPECT_FALSE(s->empty());
    EXPECT_EQ(s->size(), 1u);
    EXPECT_EQ(s->top(), 10);

    s->push(20);
    EXPECT_EQ(s->size(), 2u);
    EXPECT_EQ(s->top(), 20);
}

TYPED_TEST(StackTest, PopReturnsLastPushedValue)
{
    auto s = this->makeStack();
    s->push(1);
    s->push(2);
    s->push(3);

    EXPECT_EQ(s->pop(), 3);
    EXPECT_EQ(s->size(), 2u);
    EXPECT_EQ(s->top(), 2);

    EXPECT_EQ(s->pop(), 2);
    EXPECT_EQ(s->pop(), 1);
    EXPECT_TRUE(s->empty());
    EXPECT_EQ(s->size(), 0u);
}
