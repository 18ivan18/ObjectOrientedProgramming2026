// Компилиране: g++ -o 2b 2b.cpp Browser.cpp BrowserTab.cpp
#include "Browser.h"
#include <iostream>

int main()
{
    Browser browser;

    browser.addTab(BrowserTab("https://google.com", "<html>Google</html>"));
    browser.addTab(BrowserTab("https://example.com", "<html>Example</html>"));
    browser.addTab(BrowserTab("https://github.com", "<html>GitHub</html>"));

    std::cout << "Брой табове: " << browser.getTabCount() << '\n';
    std::cout << "Активен таб [0]: " << browser.getTab(0).getUrl() << '\n';

    browser.switchTab(2);
    std::cout << "След switchTab(2): " << browser.getTab(browser.getActiveTabIndex()).getUrl() << '\n';

    browser.removeTab(1);
    std::cout << "\nСлед removeTab(1), брой: " << browser.getTabCount() << '\n';
    std::cout << "Табове: " << browser.getTab(0).getUrl() << ", " << browser.getTab(1).getUrl() << '\n';
}
