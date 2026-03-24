// Компилиране: g++ -o 2b 2b.cpp ToDo.cpp ToDoList.cpp
#include "ToDoList.h"
#include <iostream>

int main()
{
    ToDoList list;

    list.addTask(1, "Напиши домашно");
    list.addTask(2, "Прегледай лекции");
    list.addTask(3, "Подготви се за изпита");
    std::cout << "Добавени 3 задачи: " << list.getTaskCount() << '\n';

    if (!list.addTask(1, "Дублирана задача")) {
        std::cout << "Задача с id=1 не се добавя (уникално id)\n";
    }

    list.executeTask(1);
    list.executeTask(2);

    int completedCount;
    ToDo *completed = list.getCompletedTasks(completedCount);
    std::cout << "\nИзпълнени: " << completedCount << '\n';
    delete[] completed;

    int incompleteCount;
    ToDo *incomplete = list.getIncompleteTasks(incompleteCount);
    std::cout << "Неизпълнени: " << incompleteCount << '\n';
    for (int i = 0; i < incompleteCount; i++) {
        std::cout << "  [" << incomplete[i].getId() << "] " << incomplete[i].getDescription() << '\n';
    }
    delete[] incomplete;
}
