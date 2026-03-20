#include "ToDoList.h"

ToDoList::ToDoList() : tasks(nullptr), size(0), capacity(4)
{
    tasks = new ToDo[capacity];
}

ToDoList::ToDoList(const ToDoList &other) : tasks(nullptr), size(other.size), capacity(other.capacity)
{
    tasks = new ToDo[capacity];
    for (size_t i = 0; i < size; i++) {
        tasks[i] = other.tasks[i];
    }
}

ToDoList::~ToDoList()
{
    delete[] tasks;
}

ToDoList &ToDoList::operator=(const ToDoList &other)
{
    if (this != &other)
    {
        delete[] tasks;
        size = other.size;
        capacity = other.capacity;
        tasks = new ToDo[capacity];
        for (size_t i = 0; i < size; i++) {
            tasks[i] = other.tasks[i];
        }
    }
    return *this;
}

void ToDoList::resize()
{
    if (size < capacity)
        return;
    size_t newCapacity = capacity * 2;
    ToDo *newTasks = new ToDo[newCapacity];
    for (size_t i = 0; i < size; i++)
        newTasks[i] = tasks[i];
    delete[] tasks;
    tasks = newTasks;
    capacity = newCapacity;
}

bool ToDoList::hasId(int id) const
{
    for (size_t i = 0; i < size; i++)
    {
        if (tasks[i].getId() == id)
            return true;
    }
    return false;
}

bool ToDoList::addTask(const ToDo &task)
{
    if (hasId(task.getId()))
        return false;
    resize();
    tasks[size++] = task;
    return true;
}

bool ToDoList::addTask(int id, const char *description)
{
    if (hasId(id))
        return false;
    resize();
    tasks[size++] = ToDo(id, description, false);
    return true;
}

bool ToDoList::executeTask(int id)
{
    for (size_t i = 0; i < size; i++)
    {
        if (tasks[i].getId() == id)
        {
            tasks[i].execute();
            return true;
        }
    }
    return false;
}

size_t ToDoList::getTaskCount() const
{
    return size;
}

ToDo *ToDoList::getCompletedTasks(int &count) const
{
    count = 0;
    for (size_t i = 0; i < size; i++)
    {
        if (tasks[i].isCompleted())
            count++;
    }
    ToDo *result = new ToDo[count];
    int idx = 0;
    for (size_t i = 0; i < size; i++)
    {
        if (tasks[i].isCompleted())
            result[idx++] = tasks[i];
    }
    return result;
}

ToDo *ToDoList::getIncompleteTasks(int &count) const
{
    count = 0;
    for (size_t i = 0; i < size; i++)
    {
        if (!tasks[i].isCompleted())
            count++;
    }
    ToDo *result = new ToDo[count];
    int idx = 0;
    for (size_t i = 0; i < size; i++)
    {
        if (!tasks[i].isCompleted())
            result[idx++] = tasks[i];
    }
    return result;
}
