#ifndef TEMPLATE_VECTOR_H
#define TEMPLATE_VECTOR_H

#include <cassert>
#include <ostream>

template <typename T>
class Vector {
private:
    T* data;
    std::size_t size;
    std::size_t capacity;

    bool resize(std::size_t newCapacity) {
        if (newCapacity == capacity) {
            return true;
        }

        T* temp = new (std::nothrow) T[newCapacity];
        if (!temp) {
            return false;
        }

        for (std::size_t i = 0; i < size; i++) {
            temp[i] = data[i];
        }

        delete[] data;
        data = temp;
        capacity = newCapacity;
        return true;
    }

    void copyFrom(const Vector& other) {
        if (other.capacity > capacity) {
            delete[] data;
            capacity = other.capacity;
            data = new T[capacity];
        }

        size = other.size;
        for (std::size_t i = 0; i < size; i++) {
            data[i] = other.data[i];
        }
    }

    void clear() {
        delete[] data;
        data = nullptr;
        size = 0;
        capacity = 0;
    }

public:
    explicit Vector(std::size_t initialCapacity = 4)
        : data(nullptr), size(0), capacity(initialCapacity < 1 ? 1 : initialCapacity) {
        data = new T[capacity];
    }

    Vector(const Vector& other) : data(nullptr), size(0), capacity(other.capacity < 1 ? 1 : other.capacity) {
        data = new T[capacity];
        copyFrom(other);
    }

    Vector& operator=(const Vector& other) {
        if (this != &other) {
            copyFrom(other);
        }
        return *this;
    }

    ~Vector() {
        clear();
    }

    T& operator[](std::size_t position) {
        assert(position < size);
        return data[position];
    }

    const T& operator[](std::size_t position) const {
        assert(position < size);
        return data[position];
    }

    bool operator==(const Vector& other) const {
        if (size != other.size) {
            return false;
        }
        for (std::size_t i = 0; i < size; i++) {
            if (!(data[i] == other.data[i])) {
                return false;
            }
        }
        return true;
    }

    bool operator!=(const Vector& other) const {
        return !(*this == other);
    }

    Vector operator+(const Vector& other) const {
        Vector result(size + other.size);
        result.size = size + other.size;

        for (std::size_t i = 0; i < size; i++) {
            result.data[i] = data[i];
        }
        for (std::size_t i = 0; i < other.size; i++) {
            result.data[size + i] = other.data[i];
        }
        return result;
    }

    Vector& operator+=(const Vector& other) {
        for (std::size_t i = 0; i < other.size; i++) {
            pushBack(other.data[i]);
        }
        return *this;
    }

    friend std::ostream& operator<<(std::ostream& os, const Vector& v) {
        os << "[";
        for (std::size_t i = 0; i < v.size; i++) {
            if (i > 0) {
                os << ", ";
            }
            os << v.data[i];
        }
        os << "]";
        return os;
    }

    std::size_t getCapacity() const {
        return capacity;
    }

    std::size_t getSize() const {
        return size;
    }

    bool isEmpty() const {
        return size == 0;
    }

    const T& getAt(std::size_t position) const {
        assert(position < size);
        return data[position];
    }

    const T& getFirst() const {
        assert(size > 0);
        return data[0];
    }

    const T& getLast() const {
        assert(size > 0);
        return data[size - 1];
    }

    void assign(std::size_t n, const T& x) {
        if (n > capacity) {
            delete[] data;
            capacity = n;
            data = new T[capacity];
        }

        size = n;
        for (std::size_t i = 0; i < n; i++) {
            data[i] = x;
        }
    }

    bool pushBack(const T& x) {
        if (size == capacity) {
            const std::size_t newCap = capacity * 2;
            if (!resize(newCap)) {
                return false;
            }
        }
        data[size++] = x;
        return true;
    }

    bool popBack() {
        if (size == 0) {
            return false;
        }

        size--;
        if (capacity > 4 && size * 4 < capacity) {
            resize(capacity / 2);
        }
        return true;
    }

    bool removeAt(std::size_t position) {
        if (position >= size) {
            return false;
        }

        for (std::size_t i = position; i + 1 < size; i++) {
            data[i] = data[i + 1];
        }
        size--;
        if (capacity > 4 && size * 4 < capacity) {
            resize(capacity / 2);
        }
        return true;
    }
};

#endif

