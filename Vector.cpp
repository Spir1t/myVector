#include <iostream>
#include "Vector.h"


Vector::Vector(const Value* rawArray, const size_t size, float coef)
:_size(size)
, _multiplicativeCoef(coef)
, _capacity(size * coef)
,_data(new Value[_capacity])
{
    memcpy(&_data[0], &rawArray[0], size);
    /*
    _size = size;
    _multiplicativeCoef = coef;
    _capacity = size * coef;
    _data = new Value[_capacity];
    */
    /*
    for(int i = 0; i < size; i++)
    {
            _data[i] = rawArray[i];
    }
    */
}

Vector::Vector(const Vector& other)
: _size(other._size)
, _multiplicativeCoef(other._multiplicativeCoef)
, _capacity(other._size * _multiplicativeCoef)
, _data(new Value[_capacity])
{
    memcpy(&_data[0], &other._data[0], _size);
}

Vector& Vector::operator=(const Vector& other)
{
    delete[] _data;
    _size = other._size;
    _multiplicativeCoef = other._multiplicativeCoef;
    _capacity = other._size * _multiplicativeCoef;
    _data = new Value[_capacity];
    memcpy(&_data[0], &other._data[0], _size);
    return(*this);
}

Vector::Vector(Vector&& other) noexcept
: _size(other._size)
, _multiplicativeCoef(other._multiplicativeCoef)
, _capacity(other._size * _multiplicativeCoef)
{
    _data = new Value[_capacity];
    //for(int i = 0; i < _size; i++)
    //{
      //  _data[i] = other._data[i];
    //}
    _data = other._data;
    delete[] other._data;
}

Vector& Vector::operator=(Vector&& other) noexcept
{
    delete[] _data;
    _size = other._size;
    _multiplicativeCoef = other._multiplicativeCoef;
    _capacity = other._size * _multiplicativeCoef;
    _data = new Value[_capacity];
    _data = other._data;
    delete[] other._data;
    return(*this);
}

Vector::~Vector()
{
    delete[] _data;
}

void Vector::pushBack(const Value& value)
{
    _size += 1;
    if(_size < _capacity)
    {
        _data[_size - 1] = value;
    }
    else
    {
        _capacity *= _multiplicativeCoef;
        Value* newData = new Value[_capacity];
        memcpy(&newData[0], &_data[0], _size - 1);
        newData[_size - 1] = value;
        delete[] _data;
        _data = newData;
    }
}

void Vector::pushFront(const Value& value)
{
    _size += 1;
    if(_size < _capacity)
    {
        _data[_size - 1] = value;
    }
    else
    {
        _capacity *= _multiplicativeCoef;
        Value* newData = new Value[_capacity];
        newData[0] = value;
        memcpy(&newData[1], &_data[0], _size - 1);
        delete[] _data;
        _data = newData;
    }
}

void Vector::insert(const Value& value, size_t pos)
{
    _size++;
    if(_size < _capacity)
    {
        memcpy(&_data[pos + 1], &_data[pos], sizeof(Value) * (_size - 1 - pos));
        _data[pos] = value;
    }
    else
    {
        _capacity *= _multiplicativeCoef;
        Value* newData = new Value[_capacity];
        memcpy(&newData[0], &_data[0], sizeof(Value) * pos);
        newData[pos] = value;
        memcpy(&newData[pos + 1], &_data[pos], sizeof(Value) * (_size - 1 - pos));
        delete[] _data;
        _data = newData;
    }
}
void Vector::insert(const Value* values, size_t size, size_t pos)
{
    _size += size;
    if(_size < _capacity)
    {
        memcpy(&_data[pos + size], &_data[pos], sizeof(Value) * (_size - 1 - pos));
        memcpy(&_data[pos], &values[0], sizeof(Value) * (size));
    }
    else
    {
        _capacity *= _multiplicativeCoef;
        Value* newData = new Value[_capacity];
        memcpy(&newData[0], &_data[0], sizeof(Value) * pos);
        memcpy(&newData[pos], &values[0], sizeof(Value) * size);
        memcpy(&newData[pos + size], &_data[pos], sizeof(Value) * (size - 1 - pos));
        delete[] _data;
        _data = newData;
    }
}

void Vector::insert(const Vector& vector, size_t pos)
{
    Vector::insert(vector._data, vector._size, pos);
}

void Vector::popBack()
{
    _size--;
    delete &_data[_size - 1];
}

void Vector::popFront()
{
    _size--;
    delete &_data[0];
    memmove(&_data[0], &_data[1], sizeof(Value) * _size);
}

void Vector::erase(size_t pos, size_t count)
{
    for(int i = 0; i < count; i++)
    {
        delete &_data[pos + i];
    }
    memmove(&_data[pos], &_data[pos + count], sizeof(int) * (_size - pos - count));
    _size -= count;
}

void Vector::eraseBetween(size_t beginPos, size_t endPos)
{
    int count = endPos - beginPos + 1;
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
    return _multiplicativeCoef;
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
        memcpy(&newData[0], &_data[0], _size);
        delete[] _data;
        _data = newData;
        _capacity = capacity;
    }
}

void Vector::shrinkToFit()
{
    for(int i = _size; i < _capacity; i++)
    {
        delete &_data[i];
    }
    _capacity = _size;
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

Vector::Iterator Vector::end() {return Iterator(&_data[_size]);}