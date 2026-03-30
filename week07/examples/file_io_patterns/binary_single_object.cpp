// Един обект Record в двоичен файл — write/read на sizeof(Record).

#include "Record.h"
#include <fstream>
#include <iostream>

bool saveRecordBinary(const char* path, const Record& r) {
    std::ofstream out(path, std::ios::binary);
    if (!out.is_open()) {
        return false;
    }
    out.write((const char*)&r, sizeof(Record));
    return out.good();
}

bool loadRecordBinary(const char* path, Record& r) {
    std::ifstream in(path, std::ios::binary);
    if (!in.is_open()) {
        return false;
    }
    in.read((char*)&r, sizeof(Record));
    return in.good();
}

int main() {
    Record r(100, 9.99, "BinaryOne");

    if (!saveRecordBinary("one_record.dat", r)) {
        std::cerr << "write failed\n";
        return 1;
    }

    Record in{};
    if (!loadRecordBinary("one_record.dat", in)) {
        std::cerr << "read failed\n";
        return 1;
    }

    std::cout << in.getId() << ' ' << in.getScore() << ' ' << in.getName() << '\n';
    return 0;
}
