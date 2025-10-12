#pragma once
#include <stdlib.h>
#include <cstring>
#include <stdexcept>

namespace Containers
{
    class Array
    {
    public:
        Array() : _size(0), _capacity(0), _data(nullptr) {}
        Array(size_t);
        Array(const Array&);
        Array& operator=(const Array&);
        ~Array();

        size_t size() const;
        size_t capacity() const;
        bool empty() const;
        void clear();
        int& operator[](size_t);
        
        void push_back(int);
        void push_front(int);
        const int& back() const;
        const int& front() const;
        int pop_back();
        int pop_front();

        void reserve(size_t);
        void shrink_to_fit(size_t);

    private:
        size_t _size;
        size_t _capacity;
        int* _data;
    };
} // namespace Containers
