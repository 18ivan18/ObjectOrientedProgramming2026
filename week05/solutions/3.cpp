// Компилиране: g++ -o 3 3.cpp SharedNote.cpp
#include "SharedNote.h"
#include <iostream>

int main()
{
    SharedNote note("Първоначална бележка");
    std::cout << "note: " << note.getContent() << '\n';

    SharedNote copy(note);
    std::cout << "copy (shallow): " << copy.getContent() << '\n';

    note.setContent("Променена от note");
    std::cout << "\nСлед setContent от note:\n";
    std::cout << "note: " << note.getContent() << '\n';
    std::cout << "copy: " << copy.getContent() << " (споделя същото съдържание)\n";

    copy.append(" - допълнено от copy");
    std::cout << "\nСлед append от copy:\n";
    std::cout << "note: " << note.getContent() << '\n';
    std::cout << "copy: " << copy.getContent() << '\n';
}
