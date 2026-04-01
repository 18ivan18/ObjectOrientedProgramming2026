#pragma once

#include "RecordDynamic.h"
#include <cstring>
#include <fstream>

// Двоичен формат: id, score, дължина на името, байтове на името.
bool writeRecordBinary(std::ofstream& out, const RecordDynamic& r) {
    int id = r.getId();
    double score = r.getScore();
    out.write((const char*)&id, sizeof(id));
    out.write((const char*)&score, sizeof(score));
    const char* nm = r.getName();
    size_t nameLen = 0;
    if (nm != nullptr && nm[0] != '\0') {
        nameLen = std::strlen(nm);
    }
    out.write((const char*)&nameLen, sizeof(nameLen));
    if (nameLen > 0) {
        out.write(nm, nameLen);
    }
    return out.good();
}

bool readRecordBinary(std::ifstream& in, RecordDynamic& r) {
    int id = 0;
    double score = 0.0;
    in.read((char*)&id, sizeof(id));
    in.read((char*)&score, sizeof(score));
    size_t nameLen = 0;
    in.read((char*)&nameLen, sizeof(nameLen));
    if (!in) {
        return false;
    }
    r.setId(id);
    r.setScore(score);
    if (nameLen == 0) {
        return true;
    }
    char* buf = new char[nameLen + 1];
    in.read(buf, nameLen);
    buf[nameLen] = '\0';
    if (!in) {
        delete[] buf;
        return false;
    }
    r.setName(buf);
    delete[] buf;
    return true;
}
