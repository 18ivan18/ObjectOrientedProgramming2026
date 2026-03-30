#include "Record.h"
#include <fstream>
#include <iostream>

const size_t N = 4;

bool saveFixedArray(const char* path, const Record (&arr)[N]) {
    std::ofstream out(path, std::ios::binary);
    if (!out.is_open()) {
        return false;
    }
    out.write((const char*)arr, sizeof(arr));
    return out.good();
}

bool loadFixedArray(const char* path, Record (&arr)[N]) {
    std::ifstream in(path, std::ios::binary);
    if (!in.is_open()) {
        return false;
    }
    in.read((char*)arr, sizeof(arr));
    return in.good();
}

int main() {
    const char* names[N] = {"User0", "User1", "User2", "User3"};
    Record arr[N];
    for (size_t i = 0; i < N; i++) {
        arr[i] = Record(static_cast<int>(i + 1), 3.0 + static_cast<double>(i), names[i]);
    }

    if (!saveFixedArray("fixed_array.dat", arr)) {
        return 1;
    }

    Record loaded[N]{};
    if (!loadFixedArray("fixed_array.dat", loaded)) {
        return 1;
    }

    for (size_t i = 0; i < N; i++) {
        std::cout << loaded[i].getId() << ' ' << loaded[i].getScore() << ' ' << loaded[i].getName()
                  << '\n';
    }
    return 0;
}
