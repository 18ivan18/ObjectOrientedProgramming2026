#include "Record.h"
#include <fstream>
#include <iostream>

bool saveDynamicArray(const char* path, const Record* arr, size_t count) {
    std::ofstream out(path, std::ios::binary);
    if (!out.is_open()) {
        return false;
    }
    out.write((const char*)&count, sizeof(count));
    if (count > 0) {
        out.write((const char*)arr, count * sizeof(Record));
    }
    return out.good();
}

bool loadDynamicArray(const char* path, Record*& outArr, size_t& outCount) {
    std::ifstream in(path, std::ios::binary);
    if (!in.is_open()) {
        return false;
    }
    size_t count = 0;
    in.read((char*)&count, sizeof(count));
    if (!in) {
        return false;
    }
    if (count == 0) {
        outArr = nullptr;
        outCount = 0;
        return true;
    }
    Record* arr = new Record[count];
    in.read((char*)arr, count * sizeof(Record));
    if (!in) {
        delete[] arr;
        return false;
    }
    outArr = arr;
    outCount = count;
    return true;
}

int main() {
    const size_t count = 2;
    Record* data = new Record[count]{
        Record(7, 1.0, "DynA"),
        Record(8, 2.0, "DynB"),
    };

    if (!saveDynamicArray("dynamic_array.dat", data, count)) {
        delete[] data;
        return 1;
    }
    delete[] data;

    Record* loaded = nullptr;
    size_t n = 0;
    if (!loadDynamicArray("dynamic_array.dat", loaded, n)) {
        return 1;
    }

    std::cout << "count = " << n << '\n';
    for (size_t i = 0; i < n; i++) {
        std::cout << loaded[i].getId() << ' ' << loaded[i].getScore() << ' ' << loaded[i].getName()
                  << '\n';
    }
    delete[] loaded;
    return 0;
}
