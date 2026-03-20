#ifndef SHAREDNOTE_H
#define SHAREDNOTE_H

#include <cstddef>

class SharedNote
{
private:
    char **pContent;
    int *refCount;

    void release();

public:
    SharedNote();
    SharedNote(const char *content);
    SharedNote(const SharedNote &other);
    ~SharedNote();

    SharedNote &operator=(const SharedNote &other);

    const char *getContent() const;
    void setContent(const char *content);
    void append(const char *text);
};

#endif
