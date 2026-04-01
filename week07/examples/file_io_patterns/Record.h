#pragma once

#include <cstring>
#include <fstream>
#include "parse_record_line.h"

const size_t RECORD_LINE_BUF = 512;

// POD-подобен клас: фиксиран буфер за име, без динамична памет вътре в обекта —
// подходящ за директно read/write в двоичен файл на целия обект.
class Record
{
private:
    char name[64];
    int id;
    double score;

public:
    Record() : id(0), score(0.0)
    {
        name[0] = '\0';
    }

    Record(int id, double score, const char *nameStr) : id(id), score(score)
    {
        setName(nameStr);
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
        return name;
    }

    void setId(int id)
    {
        this->id = id;
    }

    void setScore(double score)
    {
        this->score = score;
    }

    void setName(const char *name)
    {
        std::strncpy(this->name, name, sizeof(this->name) - 1);
        this->name[sizeof(this->name) - 1] = '\0';
    }

    friend std::ostream &operator<<(std::ostream &os, const Record &r)
    {
        os << r.getId() << '|' << r.getScore() << '|' << r.getName();
        return os;
    }

    friend std::istream &operator>>(std::istream &is, Record &r)
    {
        char line[RECORD_LINE_BUF];
        is.getline(line, sizeof(line));
        if (!is)
        {
            return is;
        }
        int id = 0;
        double score = 0.0;
        char nameBuf[RECORD_LINE_BUF] = {};
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
