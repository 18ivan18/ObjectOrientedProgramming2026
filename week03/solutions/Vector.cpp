#include "Vector.h"
#include <iostream>
#include <cassert>

Vector::Vector(size_t initialCapacity) : data(nullptr), size(0), capacity(initialCapacity)
{
    data = new int[capacity];
}

Vector::~Vector()
{
    delete[] data;
    data = nullptr;
}

bool Vector::resize(size_t newCapacity)
{
    if (newCapacity == capacity)
        return true;
    int *temp = new (std::nothrow) int[newCapacity];
    if (!temp) {
        return false;
    }
    size_t copyCount = size < newCapacity ? size : newCapacity;
    for (size_t i = 0; i < copyCount; i++) {
        temp[i] = data[i];
    }
    delete[] data;
    data = temp;
    capacity = newCapacity;
    if (size > newCapacity) {
        size = newCapacity;
    }
    return true;
}

size_t Vector::getCapacity() const
{
    return capacity;
}

size_t Vector::getSize() const
{
    return size;
}

bool Vector::isEmpty() const
{
    return size == 0;
}

int Vector::getAt(size_t position) const
{
    assert(position < size);
    return data[position];
}

int Vector::getFirst() const
{
    assert(size > 0);
    return data[0];
}

int Vector::getLast() const
{
    assert(size > 0);
    return data[size - 1];
}

void Vector::assign(size_t n, int x)
{
    if (n > capacity)
    {
        delete[] data;
        capacity = n;
        data = new int[capacity];
    }
    size = n;
    for (size_t i = 0; i < n; i++) {
        data[i] = x;
    }
}

bool Vector::pushBack(int x)
{
    if (size == capacity && !resize(capacity * 2)) {
        return false;
    }
    data[size++] = x;
    return true;
}

bool Vector::popBack()
{
    if (size == 0) {
        return false;
    }
    size--;
    if (size * 4 < capacity) {
        resize(capacity / 2);
    }
    return true;
}

bool Vector::removeAt(size_t position)
{
    if (position >= size) {
        return false;
    }
    for (size_t i = position; i < size - 1; i++) {
        data[i] = data[i + 1];
    }
    size--;
    if (size * 4 < capacity) {
        resize(capacity / 2);
    }
    return true;
}
