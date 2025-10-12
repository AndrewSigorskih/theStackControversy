#pragma once
#include <stdlib.h>
#include <stdexcept>

namespace Containers
{
    struct _ListNode
    {
        _ListNode(int __val): data(__val) {}
        ~_ListNode() {}

        _ListNode* prev = nullptr;
        _ListNode* next = nullptr;
        int data;
    };

    class List
    {
    public:
        List() : _size(0), _head(nullptr), _tail(nullptr) {}
        List(const List&);
        List& operator=(const List&);
        ~List();

        size_t size() const;
        bool empty() const;
        void clear();

        void push_back(int);
        void push_front(int);
        const int& back() const;
        const int& front() const;
        int pop_back();
        int pop_front();

    private:
        void _copy_from_other(const List&);

    private:
        size_t _size = 0u;
        _ListNode* _head = nullptr;
        _ListNode* _tail = nullptr;
    };
} // namespace Containers
