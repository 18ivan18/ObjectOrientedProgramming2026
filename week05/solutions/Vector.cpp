#include "Vector.h"
#include <cassert>

Vector::Vector(size_t initialCapacity) : data(nullptr), size(0), capacity(initialCapacity)
{
    data = new int[capacity];
}

Vector::Vector(const Vector &other) : data(nullptr), size(0), capacity(other.capacity > 4 ? other.capacity : 4)
{
    data = new int[capacity];
    copyFrom(other);
}

Vector::~Vector()
{
    clear();
}

Vector &Vector::operator=(const Vector &other)
{
    if (this != &other)
    {
        clear();
        copyFrom(other);
    }
    return *this;
}

void Vector::copyFrom(const Vector &other)
{
    if (data == nullptr || other.capacity > capacity)
    {
        delete[] data;
        capacity = other.capacity > 4 ? other.capacity : 4;
        data = new int[capacity];
    }
    size = other.size;
    for (size_t i = 0; i < size; i++) {
        data[i] = other.data[i];
    }
}

void Vector::clear()
{
    delete[] data;
    data = nullptr;
    size = 0;
    capacity = 0;
}

bool Vector::resize(size_t newCapacity)
{
    if (newCapacity == capacity) {
        return true;
    }
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

int &Vector::operator[](size_t position)
{
    assert(position < size);
    return data[position];
}

const int &Vector::operator[](size_t position) const
{
    assert(position < size);
    return data[position];
}

bool Vector::operator==(const Vector &other) const
{
    if (size != other.size) {
        return false;
    }
    for (size_t i = 0; i < size; i++) {
        if (data[i] != other.data[i]) {
            return false;
        }
    }
    return true;
}

bool Vector::operator!=(const Vector &other) const
{
    return !(*this == other);
}

Vector Vector::operator+(const Vector &other) const
{
    Vector result(size + other.size);
    result.size = size + other.size;
    for (size_t i = 0; i < size; i++) {
        result.data[i] = data[i];
    }
    for (size_t i = 0; i < other.size; i++) {
        result.data[size + i] = other.data[i];
    }
    return result;
}

Vector &Vector::operator+=(const Vector &other)
{
    for (size_t i = 0; i < other.size; i++) {
        pushBack(other.data[i]);
    }
    return *this;
}

std::ostream &operator<<(std::ostream &os, const Vector &v)
{
    os << "[";
    for (size_t i = 0; i < v.size; i++)
    {
        if (i > 0) {
            os << ", ";
        }
        os << v.data[i];
    }
    os << "]";
    return os;
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
    if (size * 4 < capacity && capacity > 4) {
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
    if (size * 4 < capacity && capacity > 4) {
        resize(capacity / 2);
    }
    return true;
}
