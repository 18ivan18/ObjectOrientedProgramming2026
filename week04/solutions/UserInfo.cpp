#include "UserInfo.h"
#include <cstring>

char *copyString(const char *str)
{
    if (!str) {
        return nullptr;
    }
    size_t len = strlen(str) + 1;
    char *copy = new char[len];
    strcpy(copy, str);
    return copy;
}

UserInfo::UserInfo() : username(nullptr), password(nullptr)
{
}

UserInfo::UserInfo(const char *user) : username(copyString(user)), password(nullptr)
{
}

UserInfo::UserInfo(const char *user, const char *pass)
    : username(copyString(user)), password(copyString(pass))
{
}

UserInfo::~UserInfo()
{
    delete[] username;
    delete[] password;
}

const char *UserInfo::getUsername() const
{
    return username ? username : "";
}

const char *UserInfo::getPassword() const
{
    return password ? password : "";
}

void UserInfo::setUsername(const char *user)
{
    delete[] username;
    username = copyString(user);
}

void UserInfo::setPassword(const char *pass)
{
    delete[] password;
    password = copyString(pass);
}
