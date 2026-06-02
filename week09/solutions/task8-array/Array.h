#ifndef ARRAY_H
#define ARRAY_H

#include <cstddef>
#include <iostream>

template <typename T, size_t N>
class Array
{
    T data[N];

public:
    Array()
    {
        for (size_t i = 0; i < N; i++)
        {
            data[i] = T();
        }
    }

    T &operator[](size_t i)
    {
        return data[i];
    }

    const T &operator[](size_t i) const
    {
        return data[i];
    }

    size_t size() const
    {
        return N;
    }

    void print() const
    {
        std::cout << "[";
        for (size_t i = 0; i < N; i++)
        {
            std::cout << data[i];
            if (i < N - 1)
            {
                std::cout << ", ";
            }
        }
        std::cout << "]\n";
    }
};

// -----------------------------------------------------------------------
// Free function templates — algorithms on Array<T, N>
// -----------------------------------------------------------------------

template <typename T, size_t N>
T min(const Array<T, N> &arr)
{
    T result = arr[0];
    for (size_t i = 1; i < N; i++)
    {
        if (arr[i] < result)
        {
            result = arr[i];
        }
    }
    return result;
}

template <typename T, size_t N>
T max(const Array<T, N> &arr)
{
    T result = arr[0];
    for (size_t i = 1; i < N; i++)
    {
        if (arr[i] > result)
        {
            result = arr[i];
        }
    }
    return result;
}

template <typename T, size_t N>
T sum(const Array<T, N> &arr)
{
    T result = T();
    for (size_t i = 0; i < N; i++)
    {
        result = result + arr[i];
    }
    return result;
}

template <typename T, size_t N>
int find(const Array<T, N> &arr, const T &value)
{
    for (size_t i = 0; i < N; i++)
    {
        if (arr[i] == value)
        {
            return static_cast<int>(i);
        }
    }
    return -1;
}

// Selection sort
template <typename T, size_t N>
void sort(Array<T, N> &arr)
{
    for (size_t i = 0; i < N - 1; i++)
    {
        size_t minIdx = i;
        for (size_t j = i + 1; j < N; j++)
        {
            if (arr[j] < arr[minIdx])
            {
                minIdx = j;
            }
        }
        if (minIdx != i)
        {
            T temp = arr[i];
            arr[i] = arr[minIdx];
            arr[minIdx] = temp;
        }
    }
}

template <typename T, size_t N>
void reverse(Array<T, N> &arr)
{
    for (size_t i = 0; i < N / 2; i++)
    {
        T temp = arr[i];
        arr[i] = arr[N - 1 - i];
        arr[N - 1 - i] = temp;
    }
}

#endif // ARRAY_H
