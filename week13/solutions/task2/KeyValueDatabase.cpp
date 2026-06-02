#include "KeyValueDatabase.h"
#include <stdexcept>
#include <sstream>

KeyValueDatabase::KeyValueDatabase(const std::string& name, const std::string& location, const std::string& ext)
    : Object(name, location, ext), entries(nullptr), entryCount(0), entryCapacity(0) {}

void KeyValueDatabase::copyFrom(const KeyValueDatabase& other) {
    entryCount = other.entryCount;
    entryCapacity = other.entryCapacity;
    entries = entryCapacity > 0 ? new Entry[entryCapacity] : nullptr;
    for (int i = 0; i < entryCount; i++) {
        entries[i] = other.entries[i];
    }
}

void KeyValueDatabase::clearEntries() {
    delete[] entries;
    entries = nullptr;
    entryCount = 0;
    entryCapacity = 0;
}

KeyValueDatabase::KeyValueDatabase(const KeyValueDatabase& other)
    : Object(other.name, other.location, other.extension), entries(nullptr), entryCount(0), entryCapacity(0) {
    copyFrom(other);
}

KeyValueDatabase& KeyValueDatabase::operator=(const KeyValueDatabase& other) {
    if (this != &other) {
        clearEntries();
        name = other.name;
        location = other.location;
        extension = other.extension;
        copyFrom(other);
    }
    return *this;
}

KeyValueDatabase::~KeyValueDatabase() {
    clearEntries();
}

void KeyValueDatabase::ensureCapacity() {
    if (entryCount == entryCapacity) {
        int newCap = entryCapacity == 0 ? 4 : entryCapacity * 2;
        Entry* newEntries = new Entry[newCap];
        for (int i = 0; i < entryCount; i++) {
            newEntries[i] = entries[i];
        }
        delete[] entries;
        entries = newEntries;
        entryCapacity = newCap;
    }
}

int KeyValueDatabase::findIndex(const std::string& key) const {
    for (int i = 0; i < entryCount; i++) {
        if (entries[i].key == key) { return i; }
    }
    return -1;
}

void KeyValueDatabase::put(const std::string& key, int value) {
    if (findIndex(key) != -1) {
        throw std::invalid_argument("Key already exists: " + key);
    }
    ensureCapacity();
    entries[entryCount++] = {key, value};
}

int KeyValueDatabase::get(const std::string& key) const {
    int idx = findIndex(key);
    if (idx == -1) {
        throw std::invalid_argument("Key not found: " + key);
    }
    return entries[idx].value;
}

bool KeyValueDatabase::operator==(const Comparable* other) const {
    const KeyValueDatabase* db = dynamic_cast<const KeyValueDatabase*>(other);
    if (!db) { return false; }
    if (entryCount != db->entryCount) { return false; }
    for (int i = 0; i < entryCount; i++) {
        int idx = db->findIndex(entries[i].key);
        if (idx == -1 || db->entries[idx].value != entries[i].value) { return false; }
    }
    return true;
}

bool KeyValueDatabase::operator!=(const Comparable* other) const {
    return !(*this == other);
}

std::string KeyValueDatabase::debug_print() const {
    std::string result;
    for (int i = 0; i < entryCount; i++) {
        result += "{" + entries[i].key + ":" + std::to_string(entries[i].value) + "}\n";
    }
    return result;
}

std::string KeyValueDatabase::toString() const {
    std::string result;
    result += name + "\n";
    result += location + "\n";
    result += extension + "\n";
    for (int i = 0; i < entryCount; i++) {
        result += entries[i].key + ":" + std::to_string(entries[i].value) + "\n";
    }
    return result;
}

void KeyValueDatabase::fromString(const std::string& s) {
    clearEntries();

    std::istringstream stream(s);
    std::string line;

    std::getline(stream, name);
    std::getline(stream, location);
    std::getline(stream, extension);

    while (std::getline(stream, line)) {
        if (line.empty()) { continue; }
        size_t colonPos = line.find(':');
        if (colonPos == std::string::npos) { continue; }
        std::string key = line.substr(0, colonPos);
        int value = std::stoi(line.substr(colonPos + 1));
        ensureCapacity();
        entries[entryCount++] = {key, value};
    }
}

Object* KeyValueDatabase::clone() const {
    return new KeyValueDatabase(*this);
}
