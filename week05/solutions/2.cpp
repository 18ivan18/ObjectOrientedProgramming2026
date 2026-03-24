// Компилиране: g++ -o 2 2.cpp ToDo.cpp
#include "ToDo.h"
#include <iostream>

int main()
{
    ToDo defaultTodo;
    std::cout << "По подразбиране: id=" << defaultTodo.getId()
              << ", completed=" << (defaultTodo.isCompleted() ? "да" : "не") << '\n';

    ToDo todo(1, "Напиши домашно по ООП");
    std::cout << "Задача: [" << todo.getId() << "] " << todo.getDescription()
              << " - " << (todo.isCompleted() ? "изпълнена" : "чакаща") << '\n';

    todo.execute();
    std::cout << "След execute: " << (todo.isCompleted() ? "изпълнена" : "чакаща") << '\n';

    ToDo copy(todo);
    std::cout << "Копие: " << copy.getDescription() << '\n';

    ToDo other(2, "Прегледай лекции");
    todo = other;
    std::cout << "След присвояване: " << todo.getDescription() << '\n';
}
