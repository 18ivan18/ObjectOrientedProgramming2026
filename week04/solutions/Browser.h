#ifndef BROWSER_H
#define BROWSER_H

#include "BrowserTab.h"
#include <cstddef>

class Browser
{
private:
    BrowserTab *tabs;
    size_t size;
    size_t capacity;
    size_t activeTabIndex;

    void resize();

public:
    Browser();
    ~Browser();

    size_t getTabCount() const;
    size_t getActiveTabIndex() const;
    BrowserTab &getTab(size_t index);
    const BrowserTab &getTab(size_t index) const;

    void addTab(const BrowserTab &tab);
    void removeTab(size_t index);
    bool switchTab(size_t index);
};

#endif
