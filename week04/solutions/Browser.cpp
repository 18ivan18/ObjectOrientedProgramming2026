#include "Browser.h"
#include <cassert>

Browser::Browser() : tabs(nullptr), size(0), capacity(4), activeTabIndex(0)
{
    tabs = new BrowserTab[capacity];
}

Browser::~Browser()
{
    delete[] tabs;
}

void Browser::resize()
{
    if (size < capacity) {
        return;
    }
    size_t newCapacity = capacity * 2;
    BrowserTab *newTabs = new BrowserTab[newCapacity];
    for (size_t i = 0; i < size; i++) {
        newTabs[i].loadFrom(tabs[i]);
    }
    delete[] tabs;
    tabs = newTabs;
    capacity = newCapacity;
}

size_t Browser::getTabCount() const
{
    return size;
}

size_t Browser::getActiveTabIndex() const
{
    return activeTabIndex;
}

BrowserTab &Browser::getTab(size_t index)
{
    assert(index < size);
    return tabs[index];
}

const BrowserTab &Browser::getTab(size_t index) const
{
    assert(index < size);
    return tabs[index];
}

void Browser::addTab(const BrowserTab &tab)
{
    resize();
    tabs[size].loadFrom(tab);
    size++;
}

void Browser::removeTab(size_t index)
{
    if (index >= size) {
        return;
    }
    for (size_t i = index; i < size - 1; i++) {
        tabs[i].loadFrom(tabs[i + 1]);
    }
    size--;
    if (size == 0) {
        activeTabIndex = 0;
    }
    else if (activeTabIndex >= size) {
        activeTabIndex = size - 1;
    }
    else if (activeTabIndex > index) {
        activeTabIndex--;
    }
}

bool Browser::switchTab(size_t index)
{
    if (index >= size) {
        return false;
    }
    activeTabIndex = index;
    return true;
}
