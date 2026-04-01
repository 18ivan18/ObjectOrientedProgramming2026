// Текстов файл с RecordDynamic: същият текстов формат като при Record; при зареждане new RecordDynamic[n].

#include <fstream>
#include <iostream>
#include "RecordDynamic.h"


bool saveRecords(const char* path, const RecordDynamic* records, size_t count) {
    std::ofstream out(path);
    if (!out.is_open()) {
        return false;
    }
    out << count << '\n';
    for (size_t i = 0; i < count; i++) {
        out << records[i] << '\n';
    }
    return out.good();
}

bool loadRecords(const char* path, RecordDynamic*& outRecords, size_t& outCount) {
    std::ifstream in(path);
    if (!in.is_open()) {
        return false;
    }
    size_t n = 0;
    in >> n;
    if (!in) {
        return false;
    }
    in.ignore();

    RecordDynamic* arr = new RecordDynamic[n];
    for (size_t i = 0; i < n; i++) {
        in >> arr[i];
        if (!in) {
            delete[] arr;
            return false;
        }
    }
    outRecords = arr;
    outCount = n;
    return true;
}

int main() {
    const size_t count = 2;
    RecordDynamic* data = new RecordDynamic[count]{
        RecordDynamic(10, 4.5, "First"),
        RecordDynamic(20, 5.0, "Second with spaces"),
    };

    if (!saveRecords("records_dynname.txt", data, count)) {
        std::cerr << "save failed\n";
        delete[] data;
        return 1;
    }
    delete[] data;

    RecordDynamic* loaded = nullptr;
    size_t loadedCount = 0;
    if (!loadRecords("records_dynname.txt", loaded, loadedCount)) {
        std::cerr << "load failed\n";
        return 1;
    }

    std::cout << "Loaded " << loadedCount << " records:\n";
    for (size_t i = 0; i < loadedCount; i++) {
        std::cout << loaded[i] << '\n';
    }
    delete[] loaded;
    return 0;
}
