#include <iostream>
#include "Vector.h"


Vector::Vector(const Value* rawArray, const size_t size, float coef)
{
    _size = size;
    _multiplicativeCoef = coef;
    _capacity = size * coef;
    _data = new Value[_capacity];
    for(int i = 0; i < size; i++)
    {
            _data[i] = rawArray[i];
    }
    //_multiplicativeCoef = coef;
}

explicit Vector::Vector(const Vector& other)
: _size(other._size)
, _multiplicativeCoef(other._multiplicativeCoef)
, _capacity(other._size * _multiplicativeCoef)
, _data(new Value[_capacity])
{
    _data = new Value[_capacity];
    for(int i = 0; i < _size; i++)
    {
        _data[i] = other._data[i];
    }
}

Vector& Vector::operator=(const Vector& other)
{
    delete[] _data;
    _size = other._size;
    _multiplicativeCoef = other._multiplicativeCoef;
    _capacity = other._size * _multiplicativeCoef;
    _data = new Value[_capacity];
    for(int i = 0; i < _size; i++)
    {
        _data[i] = other._data[i];
    }
}

explicit Vector::Vector(Vector&& other) noexcept
: _size(other._size)
, _multiplicativeCoef(other._multiplicativeCoef)
, _capacity(other._size * _multiplicativeCoef)
{
    _data = new Value[_capacity];
    for(int i = 0; i < _size; i++)
    {
        _data[i] = other._data[i];
    }
    delete[] other._data;
}

Vector& Vector::operator=(Vector&& other) noexcept
{
    delete[] _data;
    _size = other._size;
    _multiplicativeCoef = other._multiplicativeCoef;
    _capacity = other._size * _multiplicativeCoef;
    _data = new Value[_capacity];
    for(int i = 0; i < _size; i++)
    {
        _data[i] = other._data[i];
    }
    delete[] other._data;
}

Vector::~Vector()
{
    delete[] _data;
}

void Vector::pushBack(const Value& value)
{
    _size += 1;
    if(_size <= _capacity)
    {
        _data[_size - 1] = value;
    }
    else
    {
        _capacity *= _multiplicativeCoef;
        Value* newData = new Value[_capacity];
        for(int i = 0; i < _size - 1; i++)
        {
            newData[i] = _data[i];
        }
        newData[_size - 1] = value;
        delete[] _data;
        _data = newData;
    }
}

void Vector::pushFront(const Value& value)
{
    _size += 1;
    if(_size <= _capacity)
    {
        _data[_size - 1] = value;
    }
    else
    {
        _capacity *= _multiplicativeCoef;
        Value* newData = new Value[_capacity];
        newData[0] = value;
        for(int i = 1; i < _size; i++)
        {
            newData[i] = _data[i - 1];
        }
        delete[] _data;
        _data = newData;
    }
}

void Vector::insert(const Value& value, size_t pos)
{
    _size += 1;
    Value* ptr = new Value[_size];
    for(int i = 0; i < pos; i++)
    {
        ptr[i] = _data[i];
    }
    ptr[pos] = value;
    for(int i = pos + 1; i < _size; i++)
    {
        ptr[i] = _data[i - 1];
    }
}
void Vector::insert(const Value* values, size_t size, size_t pos)
{
    _size += size;
    Value* ptr = new Value[_size];
    for(int i = 0; i < pos; i++)
    {
        ptr[i] = _data[i];
    }
    for(int i = pos; i < pos + size; i++)
    {
        ptr[i] = values[i - pos];
    }
    for(int i = pos + size; i < _size; i++)
    {
        ptr[i] = _data[i - size];
    }
}
void insert(const Vector& vector, size_t pos)
{
    
}

void popBack();
void popFront();