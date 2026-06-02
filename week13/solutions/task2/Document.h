#ifndef DOCUMENT_H
#define DOCUMENT_H

#include "Object.h"

class Document : public Object {
    std::string* lines;
    int lineCount;
    int lineCapacity;
    int cursor;

    void ensureCapacity();
    void copyFrom(const Document& other);
    void clearLines();

public:
    Document(const std::string& name, const std::string& location, const std::string& ext);
    Document(const Document& other);
    Document& operator=(const Document& other);
    ~Document();

    void writeLine(const std::string& line);
    std::string readLine();
    std::string readLine(int lineNum);

    bool operator==(const Comparable* other) const override;
    bool operator!=(const Comparable* other) const override;
    std::string debug_print() const override;
    std::string toString() const override;
    void fromString(const std::string& s) override;
    Object* clone() const override;
};

#endif // DOCUMENT_H
