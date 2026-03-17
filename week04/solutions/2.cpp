// Компилиране: g++ -o 2 2.cpp BrowserTab.cpp
#include "BrowserTab.h"
#include <iostream>
#include <iomanip>

int main()
{
    BrowserTab defaultTab;
    std::cout << "По подразбиране: URL=\"" << defaultTab.getUrl() << "\", isEmpty=" << (defaultTab.isEmpty() ? "true" : "false") << '\n';

    BrowserTab tab("https://example.com", "<html><body>Hello</body></html>");
    std::cout << "URL: " << tab.getUrl() << '\n';
    std::cout << "HTML: " << tab.getHtmlContent() << '\n';

    BrowserTab emptyTab;
    emptyTab.loadFrom(tab);
    std::cout << "loadFrom - emptyTab сега има URL: " << emptyTab.getUrl() << '\n';

    tab.clear();
    std::cout << "След clear - isEmpty=" << std::boolalpha << tab.isEmpty() << '\n';
}
