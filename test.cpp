#include <iostream>
using namespace std;

int main()
{
    int _size = 5;
    int _capacity = 7;
    int* _data = new int[_capacity];
    for(int i = 0; i < _size; i++) {_data[i] = i;}
    for(int i = 0; i < _size; i++) {cout << _data[i] << " ";}
    _size++;
    int pos = 3;
    cout << endl;

    _capacity *= 2;
    int* newData = new int[_capacity];
    memcpy(&newData[0], &_data[0], sizeof(int) * pos);
    newData[pos] = 10;
    memcpy(&newData[pos + 1], &_data[pos], sizeof(int) * (_size - 1 - pos));
    for(int i = 0; i < _size; i++) {cout << newData[i] << " ";}
    delete _data;
    delete newData;
}
