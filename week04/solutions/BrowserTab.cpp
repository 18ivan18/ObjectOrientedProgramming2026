#include "BrowserTab.h"
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

BrowserTab::BrowserTab() : url(nullptr), htmlContent(nullptr)
{
}

BrowserTab::BrowserTab(const char *u, const char *html)
    : url(copyString(u)), htmlContent(copyString(html))
{
}

BrowserTab::~BrowserTab()
{
    clear();
}

const char *BrowserTab::getUrl() const
{
    return url ? url : "";
}

const char *BrowserTab::getHtmlContent() const
{
    return htmlContent ? htmlContent : "";
}

void BrowserTab::setUrl(const char *u)
{
    delete[] url;
    url = copyString(u);
}

void BrowserTab::setHtmlContent(const char *html)
{
    delete[] htmlContent;
    htmlContent = copyString(html);
}

bool BrowserTab::isEmpty() const
{
    return url == nullptr && htmlContent == nullptr;
}

void BrowserTab::clear()
{
    delete[] url;
    delete[] htmlContent;
    url = nullptr;
    htmlContent = nullptr;
}

void BrowserTab::loadFrom(const BrowserTab &other)
{
    clear();
    url = copyString(other.url);
    htmlContent = copyString(other.htmlContent);
}
