#include "MemoryBlock.h"
#include <iostream>
#include <utility>
#include <vector>

MemoryBlock makeMemoryBlock() {
    return MemoryBlock(42);
}

int main() {
    std::cout << "=== Copy / move сценарии (упражнение) ===\n\n";

    std::cout << "--- MemoryBlock a(1) ---\n";
    MemoryBlock a(1);

    std::cout << "\n--- MemoryBlock b = a; (lvalue -> copy ctor) ---\n";
    MemoryBlock b = a;

    std::cout << "\n--- MemoryBlock c = MemoryBlock(2); (prvalue) ---\n";
    MemoryBlock c = MemoryBlock(2);

    std::cout << "\n--- MemoryBlock d = std::move(a); ---\n";
    MemoryBlock d = std::move(a);

    std::cout << "\n--- b = makeMemoryBlock(); ---\n";
    b = makeMemoryBlock();

    std::cout << "\n--- b = d; (lvalue -> copy assign) ---\n";
    b = d;

    std::cout << "\n--- b = std::move(d); ---\n";
    b = std::move(d);

    std::cout << "\n=== vector<MemoryBlock> (допълнителен пример) ===\n\n";

    std::vector<MemoryBlock> v;
    v.push_back(MemoryBlock(25));
    v.push_back(MemoryBlock(75));
    v.insert(v.begin() + 1, MemoryBlock(50));

    std::cout << "\n--- край на main ---\n";
    return 0;
}
