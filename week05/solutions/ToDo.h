#ifndef TODO_H
#define TODO_H

#include <cstddef>

class ToDo
{
private:
    int id;
    char *description;
    bool completed;

    void clear();
    void copyFrom(const ToDo &other);
public:
    ToDo();
    ToDo(const ToDo &other);
    ToDo(int id, const char *description, bool completed = false);
    ~ToDo();

    ToDo &operator=(const ToDo &other);

    void execute();
    int getId() const;
    const char *getDescription() const;
    bool isCompleted() const;
};

#endif
