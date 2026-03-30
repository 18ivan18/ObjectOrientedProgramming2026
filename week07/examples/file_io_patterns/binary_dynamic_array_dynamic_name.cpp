#include "RecordDynamic.h"
#include "binary_io_dynamic_name.h"
#include <fstream>
#include <iostream>

bool saveDynamicArray(const char* path, const RecordDynamic* arr, size_t count) {
    std::ofstream out(path, std::ios::binary);
    if (!out.is_open()) {
        return false;
    }
    out.write((const char*)&count, sizeof(count));
    for (size_t i = 0; i < count; i++) {
        if (!writeRecordBinary(out, arr[i])) {
            return false;
        }
    }
    return out.good();
}

bool loadDynamicArray(const char* path, RecordDynamic*& outArr, size_t& outCount) {
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
    RecordDynamic* arr = new RecordDynamic[count];
    for (size_t i = 0; i < count; i++) {
        if (!readRecordBinary(in, arr[i])) {
            delete[] arr;
            return false;
        }
    }
    outArr = arr;
    outCount = count;
    return true;
}

int main() {
    const size_t count = 2;
    RecordDynamic* data = new RecordDynamic[count]{
        RecordDynamic(7, 1.0, "DynA"),
        RecordDynamic(8, 2.0, "DynB extended"),
    };

    if (!saveDynamicArray("dynamic_array_dynname.dat", data, count)) {
        delete[] data;
        return 1;
    }
    delete[] data;

    RecordDynamic* loaded = nullptr;
    size_t n = 0;
    if (!loadDynamicArray("dynamic_array_dynname.dat", loaded, n)) {
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
