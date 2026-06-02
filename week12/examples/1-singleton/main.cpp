#include <iostream>

// -----------------------------------------------------------------------
// Manual Singleton — the classic approach
// -----------------------------------------------------------------------

class Logger
{
    static Logger *instance;

    Logger()
    {
    }
    Logger(const Logger &) = delete;
    Logger &operator=(const Logger &) = delete;

public:
    static Logger *getInstance()
    {
        if (!instance)
        {
            instance = new Logger();
        }
        return instance;
    }

    void log(const char *message)
    {
        std::cout << "[LOG] " << message << "\n";
    }
};

Logger *Logger::instance = nullptr;

// -----------------------------------------------------------------------
// Singleton<T> base class — CRTP, eliminates the boilerplate
//
// Every class that inherits Singleton<T> gets getInstance() for free.
// Uses Meyers' Singleton (static local variable) which is:
//   - lazily initialized on first call
//   - thread-safe since C++11
//   - destroyed automatically when the program exits
// -----------------------------------------------------------------------

template <typename T> 
class Singleton
{
protected:
    Singleton() = default;

private:
    Singleton(const Singleton &) = delete;
    Singleton &operator=(const Singleton &) = delete;

public:
    static T &getInstance()
    {
        static T instance;
        return instance;
    }
};

class AppConfig : public Singleton<AppConfig>
{
    friend class Singleton<AppConfig>; // lets the base call the private constructor

    int port;
    bool debug;

    AppConfig() : port(8080), debug(false)
    {
    }

public:
    void setPort(int p)
    {
        port = p;
    }
    void setDebug(bool d)
    {
        debug = d;
    }
    int getPort() const
    {
        return port;
    }
    bool getDebug() const
    {
        return debug;
    }
};

class EventLog : public Singleton<EventLog>
{
    friend class Singleton<EventLog>;

    EventLog()
    {
    }

public:
    void record(const char *event)
    {
        std::cout << "[EVENT] " << event << "\n";
    }
};

int main()
{
    // --- Manual Singleton ---
    Logger *a = Logger::getInstance();
    Logger *b = Logger::getInstance();
    std::cout << "Same Logger instance: " << (a == b ? "yes" : "no") << "\n";
    a->log("Application started");
    b->log("Application ready");

    std::cout << "\n";

    // --- CRTP Singleton base ---
    // getInstance() returns T& — call with . not ->
    AppConfig::getInstance().setPort(9090);
    AppConfig::getInstance().setDebug(true);

    AppConfig &cfg1 = AppConfig::getInstance();
    AppConfig &cfg2 = AppConfig::getInstance();
    std::cout << "Same AppConfig instance: " << (&cfg1 == &cfg2 ? "yes" : "no") << "\n";
    std::cout << "port:  " << cfg1.getPort() << "\n";
    std::cout << "debug: " << cfg1.getDebug() << "\n";

    EventLog::getInstance().record("Server started");
    EventLog::getInstance().record("First request received");
}
