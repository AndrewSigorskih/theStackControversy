#pragma once
#include "IStack.hpp"
#include "ArrayContainer.hpp"

class ArrayStack : public IStack
{
    public:
        ArrayStack() {}
        ~ArrayStack() {}
        void push(int);
        int pop();
        const int& top() const;
        size_t size() const;
        bool empty() const;
    private:
        Containers::Array _array;
};
