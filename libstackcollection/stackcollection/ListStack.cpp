#include "ListStack.hpp"

void ListStack::push(int __val)
{
    _list.push_back(__val);
}

int ListStack::pop()
{
    return _list.pop_back();
}

const int& ListStack::top() const
{
    return _list.back();
}

size_t ListStack::size() const
{
    return _list.size();
}

bool ListStack::empty() const
{
    return _list.empty();
}
