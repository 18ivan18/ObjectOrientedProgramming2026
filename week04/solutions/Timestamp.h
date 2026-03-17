#ifndef TIMESTAMP_H
#define TIMESTAMP_H

class Timestamp
{
private:
    unsigned long totalSeconds;

public:
    Timestamp();
    Timestamp(int year, int month, int day);
    Timestamp(unsigned long seconds);

    unsigned long toSeconds() const;

    bool isBefore(const Timestamp &other) const;
    bool isAfter(const Timestamp &other) const;
};

Timestamp now();

#endif
