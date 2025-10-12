#include "ListContainer.hpp"

namespace Containers
{
    List::List(const List& other)
    {
        this->_copy_from_other(other);
    }

    List& List::operator=(const List& other)
    {
        if (this != &other)
        {
            this->clear();
            this->_copy_from_other(other);
        }
        return *this;
    }

    List::~List()
    {
        this-> clear();
    }

    size_t List::size() const
    {
        return _size;
    }

    bool List::empty() const
    {
        return (_size == 0);
    }

    void List::clear()
    {
        _size = 0;
        _ListNode* curr = _head;
        while (curr != nullptr)
        {
            _ListNode* next = curr->next;
            delete curr;
            curr = next;
        }
        _head = nullptr;
        _tail = nullptr;
    }

    void List::push_back(int val)
    {
        auto newnode = new _ListNode(val);
        if (this->empty())
        {
            _head = newnode;
            _tail = newnode;
        } else {
            _tail->next = newnode;
            newnode->prev = _tail;
            _tail = newnode;
        }
        _size++;
    }

    void List::push_front(int val)
    {
        auto newnode = new _ListNode(val);
        if (this->empty())
        {
            _head = newnode;
            _tail = newnode;
        } else {
            newnode->next = _head;
            _head->prev = newnode;
            _head = newnode;
        }
        _size++;
    }

    const int& List::back() const
    {
        if (this->empty())
            throw std::out_of_range("Trying to access an element from an empty List!");

        return _tail->data;
    }
    
    const int& List::front() const
    {
        if (this->empty())
            throw std::out_of_range("Trying to access an element from an empty List!");
        
        return _head->data;
    }

    int List::pop_back()
    {
        if (this->empty())
            throw std::out_of_range("Trying to pop from an empty List!");

        int val = _tail->data;
        if (_size == 1)
        {
            this->clear();
        } else {
            auto new_tail = _tail->prev;
            new_tail->next = nullptr;
            delete _tail;
            _tail = new_tail;
            _size--;
        }
        return val;
    }

    int List::pop_front()
    {
        if (this->empty())
            throw std::out_of_range("Trying to pop from an empty List!");

        int val = _head->data;
        if (_size == 1)
        {
            this->clear();
        } else {
            auto new_head = _head->next;
            new_head->prev = nullptr;
            delete _head;
            _head = new_head;
            _size--;
        }
        return val;
    }

    void List::_copy_from_other(const List& other)
    {
        _size = other._size;
        auto curr_source = other._head;
        auto curr_dest = _head;
        while (curr_source != nullptr)
        {
            auto new_node = new _ListNode(curr_source->data);
            new_node->prev = curr_dest;

            if (curr_dest == nullptr)
            {
                _head = new_node;
            } else {
                curr_dest->next = new_node;
            }
            curr_dest = new_node;
            curr_source = curr_source->next;
        }
        _tail = curr_dest;
    }
}
