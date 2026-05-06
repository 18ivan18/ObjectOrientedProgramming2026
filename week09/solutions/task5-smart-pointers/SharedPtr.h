#ifndef SHAREDPTR_H
#define SHAREDPTR_H

#include <cstddef>

template <typename T> class WeakPtr;

template <typename T> struct ControlBlock
{
    T *ptr;
    size_t strong_count;
    size_t weak_count;

    ControlBlock(T *p) : ptr(p), strong_count(1), weak_count(0)
    {
    }
};

template <typename T> class SharedPtr
{
private:
    ControlBlock<T> *cb;

    SharedPtr(ControlBlock<T> *block) : cb(block)
    {
        if (cb)
        {
            cb->strong_count++;
        }
    }

public:
    friend class WeakPtr<T>;

    SharedPtr(T *p = nullptr) : cb(p ? new ControlBlock<T>(p) : nullptr)
    {
    }

    SharedPtr(const SharedPtr &other) : cb(other.cb)
    {
        if (cb)
            cb->strong_count++;
    }

    SharedPtr &operator=(const SharedPtr &other)
    {
        if (this != &other)
        {
            release();
            cb = other.cb;
            if (cb)
                cb->strong_count++;
        }
        return *this;
    }

    SharedPtr(SharedPtr &&other) noexcept : cb(other.cb)
    {
        other.cb = nullptr;
    }

    SharedPtr &operator=(SharedPtr &&other) noexcept
    {
        if (this != &other)
        {
            release();
            cb = other.cb;
            other.cb = nullptr;
        }
        return *this;
    }

    ~SharedPtr()
    {
        release();
    }

    T &operator*() const
    {
        return *cb->ptr;
    }
    T *operator->() const
    {
        return cb->ptr;
    }
    T *get() const
    {
        return cb ? cb->ptr : nullptr;
    }

    size_t use_count() const
    {
        return cb ? cb->strong_count : 0;
    }

    operator bool() const
    {
        return get() != nullptr;
    }

    void reset(T *p = nullptr)
    {
        release();
        if (p)
            cb = new ControlBlock<T>(p);
        else
            cb = nullptr;
    }

private:
    void release()
    {
        if (!cb)
            return;
        cb->strong_count--;
        if (cb->strong_count == 0)
        {
            delete cb->ptr;
            cb->ptr = nullptr;
            if (cb->weak_count == 0)
            {
                delete cb;
            }
        }
        cb = nullptr;
    }
};

#endif
