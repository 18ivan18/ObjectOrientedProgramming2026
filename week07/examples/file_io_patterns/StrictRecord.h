#pragma once

#include <cstring>

// Като Record, но без конструктор по подразбиране — не може `new StrictRecord[n]`
// без списък с инициализатори за всеки елемент (при неизвестен n от файл: placement new).
class StrictRecord {
private:
    char name[64];
    int id;
    double score;

public:
    StrictRecord(int id_, double score_, const char* nameStr) : id(id_), score(score_) {
        setName(nameStr);
    }

    ~StrictRecord() = default;

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
