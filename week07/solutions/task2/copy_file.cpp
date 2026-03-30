#include <fstream>
#include <iostream>

const int MAX_PATH_LEN = 512;

// Връща true при успешно копиране (изходният файл е създаден/презаписан).
bool copyFile(const char* sourcePath, const char* destPath) {
    std::ifstream in(sourcePath);
    if (!in.is_open()) {
        return false;
    }

    std::ofstream out(destPath);
    if (!out.is_open()) {
        return false;
    }

    char ch;
    while (in.get(ch)) {
        out.put(ch);
    }

    return in.eof() && out.good();
}

int main() {
    char sourcePath[MAX_PATH_LEN];
    char destPath[MAX_PATH_LEN];

    std::cout << "Existing file: ";
    std::cin.getline(sourcePath, MAX_PATH_LEN);
    std::cout << "New file: ";
    std::cin.getline(destPath, MAX_PATH_LEN);

    if (!copyFile(sourcePath, destPath)) {
        std::cerr << "Copy failed.\n";
        return 1;
    }

    std::cout << "Copy finished.\n";
}
