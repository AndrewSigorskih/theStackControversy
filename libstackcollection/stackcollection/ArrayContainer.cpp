#include "ArrayContainer.hpp"

namespace Containers
{
    Array::Array(size_t capacity)
    {
        _capacity = capacity;
        _size = 0;
        _data = new int[capacity];
    }

    Array::Array(const Array& other)
    {
        _size = other._size;
        _capacity = other._capacity;
        _data = new int[_capacity];
        memcpy(_data, other._data, _size * sizeof(int));
    }

    Array& Array::operator=(const Array& other)
    {
        if (this != &other)
        {
            if (_capacity < other._capacity)
            this->reserve(other._capacity);
            _size = other._size;
            _capacity = other._capacity;
            memcpy(_data, other._data, _size * sizeof(int));
        }
        return *this;
    }

    Array::~Array()
    {
        if (_data != nullptr)
            delete[] _data;
    }

    size_t Array::size() const
    {
        return _size;
    }

    size_t Array::capacity() const
    {
        return _capacity;
    }

    bool Array::empty() const
    {
        return (_size == 0);
    }

    void Array::clear()
    {
        _size = 0;
        _capacity = 0;
        delete[] _data;
        _data = nullptr;
    }

    int& Array::operator[](size_t index)
    {
        if (_size <= index)
            throw std::out_of_range("Array index out of range!");
        return _data[index];
    }

    void Array::push_back(int val)
    {
        if (this->empty())
            this->reserve(5);

        if (_size == _capacity)
            this->reserve(_capacity * 1.5);
        
        _data[_size++] = val;
    }

    void Array::push_front(int val)
    {
        if (this->empty())
            this->reserve(5);

        if (_size == _capacity)
            reserve(_capacity * 1.5);

        for (size_t idx = _size; idx > 0; idx--)
        {
            _data[idx] = _data[idx-1];
        }

        _data[0] = val;
        _size++;
    }

    const int& Array::back() const
    {
        if (this->empty())
            throw std::out_of_range("Trying to access an element from an empty Array!");

        return _data[_size-1];
    }

    const int& Array::front() const
    {
        if (this->empty())
            throw std::out_of_range("Trying to access an element from an empty Array!");

        return _data[0];
    }

    int Array::pop_back()
    {
        if (this->empty())
            throw std::out_of_range("Trying to pop from an empty Array!");

        _size--;
        int val = _data[_size];
        if (_capacity > _size*2)
            this->shrink_to_fit(_capacity / 2);
        return val;
    }

    int Array::pop_front()
    {
        if (this->empty())
            throw std::out_of_range("Trying to pop from an empty Array!");
        
        _size--;
        int val = _data[0];
        for (size_t idx = 0; idx < _size; idx++)
        {
            _data[idx] = _data[idx+1];
        }
        if (_capacity > _size*2)
            this->shrink_to_fit(_capacity / 2);
        return val;
    }

    void Array::reserve(size_t new_capacity)
    {
        if (new_capacity <= _capacity)
            return;
        
        int* new_data = new int[new_capacity];
        if (!this->empty())
        {
            memcpy(new_data, _data, _size * sizeof(int));
            delete[] _data;
        }

        _data = new_data;
        _capacity = new_capacity;
    }

    void Array::shrink_to_fit(size_t new_capacity)
    {
        if (new_capacity >= _capacity)
            return;

        int* new_data = nullptr;
        if (new_capacity > 0)
        {
            new_data = new int[new_capacity];
            memcpy(new_data, _data, new_capacity * sizeof(int));
        }
        delete[] _data;
        _data = new_data;
        _capacity = new_capacity;
        if (_size > new_capacity)
            _size = new_capacity;
    }
}
