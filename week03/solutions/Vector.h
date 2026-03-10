#ifndef VECTOR_H
#define VECTOR_H

#include <cstddef>

class Vector
{
private:
    int *data;
    size_t size;
    size_t capacity;

    bool resize(size_t newCapacity);

public:
    Vector(size_t initialCapacity = 4);
    ~Vector();

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
