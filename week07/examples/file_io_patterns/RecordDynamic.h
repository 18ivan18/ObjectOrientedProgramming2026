#pragma once

#include <cstring>
#include <fstream>
#include "parse_record_line.h"

const size_t RECORD_DYNAMIC_LINE_BUF = 512;

// Обект с динамично име — за текстов/двоичен формат записваме дължината и съдържанието.
class RecordDynamic
{
private:
    int id;
    double score;
    char *name;

public:
    RecordDynamic() : id(0), score(0.0), name(nullptr) {}

    RecordDynamic(int id, double score, const char *nameStr) : id(id), score(score), name(nullptr)
    {
        setName(nameStr);
    }

    RecordDynamic(const RecordDynamic &other) : id(other.id), score(other.score), name(nullptr)
    {
        setName(other.getName());
    }

    RecordDynamic &operator=(const RecordDynamic &other)
    {
        if (this != &other)
        {
            id = other.id;
            score = other.score;
            setName(other.getName());
        }
        return *this;
    }

    ~RecordDynamic()
    {
        delete[] name;
    }

    int getId() const
    {
        return id;
    }

    double getScore() const
    {
        return score;
    }

    const char *getName() const
    {
        return name ? name : "";
    }

    void setId(int id)
    {
        this->id = id;
    }

    void setScore(double score)
    {
        this->score = score;
    }

    void setName(const char *s)
    {
        delete[] name;
        if (s == nullptr || s[0] == '\0')
        {
            name = nullptr;
            return;
        }
        size_t len = std::strlen(s);
        name = new char[len + 1];
        std::strcpy(name, s);
    }

    friend std::ostream &operator<<(std::ostream &os, const RecordDynamic &r)
    {
        os << r.getId() << '|' << r.getScore() << '|' << r.getName();
        return os;
    }

    friend std::istream &operator>>(std::istream &is, RecordDynamic &r)
    {
        char line[RECORD_DYNAMIC_LINE_BUF];
        is.getline(line, sizeof(line));
        if (!is)
        {
            return is;
        }
        int id = 0;
        double score = 0.0;
        char nameBuf[RECORD_DYNAMIC_LINE_BUF] = {};
        if (!parseRecordLine(line, id, score, nameBuf, sizeof(nameBuf)))
        {
            is.setstate(std::ios::failbit);
            return is;
        }
        r.setId(id);
        r.setScore(score);
        r.setName(nameBuf);
        return is;
    }
};
