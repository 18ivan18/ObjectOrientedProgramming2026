#pragma once

#include "RecordDynamic.h"
#include "parse_record_line.h"
#include <iostream>

const size_t RECORD_DYNAMIC_LINE_BUF = 512;

inline std::ostream& operator<<(std::ostream& os, const RecordDynamic& r) {
    os << r.getId() << '|' << r.getScore() << '|' << r.getName();
    return os;
}

inline std::istream& operator>>(std::istream& is, RecordDynamic& r) {
    char line[RECORD_DYNAMIC_LINE_BUF];
    is.getline(line, sizeof(line));
    if (!is) {
        return is;
    }
    int id = 0;
    double score = 0.0;
    char nameBuf[RECORD_DYNAMIC_LINE_BUF] = {};
    if (!parseRecordLine(line, id, score, nameBuf, sizeof(nameBuf))) {
        is.setstate(std::ios::failbit);
        return is;
    }
    r.setId(id);
    r.setScore(score);
    r.setName(nameBuf);
    return is;
}
