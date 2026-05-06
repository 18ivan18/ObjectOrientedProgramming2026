#ifndef PAIR_H
#define PAIR_H

template <typename T1, typename T2 = T1> class Pair
{
private:
    T1 first;
    T2 second;

public:
    Pair(const T1 &first, const T2 &second) : first(first), second(second)
    {
    }

    const T1 &getFirst() const
    {
        return first;
    }

    const T2 &getSecond() const
    {
        return second;
    }

    void setFirst(const T1 &value)
    {
        first = value;
    }

    void setSecond(const T2 &value)
    {
        second = value;
    }

    bool operator==(const Pair &other) const
    {
        return first == other.first && second == other.second;
    }

    bool operator!=(const Pair &other) const
    {
        return !(*this == other);
    }
};

#endif // PAIR_H
