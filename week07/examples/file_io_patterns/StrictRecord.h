#pragma once

#include <cstring>
#include <fstream>

// Като Record, но без конструктор по подразбиране — не може `new StrictRecord[n]`
// без списък с инициализатори за всеки елемент (при неизвестен n от файл: placement new).
class StrictRecord
{
private:
    char name[64];
    int id;
    double score;

public:
    StrictRecord(int id, double score, const char *nameStr) : id(id), score(score)
    {
        setName(nameStr);
    }

    ~StrictRecord() = default;

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

    void setName(const char *s)
    {
        std::strncpy(name, s, sizeof(name) - 1);
        name[sizeof(name) - 1] = '\0';
    }

    friend std::ostream &operator<<(std::ostream &os, const StrictRecord &r)
    {
        os << r.getId() << '|' << r.getScore() << '|' << r.getName();
        return os;
    }
};