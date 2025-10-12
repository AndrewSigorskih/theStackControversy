#pragma once
#include "IStack.hpp"
#include "RBTreeContainer.hpp"

class RBTreeStack : public IStack
{
    public:
        RBTreeStack() : _last_key_added(-1), _tree() {}
        ~RBTreeStack() {}
        void push(int);
        int pop();
        const int& top() const;
        size_t size() const;
        bool empty() const;
    private:
        ssize_t _last_key_added;
        Containers::rbTree _tree;
};
