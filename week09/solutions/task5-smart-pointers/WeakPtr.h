#ifndef WEAKPTR_H
#define WEAKPTR_H

#include "SharedPtr.h"
#include <cstddef>

template <typename T> class WeakPtr
{
private:
    ControlBlock<T> *cb;

public:
    WeakPtr() : cb(nullptr)
    {
    }

    WeakPtr(const SharedPtr<T> &other) : cb(other.cb)
    {
        if (cb)
            cb->weak_count++;
    }

    WeakPtr(const WeakPtr &other) : cb(other.cb)
    {
        if (cb)
            cb->weak_count++;
    }

    WeakPtr &operator=(const WeakPtr &other)
    {
        if (this != &other)
        {
            release();
            cb = other.cb;
            if (cb)
                cb->weak_count++;
        }
        return *this;
    }

    WeakPtr &operator=(const SharedPtr<T> &other)
    {
        release();
        cb = other.cb;
        if (cb)
            cb->weak_count++;
        return *this;
    }

    ~WeakPtr()
    {
        release();
    }

    bool expired() const
    {
        return !cb || cb->strong_count == 0;
    }

    SharedPtr<T> lock() const
    {
        if (cb && cb->strong_count > 0)
            return SharedPtr<T>(cb);
        return SharedPtr<T>();
    }

private:
    void release()
    {
        if (!cb)
            return;
        cb->weak_count--;
        if (cb->strong_count == 0 && cb->weak_count == 0)
            delete cb;
        cb = nullptr;
    }
};

#endif
