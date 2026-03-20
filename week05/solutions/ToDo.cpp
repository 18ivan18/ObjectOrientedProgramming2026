#include "ToDo.h"
#include <cstring>

char *copyString(const char *str)
{
    if (!str)
    {
        return nullptr;
    }
    size_t len = strlen(str) + 1;
    char *copy = new char[len];
    strcpy(copy, str);
    return copy;
}

ToDo::ToDo() : id(0), description(nullptr), completed(false)
{
}

ToDo::ToDo(const ToDo &other)
    : id(other.id), description(copyString(other.description)), completed(other.completed)
{
}

ToDo::ToDo(int i, const char *desc, bool done)
    : id(i), description(copyString(desc)), completed(done)
{
}

ToDo::~ToDo()
{
    clear();
}

ToDo &ToDo::operator=(const ToDo &other)
{
    if (this != &other)
    {
        id = other.id;
        clear();
        copyFrom(other);
        completed = other.completed;
    }
    return *this;
}

void ToDo::clear()
{
    delete[] description;
    description = nullptr;
}

void ToDo::copyFrom(const ToDo &other)
{
    description = copyString(other.description);
}

void ToDo::execute()
{
    completed = true;
}

int ToDo::getId() const
{
    return id;
}

const char *ToDo::getDescription() const
{
    return description ? description : "";
}

bool ToDo::isCompleted() const
{
    return completed;
}
