#ifndef MATRIX_H
#define MATRIX_H

#include <cassert>
#include <cstddef>
#include <iostream>

template <typename T> class Matrix
{
private:
    T **data;
    std::size_t rows;
    std::size_t cols;

    void allocate(std::size_t r, std::size_t c)
    {
        rows = r;
        cols = c;
        if (r == 0 || c == 0)
        {
            data = nullptr;
            rows = 0;
            cols = 0;
            return;
        }
        data = new T *[rows];
        for (std::size_t i = 0; i < rows; i++)
        {
            data[i] = new T[cols]();
        }
    }

    void copyFrom(const Matrix &other)
    {
        allocate(other.rows, other.cols);
        for (std::size_t i = 0; i < rows; i++)
        {
            for (std::size_t j = 0; j < cols; j++)
            {
                data[i][j] = other.data[i][j];
            }
        }
    }

    void free()
    {
        for (std::size_t i = 0; i < rows; i++)
        {
            delete[] data[i];
        }
        delete[] data;
        data = nullptr;
        rows = 0;
        cols = 0;
    }

public:
    Matrix() : data(nullptr), rows(0), cols(0)
    {
    }

    Matrix(std::size_t rows, std::size_t cols) : data(nullptr), rows(0), cols(0)
    {
        allocate(rows, cols);
    }

    Matrix(const Matrix &other) : data(nullptr), rows(0), cols(0)
    {
        copyFrom(other);
    }

    Matrix &operator=(const Matrix &other)
    {
        if (this != &other)
        {
            free();
            copyFrom(other);
        }
        return *this;
    }

    Matrix(Matrix &&other) : data(other.data), rows(other.rows), cols(other.cols)
    {
        other.data = nullptr;
        other.rows = 0;
        other.cols = 0;
    }

    Matrix &operator=(Matrix &&other)
    {
        if (this != &other)
        {
            free();
            data = other.data;
            rows = other.rows;
            cols = other.cols;
            other.data = nullptr;
            other.rows = 0;
            other.cols = 0;
        }
        return *this;
    }

    ~Matrix()
    {
        free();
    }

    std::size_t getRows() const
    {
        return rows;
    }

    std::size_t getCols() const
    {
        return cols;
    }

    void setElement(std::size_t i, std::size_t j, T element)
    {
        assert(i < rows && j < cols);
        data[i][j] = element;
    }

    const T &getElement(std::size_t i, std::size_t j) const
    {
        assert(i < rows && j < cols);
        return data[i][j];
    }

    Matrix operator+(const Matrix &other) const
    {
        if (rows != other.rows || cols != other.cols)
        {
            std::cerr << "Matrix::operator+: dimension mismatch (" << rows << "x" << cols << " + " << other.rows << "x"
                      << other.cols << ")\n";
            return Matrix();
        }
        Matrix result(rows, cols);
        for (std::size_t i = 0; i < rows; i++)
        {
            for (std::size_t j = 0; j < cols; j++)
            {
                result.data[i][j] = data[i][j] + other.data[i][j];
            }
        }
        return result;
    }

    Matrix operator*(const Matrix &other) const
    {
        if (cols != other.rows)
        {
            std::cerr << "Matrix::operator*: dimension mismatch (" << rows << "x" << cols << " * " << other.rows << "x"
                      << other.cols << ")\n";
            return Matrix();
        }
        Matrix result(rows, other.cols);
        for (std::size_t i = 0; i < rows; i++)
        {
            for (std::size_t k = 0; k < cols; k++)
            {
                for (std::size_t j = 0; j < other.cols; j++)
                {
                    result.data[i][j] = result.data[i][j] + data[i][k] * other.data[k][j];
                }
            }
        }
        return result;
    }

    void print(std::ostream &os) const
    {
        for (std::size_t i = 0; i < rows; i++)
        {
            for (std::size_t j = 0; j < cols; j++)
            {
                if (j > 0)
                {
                    os << " ";
                }
                os << data[i][j];
            }
            os << "\n";
        }
    }

    friend std::ostream &operator<<(std::ostream &os, const Matrix &m)
    {
        m.print(os);
        return os;
    }
};

#endif // MATRIX_H
