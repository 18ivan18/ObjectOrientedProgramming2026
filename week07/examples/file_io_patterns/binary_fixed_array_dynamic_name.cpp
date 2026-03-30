#include "RecordDynamic.h"
#include "binary_io_dynamic_name.h"
#include <fstream>
#include <iostream>

const size_t N = 3;

bool saveArray(const char* path, const RecordDynamic (&arr)[N]) {
    std::ofstream out(path, std::ios::binary);
    if (!out.is_open()) {
        return false;
    }
    for (size_t i = 0; i < N; i++) {
        if (!writeRecordBinary(out, arr[i])) {
            return false;
        }
    }
    return true;
}

bool loadArray(const char* path, RecordDynamic (&arr)[N]) {
    std::ifstream in(path, std::ios::binary);
    if (!in.is_open()) {
        return false;
    }
    for (size_t i = 0; i < N; i++) {
        if (!readRecordBinary(in, arr[i])) {
            return false;
        }
    }
    return true;
}

int main() {
    RecordDynamic arr[N] = {
        RecordDynamic(1, 1.0, "A"),
        RecordDynamic(2, 2.0, "BB"),
        RecordDynamic(3, 3.0, "Longer name here"),
    };

    if (!saveArray("fixed_array_dynname.dat", arr)) {
        return 1;
    }

    RecordDynamic loaded[N];
    if (!loadArray("fixed_array_dynname.dat", loaded)) {
        return 1;
    }

    for (size_t i = 0; i < N; i++) {
        std::cout << loaded[i].getId() << ' ' << loaded[i].getScore() << ' ' << loaded[i].getName()
                  << '\n';
    }
    return 0;
}
