#include <iostream>
#include <cstring>
#include "Vector.h"


Vector::Vector(const Value* rawArray, const size_t size, float coef)
:_size(size)
, _multiplicativeCoef(coef)
, _capacity(size * coef)
{
    _data = new Value[_capacity];
    memcpy(&_data[0], &rawArray[0], size * sizeof(Value));
}

Vector::Vector(const Vector& other)
: _size(other._size)
, _multiplicativeCoef(other._multiplicativeCoef)
, _capacity(other._size * other._multiplicativeCoef)
{
    _data = new Value[_capacity];
    memcpy(_data, other._data, _size * sizeof(Value));
}

Vector& Vector::operator=(const Vector& other)
{
    if (this == &other)
    {
        return(*this);
    }
    _size = other._size;
    _multiplicativeCoef = other._multiplicativeCoef;
    _capacity = other._size;
    delete[] _data;
    _data = new Value[_capacity];
    memcpy(_data, other._data, _size * sizeof(Value));
    return(*this);
}

Vector::Vector(Vector&& other) noexcept
{
    _data = other._data;
    _multiplicativeCoef = other._multiplicativeCoef;
    _capacity = other._capacity;
    _size = other._size;

    other._data = nullptr;
    other._capacity = 0;
    other._size = 0;
}

Vector& Vector::operator=(Vector&& other) noexcept
{
    if(this == &other)
    {
        return(*this);
    }
    _size = other._size;
    _multiplicativeCoef = other._multiplicativeCoef;
    _capacity = other._capacity;
    delete[] _data;

    _data = other._data;
    other._data = nullptr;
    other._capacity = 0;
    return(*this);
}

Vector::~Vector()
{
    delete[] _data;
}

void Vector::pushBack(const Value &value) {
    if(_capacity == 0)
    {
        reserve(_multiplicativeCoef);
    }

    else if(_size == _capacity) 
    {
        reserve(_capacity * _multiplicativeCoef);
    }

    _data[_size] = value;
    _size++;
}

void Vector::pushFront(const Value& value)
{
    if(_capacity == 0)
    {
        reserve(_multiplicativeCoef);
    }
    
    else if(_size == _capacity)
    {
        reserve(_capacity * _multiplicativeCoef);
    }

    memmove(&_data[1], _data, _size * sizeof(Value));
    _data[0] = value;
    _size++;
}

void Vector::insert(const Value& value, size_t pos)
{
    if(pos > _size)
    {
        throw std::out_of_range("Incorrect pos");
    }
    
    if(_size == _capacity)
    {
        reserve(_capacity * _multiplicativeCoef);
    }
    memmove(&_data[pos + 1], &_data[pos], (_size - pos) * sizeof(Value));
    _data[pos] = value;
    _size++;
}

void Vector::insert(const Value* values, size_t size, size_t pos)
{
    if(pos > _size)
    {
        throw std::out_of_range("incorrect pos");
    }

    if(values == nullptr)
    {
        throw std::out_of_range("Incorrect values");
    }

    if(_size + size >= _capacity)
    {
        reserve((_size + size) * _multiplicativeCoef);
    }
    memmove(&_data[pos + size], &_data[pos], sizeof(Value) * (_size - pos));
    memcpy(&_data[pos], values, sizeof(Value) * size);
    _size += size;
}

void Vector::insert(const Vector& vector, size_t pos)
{
    Vector::insert(vector._data, vector._size, pos);
}

void Vector::popBack()
{
    if (_size == 0)
    {
        throw(std::out_of_range("Nothing to pop"));
    }
    else
    {
        _size--;
    }
}

void Vector::popFront()
{
    if (_size == 0)
    {
        throw(std::out_of_range("Nothing to pop"));
    }
    else
    {
        _size--;
        memmove(&_data[0], &_data[1], sizeof(Value) * _size);
    }
}

void Vector::erase(size_t pos, size_t count)
{
    if(pos + count > _size)
    {
        count = _size - pos;
    }
    if(pos < 0 || count < 0)
    {
        return;
    }
    memmove(&_data[pos], &_data[pos + count], sizeof(Value) * (_size - pos - count));
    _size -= count;
}

void Vector::eraseBetween(size_t beginPos, size_t endPos)
{
    if(beginPos < endPos)
    {
        return;
    }
    int count = endPos - beginPos;
    erase(beginPos, count);
}

size_t Vector::size() const
{
    return _size;
}

size_t Vector::capacity() const
{
    return _capacity;
}

double Vector::loadFactor() const
{
    return ((double) _size /  _capacity);
}

Value& Vector::operator[](size_t idx)
{
    return _data[idx];
}

const Value& Vector::operator[](size_t idx) const
{
    return _data[idx];
}

long long Vector::find(const Value& value) const
{
    long long i = 0;
    for(; i < _size; i++)
    {
        if(_data[i] == value)
        {
            return i;
        }
    }
    return i;
}

void Vector::reserve(size_t capacity)
{
    if(capacity > _capacity)
    {
        Value* newData = new Value[capacity];
        for (int i = 0; i < _size; i++) {
            newData[i] = _data[i];
        }
        delete _data;

        _capacity = capacity;
        _data = newData;
    }
}

void Vector::shrinkToFit()
{
    if(_size < _capacity)
    {
            Value* newData = new Value[_size];
            for(int i = 0; i < _size; i++)
            {
                newData[i] = _data[i];
            }
            delete[] _data;
            _data = newData;
            _capacity = _size;
    }
}

Vector::Iterator::Iterator(Value* ptr): _ptr(ptr) {}

Value& Vector::Iterator::operator*() {return *_ptr;}

const Value& Vector::Iterator::operator*() const {return *_ptr;}

Value* Vector::Iterator::operator->() {return _ptr;}

const Value* Vector::Iterator::operator->() const {return _ptr;}

Vector::Iterator Vector::Iterator::operator++() {_ptr++; return *this;}

Vector::Iterator Vector::Iterator::operator++(int) {Iterator tmp = *this; ++(*this); return tmp;}

bool Vector::Iterator::operator==(const Iterator& other) const {return((_ptr == other._ptr) ? true : false);}
    
bool Vector::Iterator::operator!=(const Iterator& other) const {return((_ptr != other._ptr) ? true : false);}

Vector::Iterator Vector::begin() {return Iterator(&_data[0]);}

Vector::Iterator Vector::end() {return Iterator(&_data[_size]);}git