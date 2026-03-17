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

BrowserTab::BrowserTab() : url(copyString("")), htmlContent(copyString(""))
{
}

BrowserTab::BrowserTab(const BrowserTab &other)
    : url(copyString(other.url)), htmlContent(copyString(other.htmlContent))
{
}

BrowserTab::BrowserTab(const char *u, const char *html)
    : url(copyString(u)), htmlContent(copyString(html))
{
}

BrowserTab::~BrowserTab()
{
    delete[] url;
    delete[] htmlContent;
}

const char *BrowserTab::getUrl() const
{
    return url;
}

const char *BrowserTab::getHtmlContent() const
{
    return htmlContent;
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
    return (url == nullptr && htmlContent == nullptr);
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
    delete[] url;
    delete[] htmlContent;
    url = copyString(other.url);
    htmlContent = copyString(other.htmlContent);
}
