#include <iostream>

class Observer
{
public:
    virtual void update(int value) = 0;
    virtual ~Observer()
    {
    }
};

class Subject
{
    static const int MAX_OBSERVERS = 10;
    Observer *observers[MAX_OBSERVERS];
    int count;

protected:
    void notifyAll(int value)
    {
        for (int i = 0; i < count; i++)
        {
            observers[i]->update(value);
        }
    }

public:
    Subject() : count(0)
    {
    }

    void attach(Observer *o)
    {
        if (count < MAX_OBSERVERS)
        {
            observers[count++] = o;
        }
    }

    void detach(Observer *o)
    {
        for (int i = 0; i < count; i++)
        {
            if (observers[i] == o)
            {
                for (int j = i; j < count - 1; j++)
                {
                    observers[j] = observers[j + 1];
                }
                count--;
                return;
            }
        }
    }

    virtual ~Subject()
    {
    }
};

class TemperatureSensor : public Subject
{
    int temperature;

public:
    TemperatureSensor() : temperature(0)
    {
    }
    void setTemperature(int t)
    {
        temperature = t;
        notifyAll(t);
    }
};

class ThresholdAlert : public Observer
{
    int threshold;

public:
    ThresholdAlert(int t) : threshold(t)
    {
    }
    void update(int value)
    {
        if (value > threshold)
        {
            std::cout << "ALERT: Temperature " << value << " exceeds limit " << threshold << "\n";
        }
    }
};

class TemperatureLogger : public Observer
{
public:
    void update(int value)
    {
        std::cout << "[LOG] Temperature: " << value << "C\n";
    }
};

class MinMaxTracker : public Observer
{
    int minVal;
    int maxVal;
    bool hasData;

public:
    MinMaxTracker() : minVal(0), maxVal(0), hasData(false)
    {
    }
    void update(int value)
    {
        if (!hasData || value < minVal)
        {
            minVal = value;
        }
        if (!hasData || value > maxVal)
        {
            maxVal = value;
        }
        hasData = true;
    }
    void report() const
    {
        if (hasData)
        {
            std::cout << "Min: " << minVal << "  Max: " << maxVal << "\n";
        }
    }
};

int main()
{
    TemperatureSensor sensor;
    ThresholdAlert alert(30);
    TemperatureLogger logger;
    MinMaxTracker tracker;

    sensor.attach(&alert);
    sensor.attach(&logger);
    sensor.attach(&tracker);

    sensor.setTemperature(22);
    sensor.setTemperature(35);
    sensor.setTemperature(18);

    sensor.detach(&logger);
    std::cout << "\n(Logger detached)\n\n";

    sensor.setTemperature(40);

    std::cout << "\n";
    tracker.report();
}
