#include "UserInfo.h"
#include <cstring>

char *copyString(const char *str)
{
    if (!str){
        return nullptr;
    }
    size_t len = strlen(str) + 1;
    char *copy = new char[len];
    strcpy(copy, str);
    return copy;
}

UserInfo::UserInfo() : username(copyString("")), password(copyString(""))
{
}

UserInfo::UserInfo(const char *user) : username(copyString(user ? user : "")), password(copyString(""))
{
}

UserInfo::UserInfo(const char *user, const char *pass)
    : username(copyString(user ? user : "")), password(copyString(pass ? pass : ""))
{
}

UserInfo::~UserInfo()
{
    delete[] username;
    delete[] password;
}

const char *UserInfo::getUsername() const
{
    return username;
}

const char *UserInfo::getPassword() const
{
    return password;
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
