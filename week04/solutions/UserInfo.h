#ifndef USERINFO_H
#define USERINFO_H

#include <cstddef>

class UserInfo
{
private:
    char *username;
    char *password;

public:
    UserInfo();
    UserInfo(const char *username);
    UserInfo(const char *username, const char *password);
    ~UserInfo();

    const char *getUsername() const;
    const char *getPassword() const;
    void setUsername(const char *username);
    void setPassword(const char *password);
};

#endif
