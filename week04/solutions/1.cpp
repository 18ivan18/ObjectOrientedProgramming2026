// Компилиране: g++ -o 1 1.cpp UserInfo.cpp
#include "UserInfo.h"
#include <iostream>

int main()
{
    UserInfo defaultUser;
    std::cout << "По подразбиране: " << defaultUser.getUsername() << " / " << defaultUser.getPassword() << '\n';

    UserInfo namedUser("ivan");
    std::cout << "Само име: " << namedUser.getUsername() << " / " << namedUser.getPassword() << '\n';

    UserInfo fullUser("admin", "secret123");
    std::cout << "Име и парола: " << fullUser.getUsername() << " / " << fullUser.getPassword() << '\n';

    fullUser.setPassword("newpass");
    std::cout << "След setPassword: " << fullUser.getPassword() << '\n';
}
