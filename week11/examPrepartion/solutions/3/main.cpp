#include "Bag.h"
#include "ImprovedBad.h"
#include <iostream>

int main()
{
    // ── Bag: Add / Get / unique IDs ──────────────────────────────────────────
    Bag<int> a, b;
    a.Add(1);
    a.Add(2);
    a.Add(3);
    b.Add(1);
    b.Add(2);
    b.Add(3);

    std::cout << "a id=" << a.getId() << "  b id=" << b.getId() << '\n'; // 0  1

    // operator==
    std::cout << "a == b: " << (a == b) << '\n'; // 1

    // Get pops from top
    std::cout << "a.Get(): " << a.Get() << '\n'; // 3
    std::cout << "a == b: " << (a == b) << '\n'; // 0  (a now has [1,2], b has [1,2,3])

    // ── operator+ ────────────────────────────────────────────────────────────
    // a=[1,2]  b=[1,2,3]
    // result = a's elements in order, then b's elements reversed
    // → [1, 2, 3, 2, 1]
    Bag<int> c = a + b;
    std::cout << "c id=" << c.getId() << "  elements (top-first): ";
    while (!(c == Bag<int>()))
    {
        std::cout << c.Get() << ' ';
    }
    std::cout << '\n'; // 1 2 3 2 1

    // ── Copy semantics ───────────────────────────────────────────────────────
    Bag<int> src;
    src.Add(10);
    src.Add(20);

    Bag<int> copied(src); // copy ctor → new ID
    Bag<int> assigned;
    assigned = src; // copy op=  → keeps own ID

    std::cout << "src id=" << src.getId() << "  copied id=" << copied.getId() << "  assigned id=" << assigned.getId()
              << '\n';

    // ── ImprovedBag: Insert ───────────────────────────────────────────────────
    ImprovedBag<int> bag("Acme");
    bag.Add(10);
    bag.Add(20);
    bag.Add(30); // [10, 20, 30]  (30 = top)

    bag.Insert(99, 1);   // [10, 99, 20, 30]
    bag.Insert(0, -5);   // clamped to 0 → [0, 10, 99, 20, 30]
    bag.Insert(77, 100); // clamped to end → [0, 10, 99, 20, 30, 77]

    std::cout << "ImprovedBag (top-first): ";
    while (!(bag == ImprovedBag<int>("Acme")))
    {
        std::cout << bag.Get() << ' ';
    }
    std::cout << '\n'; // 77 30 20 99 10 0
}
