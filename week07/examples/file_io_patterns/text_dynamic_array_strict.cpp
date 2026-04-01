// Динамичен масив от обекти БЕЗ конструктор по подразбиране (StrictRecord).
// `new StrictRecord[count]` не е валидно без default ctor. Стандартният подход:
// масив от указатели StrictRecord** — `new StrictRecord*[count]`, всеки елемент е
// `new StrictRecord(id, score, name)` след парсване на реда. Освобождаване: за всеки
// `delete arr[i]`, накрая `delete[] arr`.

#include "parse_record_line.h"
#include <fstream>
#include <iostream>

bool saveRecordsText(const char* path, StrictRecord* const* records, size_t count) {
    std::ofstream out(path);
    if (!out.is_open()) {
        return false;
    }
    out << count << '\n';
    for (size_t i = 0; i < count; i++) {
        out << *records[i] << '\n';
    }
    return out.good();
}

// При успех връща масив от указатели (всеки към heap StrictRecord). При грешка — nullptr.
StrictRecord** loadRecordsText(const char* path, size_t& outCount) {
    std::ifstream in(path);
    if (!in.is_open()) {
        outCount = 0;
        return nullptr;
    }
    size_t count = 0;
    in >> count;
    if (!in) {
        outCount = 0;
        return nullptr;
    }
    in.ignore();
    if (count == 0) {
        outCount = 0;
        return nullptr;
    }

    StrictRecord** arr = new StrictRecord*[count];

    for (size_t i = 0; i < count; i++) {
        char line[256];
        in.getline(line, sizeof(line));
        if (!in) {
            for (size_t j = 0; j < i; j++) {
                delete arr[j];
            }
            delete[] arr;
            outCount = 0;
            return nullptr;
        }
        int id = 0;
        double score = 0.0;
        char nameBuf[64] = {};
        if (!parseRecordLine(line, id, score, nameBuf, sizeof(nameBuf))) {
            for (size_t j = 0; j < i; j++) {
                delete arr[j];
            }
            delete[] arr;
            outCount = 0;
            return nullptr;
        }
        arr[i] = new StrictRecord(id, score, nameBuf);
    }

    outCount = count;
    return arr;
}

void destroyStrictRecordPointerArray(StrictRecord** arr, size_t count) {
    if (arr == nullptr) {
        return;
    }
    for (size_t i = 0; i < count; i++) {
        delete arr[i];
    }
    delete[] arr;
}

int main() {
    const size_t count = 2;
    StrictRecord** toSave = new StrictRecord*[count];
    toSave[0] = new StrictRecord(1, 5.5, "Anna");
    toSave[1] = new StrictRecord(2, 6.0, "Boris");

    if (!saveRecordsText("records_strict.txt", toSave, count)) {
        std::cerr << "save failed\n";
        destroyStrictRecordPointerArray(toSave, count);
        return 1;
    }
    destroyStrictRecordPointerArray(toSave, count);

    size_t loadedCount = 0;
    StrictRecord** loaded = loadRecordsText("records_strict.txt", loadedCount);
    if (loaded == nullptr) {
        std::cerr << "load failed\n";
        return 1;
    }

    std::cout << "Loaded " << loadedCount << " StrictRecord records:\n";
    for (size_t i = 0; i < loadedCount; i++) {
        std::cout << *loaded[i] << '\n';
    }
    destroyStrictRecordPointerArray(loaded, loadedCount);
    return 0;
}
