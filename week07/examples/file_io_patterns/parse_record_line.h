#pragma once

#include <cstdlib>
#include <cstring>

// Парсва ред от вида id|score|име без sscanf — модифицира буфера line на място.
inline bool parseRecordLine(char* line, int& id, double& score, char* nameBuf, size_t nameMax) {
    char* p1 = std::strchr(line, '|');
    if (p1 == nullptr) {
        return false;
    }
    *p1 = '\0';
    id = std::atoi(line);

    char* p2 = std::strchr(p1 + 1, '|');
    if (p2 == nullptr) {
        return false;
    }
    *p2 = '\0';
    score = std::atof(p1 + 1);

    std::strncpy(nameBuf, p2 + 1, nameMax - 1);
    nameBuf[nameMax - 1] = '\0';
    return true;
}
