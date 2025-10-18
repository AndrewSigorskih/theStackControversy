#include "RBTreeStack.hpp"

void RBTreeStack::push(int data)
{
    // TODO throw error when _last_key_added type limit is reached
    _last_key_added++;
    _tree.insert(_last_key_added, data);
}

int RBTreeStack::pop()
{
    auto result = _tree.pop(_last_key_added);
    if (result.has_value())
    {
        _last_key_added--;
        return result.value();
    } else {
        if (_tree.empty())
            throw std::out_of_range("Trying to pop from an empty instance of RBTreeStack!");
        throw std::runtime_error("Unexpected error occured when trying to pop from an instance of RBTreeStack!");
    }
        
}

const int& RBTreeStack::top() const
{
    auto result = _tree.search(_last_key_added);
    if (result.has_value())
    {
        return *(result.value());
    } else {
        if (_tree.empty())
            throw std::out_of_range("Trying to access an element of an empty instance of RBTreeStack!");
        throw std::runtime_error("Unexpected error occured when trying to search an instance of RBTreeStack!");
    }  
}

size_t RBTreeStack::size() const
{
    return _tree.size();
}

bool RBTreeStack::empty() const
{
    return _tree.empty();
}
