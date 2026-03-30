#pragma once

#include <cstring>
#include <cstdlib>

// Обект с динамично име — за текстов/двоичен формат записваме дължината и съдържанието.
class RecordDynamic {
private:
    int id;
    double score;
    char* name;

public:
    RecordDynamic() : id(0), score(0.0), name(nullptr) {}

    RecordDynamic(int id_, double score_, const char* nameStr) : id(id_), score(score_), name(nullptr) {
        setName(nameStr);
    }

    RecordDynamic(const RecordDynamic& other) : id(other.id), score(other.score), name(nullptr) {
        setName(other.getName());
    }

    RecordDynamic& operator=(const RecordDynamic& other) {
        if (this != &other) {
            id = other.id;
            score = other.score;
            setName(other.getName());
        }
        return *this;
    }

    ~RecordDynamic() {
        delete[] name;
    }

    int getId() const {
        return id;
    }

    double getScore() const {
        return score;
    }

    const char* getName() const {
        return name ? name : "";
    }

    void setId(int id_) {
        id = id_;
    }

    void setScore(double score_) {
        score = score_;
    }

    void setName(const char* s) {
        delete[] name;
        if (s == nullptr || s[0] == '\0') {
            name = nullptr;
            return;
        }
        size_t len = std::strlen(s);
        name = new char[len + 1];
        std::strcpy(name, s);
    }
};
