#ifndef KEY_VALUE_DATABASE_H
#define KEY_VALUE_DATABASE_H

#include "Object.h"

class KeyValueDatabase : public Object {
    struct Entry {
        std::string key;
        int value;
    };

    Entry* entries;
    int entryCount;
    int entryCapacity;

    void ensureCapacity();
    void copyFrom(const KeyValueDatabase& other);
    void clearEntries();
    int findIndex(const std::string& key) const;

public:
    KeyValueDatabase(const std::string& name, const std::string& location, const std::string& ext);
    KeyValueDatabase(const KeyValueDatabase& other);
    KeyValueDatabase& operator=(const KeyValueDatabase& other);
    ~KeyValueDatabase();

    void put(const std::string& key, int value);
    int get(const std::string& key) const;

    bool operator==(const Comparable* other) const override;
    bool operator!=(const Comparable* other) const override;
    std::string debug_print() const override;
    std::string toString() const override;
    void fromString(const std::string& s) override;
    Object* clone() const override;
};

#endif // KEY_VALUE_DATABASE_H
