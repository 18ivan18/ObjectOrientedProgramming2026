#include "SharedNote.h"
#include <cstring>

char *copyString(const char *str)
{
    if (!str)
    {
        return nullptr;
    }
    size_t len = strlen(str) + 1;
    char *copy = new char[len];
    strcpy(copy, str);
    return copy;
}

void SharedNote::release()
{
    if (!refCount) {
        return;
    }
    (*refCount)--;
    if (*refCount == 0)
    {
        delete[] *pContent;
        delete pContent;
        delete refCount;
    }
}

SharedNote::SharedNote()
    : pContent(nullptr), refCount(new int(1))
{
}

SharedNote::SharedNote(const char *content)
    : pContent(copyString(content)), refCount(new int(1))
{
}

SharedNote::SharedNote(const SharedNote &other)
    : pContent(other.pContent), refCount(other.refCount)
{
    (*refCount)++;
}

SharedNote::~SharedNote()
{
    release();
}

SharedNote &SharedNote::operator=(const SharedNote &other)
{
    if (this != &other)
    {
        release();
        pContent = other.pContent;
        refCount = other.refCount;
        (*refCount)++;
    }
    return *this;
}

const char *SharedNote::getContent() const
{
    return *pContent;
}

void SharedNote::setContent(const char *content)
{
    delete[] *pContent;
    *pContent = copyString(content);
}

void SharedNote::append(const char *text)
{
    if (!text) {
        return;
    }
    size_t oldLen = strlen(*pContent);
    size_t addLen = strlen(text);
    char *newStr = new char[oldLen + addLen + 1];
    strcpy(newStr, *pContent);
    strcat(newStr, text);
    delete[] *pContent;
    *pContent = newStr;
}
