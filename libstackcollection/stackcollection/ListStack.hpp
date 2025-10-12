#pragma once
#include "IStack.hpp"
#include "ListContainer.hpp"

class ListStack : public IStack
{
    public:
        ListStack() {}
        ~ListStack() {}
        void push(int);
        int pop();
        const int& top() const;
        size_t size() const;
        bool empty() const;
    private:
        Containers::List _list;
};
