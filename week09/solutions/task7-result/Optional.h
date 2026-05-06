#ifndef OPTIONAL_H
#define OPTIONAL_H

template <typename T> class Optional
{
    T value;
    bool hasValue;

public:
    Optional() : value(T()), hasValue(false)
    {
    }

    Optional(const T &val) : value(val), hasValue(true)
    {
    }

    bool isNone() const
    {
        return !hasValue;
    }

    T getValue() const
    {
        return value;
    }
};

#endif // OPTIONAL_H
