#include <fstream>
#include <iostream>

const int LINE_BUF = 1024;

int main() {
    const char* path = "print_self.cpp";

    std::ifstream in(path);
    if (!in.is_open()) {
        std::cerr << "Cannot open file: " << path << '\n';
        return 1;
    }

    char line[LINE_BUF];
    while (in.getline(line, LINE_BUF)) {
        std::cout << line << '\n';
    }
}
