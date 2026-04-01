// Текстов файл: брой записи + редове; при зареждане new Record[n] (същият формат като при фиксиран MAX — само буферът е друг).

#include <fstream>
#include <iostream>
#include "Record.h"

bool saveRecords(const char* path, const Record* records, size_t count) {
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

bool loadRecords(const char* path, Record*& outRecords, size_t& outCount) {
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

    Record* arr = new Record[n];
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
    const size_t count = 3;
    Record* data = new Record[count]{
        Record(10, 4.5, "First"),
        Record(20, 5.0, "Second"),
        Record(30, 5.5, "Third"),
    };

    if (!saveRecords("records.txt", data, count)) {
        std::cerr << "save failed\n";
        delete[] data;
        return 1;
    }
    delete[] data;

    Record* loaded = nullptr;
    size_t loadedCount = 0;
    if (!loadRecords("records.txt", loaded, loadedCount)) {
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
