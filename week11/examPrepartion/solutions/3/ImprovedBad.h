#ifndef IMPROVED_BAG_H
#define IMPROVED_BAG_H

#include "Bag.h"
#include "../../../utils/String.h"

template <typename T>
class ImprovedBag : public Bag<T> {
    String manufacturer;

public:
    explicit ImprovedBag(const char* manufacturer);

    // Big Six is compiler-generated:
    //   copy ctor  → calls Bag<T>(const Bag<T>&) (new ID) + copies manufacturer
    //   copy op=   → calls Bag<T>::operator=(const Bag<T>&) (keeps ID) + copies manufacturer
    //   move ctor  → calls Bag<T>(Bag<T>&&) (takes source ID) + moves manufacturer
    //   move op=   → calls Bag<T>::operator=(Bag<T>&&) + moves manufacturer
    //   destructor → trivial; bases/members destruct automatically

    // Inserts x at position i (clamped to [0, size]).
    // All elements at index i and beyond shift one position toward the top.
    void Insert(const T& x, int pos);
};

template <typename T>
ImprovedBag<T>::ImprovedBag(const char* manufacturer) : manufacturer(manufacturer) {}

template <typename T>
void ImprovedBag<T>::Insert(const T& x, int pos) {
    std::size_t size = this->data.getSize();

    std::size_t i;
    if (pos < 0) {
        i = 0;
    } else if (static_cast<std::size_t>(pos) >= size) {
        i = size;
    } else {
        i = static_cast<std::size_t>(pos);
    }

    // Grow the storage by appending a placeholder, then shift right to open slot i.
    this->data.pushBack(x);
    for (std::size_t j = size; j > i; j--) {
        this->data[j] = this->data[j - 1];
    }
    this->data[i] = x;
}

#endif
