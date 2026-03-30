// Задача 3 (седмица 7): CSV студенти, конзолен интерфейс, запис при изход.
//
// Ред в CSV: първо_име,фамилия,факултетен_номер,специалност,имейл

#include <cstdio>
#include <cstring>
#include <fstream>
#include <iostream>

const int MAX_FIELD = 128;
const int MAX_STUDENTS = 256;
const int MAX_PATH = 512;

struct Student {
    char firstName[MAX_FIELD];
    char lastName[MAX_FIELD];
    char fn[MAX_FIELD];
    char major[MAX_FIELD];
    char email[MAX_FIELD];
};

Student g_students[MAX_STUDENTS];
int g_studentCount = 0;
char g_currentPath[MAX_PATH];

bool pathIsEmpty() {
    return g_currentPath[0] == '\0';
}

void setPath(const char* path) {
    std::strncpy(g_currentPath, path, MAX_PATH - 1);
    g_currentPath[MAX_PATH - 1] = '\0';
}

// Парсва един ред CSV (полетата без запетаи вътре).
bool parseCsvLine(const char* line, Student& s) {
    int n = std::sscanf(line, "%127[^,],%127[^,],%127[^,],%127[^,],%127[^\n\r]",
        s.firstName, s.lastName, s.fn, s.major, s.email);
    return n == 5;
}

bool loadFromFile(const char* path) {
    std::ifstream in(path);
    if (!in.is_open()) {
        return false;
    }

    g_studentCount = 0;
    char line[MAX_PATH + MAX_FIELD * 5];
    while (in.getline(line, sizeof(line))) {
        if (line[0] == '\0') {
            continue;
        }
        if (g_studentCount >= MAX_STUDENTS) {
            break;
        }
        Student s;
        if (!parseCsvLine(line, s)) {
            continue;
        }
        g_students[g_studentCount] = s;
        g_studentCount++;
    }

    setPath(path);
    return true;
}

bool saveToFile(const char* path) {
    std::ofstream out(path);
    if (!out.is_open()) {
        return false;
    }

    for (int i = 0; i < g_studentCount; i++) {
        const Student& s = g_students[i];
        out << s.firstName << ',' << s.lastName << ',' << s.fn << ',' << s.major << ',' << s.email << '\n';
    }

    setPath(path);
    return out.good();
}

int findStudent(const char* fn, const char* major) {
    for (int i = 0; i < g_studentCount; i++) {
        if (std::strcmp(g_students[i].fn, fn) == 0 && std::strcmp(g_students[i].major, major) == 0) {
            return i;
        }
    }
    return -1;
}

void printStudent(const char* fn, const char* major) {
    int i = findStudent(fn, major);
    if (i < 0) {
        std::cout << "No such student.\n";
        return;
    }

    const Student& s = g_students[i];
    std::cout << "Name = " << s.firstName << ' ' << s.lastName << ", Major: " << s.major
              << ", Email: " << s.email << ", FN: " << s.fn << '\n';
}

bool editEmail(const char* fn, const char* major, const char* newEmail) {
    int i = findStudent(fn, major);
    if (i < 0) {
        return false;
    }
    std::strncpy(g_students[i].email, newEmail, MAX_FIELD - 1);
    g_students[i].email[MAX_FIELD - 1] = '\0';
    return true;
}

int main() {
    g_currentPath[0] = '\0';

    std::cout << "Open file:\n>";
    char path[MAX_PATH];
    std::cin.getline(path, MAX_PATH);

    if (!loadFromFile(path)) {
        std::cerr << "Could not open file.\n";
        return 1;
    }

    std::cout << "File successfully opened!\n";

    char line[512];
    char cmd[32];
    char a[MAX_FIELD];
    char b[MAX_FIELD];
    char c[MAX_FIELD];

    while (true) {
        std::cout << '>';
        if (!std::cin.getline(line, sizeof(line))) {
            break;
        }

        int parsed = std::sscanf(line, "%31s", cmd);
        if (parsed < 1 || cmd[0] == '\0') {
            continue;
        }

        if (std::strcmp(cmd, "exit") == 0 || std::strcmp(cmd, "quit") == 0) {
            break;
        }

        if (std::strcmp(cmd, "print") == 0) {
            if (std::sscanf(line, "%31s %127s %127s", cmd, a, b) == 3) {
                printStudent(a, b);
            }
        } else if (std::strcmp(cmd, "edit") == 0) {
            if (std::sscanf(line, "%31s %127s %127s %127s", cmd, a, b, c) == 4) {
                if (!editEmail(a, b, c)) {
                    std::cout << "Edit failed (student not found).\n";
                }
            }
        } else if (std::strcmp(cmd, "save") == 0) {
            if (std::sscanf(line, "%31s %127s", cmd, a) == 2) {
                if (!saveToFile(a)) {
                    std::cout << "Save failed.\n";
                } else {
                    std::cout << "file " << a << " successfully saved!\n";
                }
            }
        } else {
            std::cout << "Unknown command.\n";
        }
    }

    if (!pathIsEmpty()) {
        if (saveToFile(g_currentPath)) {
            std::cout << "Data saved to \"" << g_currentPath << "\".\n";
        }
    }
}
