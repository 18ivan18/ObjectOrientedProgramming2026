#ifndef BAG_H
#define BAG_H

#include "../../../utils/Vector.h"

template <typename T> class Bag
{
    static int nextId;
    int id;

protected:
    Vector<T> data;

public:
    Bag();
    Bag(const Bag<T> &other);
    Bag<T> &operator=(const Bag<T> &other);
    Bag(Bag<T> &&other);
    Bag<T> &operator=(Bag<T> &&other);
    virtual ~Bag() = default;

    void Add(const T &x);
    T Get();

    bool operator==(const Bag<T> &other) const;

    template <typename U> friend Bag<U> operator+(const Bag<U> &a, const Bag<U> &b);

    int getId() const;
};

template <typename T> int Bag<T>::nextId = 0;

template <typename T> Bag<T>::Bag() : id(nextId++), data()
{
}

// Copy gets a fresh ID; only the contents are duplicated.
template <typename T> Bag<T>::Bag(const Bag<T> &other) : id(nextId++), data(other.data)
{
}

// Assignment keeps the existing ID; only contents are replaced.
template <typename T> Bag<T> &Bag<T>::operator=(const Bag<T> &other)
{
    if (this != &other)
    {
        data = other.data;
    }
    return *this;
}

// Move takes the source's ID; the source gets a new one.
template <typename T> Bag<T>::Bag(Bag<T> &&other) : id(other.id), data(std::move(other.data))
{
    other.id = nextId++;
}

template <typename T> Bag<T> &Bag<T>::operator=(Bag<T> &&other)
{
    if (this != &other)
    {
        data = std::move(other.data);
    }
    return *this;
}

template <typename T> void Bag<T>::Add(const T &x)
{
    data.pushBack(x);
}

// Returns and removes the top element (LIFO).
template <typename T> T Bag<T>::Get()
{
    T top = data.getLast();
    data.popBack();
    return top;
}

template <typename T> bool Bag<T>::operator==(const Bag<T> &other) const
{
    if (data.getSize() != other.data.getSize())
    {
        return false;
    }
    for (std::size_t i = 0; i < data.getSize(); i++)
    {
        if (!(data[i] == other.data[i]))
        {
            return false;
        }
    }
    return true;
}

template <typename T> int Bag<T>::getId() const
{
    return id;
}

// First bag's elements in their original order (bottom to top),
// then second bag's elements in reverse order (top to bottom).
template <typename U> Bag<U> operator+(const Bag<U> &a, const Bag<U> &b)
{
    Bag<U> result;
    for (std::size_t i = 0; i < a.data.getSize(); i++)
    {
        result.Add(a.data[i]);
    }
    for (std::size_t i = b.data.getSize(); i > 0; i--)
    {
        result.Add(b.data[i - 1]);
    }
    return result;
}

#endif
