#pragma once
#include <stdlib.h>

class IStack
{
public:
    virtual ~IStack() {}
    virtual void push(int) = 0;
    virtual int pop() = 0;
    virtual const int& top() const = 0;
    virtual size_t size() const = 0;
    virtual bool empty() const = 0;
};
