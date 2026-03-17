#ifndef BROWSERTAB_H
#define BROWSERTAB_H

#include <cstddef>

class BrowserTab
{
private:
    char *url;
    char *htmlContent;

public:
    BrowserTab();
    BrowserTab(const char *url, const char *htmlContent);
    ~BrowserTab();

    const char *getUrl() const;
    const char *getHtmlContent() const;
    void setUrl(const char *url);
    void setHtmlContent(const char *htmlContent);

    bool isEmpty() const;
    void clear();
    void loadFrom(const BrowserTab &other);
};

#endif
