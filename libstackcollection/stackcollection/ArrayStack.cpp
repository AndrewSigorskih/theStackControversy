#include "ArrayStack.hpp"

void ArrayStack::push(int __val)
{
    _array.push_back(__val);
}

int ArrayStack::pop()
{
    return _array.pop_back();
}

const int& ArrayStack::top() const
{
    return _array.back();
}

size_t ArrayStack::size() const
{
    return _array.size();
}

bool ArrayStack::empty() const
{
    return _array.empty();
}
