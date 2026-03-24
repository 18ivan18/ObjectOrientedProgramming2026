#ifndef TODOLIST_H
#define TODOLIST_H

#include "ToDo.h"
#include <cstddef>

class ToDoList
{
private:
    ToDo *tasks;
    size_t size;
    size_t capacity;

    void resize();
    bool hasId(int id) const;

public:
    ToDoList();
    ToDoList(const ToDoList &other);
    ~ToDoList();

    ToDoList &operator=(const ToDoList &other);

    bool addTask(const ToDo &task);
    bool addTask(int id, const char *description);
    bool executeTask(int id);
    size_t getTaskCount() const;

    ToDo *getCompletedTasks(int &count) const;
    ToDo *getIncompleteTasks(int &count) const;
};

#endif
