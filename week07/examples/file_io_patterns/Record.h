#pragma once

#include <cstring>

// POD-подобен клас: фиксиран буфер за име, без динамична памет вътре в обекта —
// подходящ за директно read/write в двоичен файл на целия обект.
class Record {
private:
    char name[64];
    int id;
    double score;

public:
    Record() : id(0), score(0.0) {
        name[0] = '\0';
    }

    Record(int id_, double score_, const char* nameStr) : id(id_), score(score_) {
        setName(nameStr);
    }

    int getId() const {
        return id;
    }

    double getScore() const {
        return score;
    }

    const char* getName() const {
        return name;
    }

    void setId(int id_) {
        id = id_;
    }

    void setScore(double score_) {
        score = score_;
    }

    void setName(const char* s) {
        std::strncpy(name, s, sizeof(name) - 1);
        name[sizeof(name) - 1] = '\0';
    }
};
