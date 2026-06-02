#include "Document.h"
#include <stdexcept>
#include <sstream>

Document::Document(const std::string& name, const std::string& location, const std::string& ext)
    : Object(name, location, ext), lines(nullptr), lineCount(0), lineCapacity(0), cursor(1) {}

void Document::copyFrom(const Document& other) {
    lineCount = other.lineCount;
    lineCapacity = other.lineCapacity;
    cursor = other.cursor;
    lines = lineCapacity > 0 ? new std::string[lineCapacity] : nullptr;
    for (int i = 0; i < lineCount; i++) {
        lines[i] = other.lines[i];
    }
}

void Document::clearLines() {
    delete[] lines;
    lines = nullptr;
    lineCount = 0;
    lineCapacity = 0;
}

Document::Document(const Document& other)
    : Object(other.name, other.location, other.extension), lines(nullptr), lineCount(0), lineCapacity(0), cursor(1) {
    copyFrom(other);
}

Document& Document::operator=(const Document& other) {
    if (this != &other) {
        clearLines();
        name = other.name;
        location = other.location;
        extension = other.extension;
        copyFrom(other);
    }
    return *this;
}

Document::~Document() {
    clearLines();
}

void Document::ensureCapacity() {
    if (lineCount == lineCapacity) {
        int newCap = lineCapacity == 0 ? 4 : lineCapacity * 2;
        std::string* newLines = new std::string[newCap];
        for (int i = 0; i < lineCount; i++) {
            newLines[i] = lines[i];
        }
        delete[] lines;
        lines = newLines;
        lineCapacity = newCap;
    }
}

void Document::writeLine(const std::string& line) {
    ensureCapacity();
    lines[lineCount++] = line;
}

std::string Document::readLine() {
    if (cursor < 1 || cursor > lineCount) {
        throw std::out_of_range("No more lines to read");
    }
    return lines[cursor++ - 1];
}

std::string Document::readLine(int lineNum) {
    if (lineNum < 1 || lineNum > lineCount) {
        throw std::out_of_range("Line number out of range");
    }
    cursor = lineNum + 1;
    return lines[lineNum - 1];
}

bool Document::operator==(const Comparable* other) const {
    const Document* doc = dynamic_cast<const Document*>(other);
    if (!doc) { return false; }
    if (lineCount != doc->lineCount) { return false; }
    for (int i = 0; i < lineCount; i++) {
        if (lines[i] != doc->lines[i]) { return false; }
    }
    return true;
}

bool Document::operator!=(const Comparable* other) const {
    return !(*this == other);
}

std::string Document::debug_print() const {
    std::string result;
    for (int i = 0; i < lineCount; i++) {
        result += "Line " + std::to_string(i + 1) + ":" + lines[i] + "\n";
    }
    return result;
}

std::string Document::toString() const {
    std::string result;
    result += name + "\n";
    result += location + "\n";
    result += extension + "\n";
    for (int i = 0; i < lineCount; i++) {
        result += lines[i] + "\n";
    }
    return result;
}

void Document::fromString(const std::string& s) {
    clearLines();
    cursor = 1;

    std::istringstream stream(s);
    std::string line;

    std::getline(stream, name);
    std::getline(stream, location);
    std::getline(stream, extension);

    while (std::getline(stream, line)) {
        writeLine(line);
    }
}

Object* Document::clone() const {
    return new Document(*this);
}
