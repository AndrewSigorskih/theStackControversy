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

TYPED_TEST(StackTest, MixedPushPopSequenceMaintainsLifoOrder)
{
    auto s = this->makeStack();
    s->push(5);
    s->push(10);
    EXPECT_EQ(s->top(), 10);
    EXPECT_EQ(s->pop(), 10);

    s->push(15);
    EXPECT_EQ(s->top(), 15);
    EXPECT_EQ(s->pop(), 15);
    EXPECT_EQ(s->pop(), 5);
    EXPECT_TRUE(s->empty());
}

TYPED_TEST(StackTest, TopReturnsConstReferenceToLastElement)
{
    auto s = this->makeStack();
    s->push(42);
    const int& ref = s->top();
    EXPECT_EQ(ref, 42);

    s->push(99);
    EXPECT_EQ(s->top(), 99);
    EXPECT_NE(&ref, &s->top());
}

TYPED_TEST(StackTest, PopOnEmptyStackThrows)
{
    auto s = this->makeStack();
    EXPECT_THROW(s->pop(), std::out_of_range);
}

TYPED_TEST(StackTest, TopOnEmptyStackThrows)
{
    auto s = this->makeStack();
    EXPECT_TRUE(s->empty());
    // Same note: adjust if you throw exceptions
    EXPECT_THROW(s->top(), std::out_of_range);
}

TYPED_TEST(StackTest, SizeAndEmptyConsistency)
{
    auto s = this->makeStack();
    EXPECT_TRUE(s->empty());
    s->push(1);
    EXPECT_EQ(s->size(), 1u);
    EXPECT_FALSE(s->empty());
    s->push(2);
    EXPECT_EQ(s->size(), 2u);
    s->pop();
    EXPECT_EQ(s->size(), 1u);
    s->pop();
    EXPECT_TRUE(s->empty());
    EXPECT_EQ(s->size(), 0u);
}

TYPED_TEST(StackTest, LargeNumberOfPushPopOperations)
{
    auto s = this->makeStack();
    const int N = 10000;
    for (int i = 0; i < N; ++i)
        s->push(i);

    EXPECT_EQ(s->size(), static_cast<size_t>(N));

    for (int i = N - 1; i >= 0; --i)
        EXPECT_EQ(s->pop(), i);

    EXPECT_TRUE(s->empty());
}
