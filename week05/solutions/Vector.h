#ifndef VECTOR_H
#define VECTOR_H

#include <cstddef>
#include <iostream>

class Vector
{
private:
    int *data;
    size_t size;
    size_t capacity;

    bool resize(size_t newCapacity);
    void copyFrom(const Vector &other);
    void clear();

public:
    Vector(size_t initialCapacity = 4);
    Vector(const Vector &other);
    ~Vector();

    Vector &operator=(const Vector &other);

    int &operator[](size_t position);
    const int &operator[](size_t position) const;

    bool operator==(const Vector &other) const;
    bool operator!=(const Vector &other) const;

    Vector operator+(const Vector &other) const;
    Vector &operator+=(const Vector &other);

    friend std::ostream &operator<<(std::ostream &os, const Vector &v);

    size_t getCapacity() const;
    size_t getSize() const;
    bool isEmpty() const;

    int getAt(size_t position) const;
    int getFirst() const;
    int getLast() const;

    void assign(size_t n, int x);
    bool pushBack(int x);
    bool popBack();
    bool removeAt(size_t position);
};

#endif
