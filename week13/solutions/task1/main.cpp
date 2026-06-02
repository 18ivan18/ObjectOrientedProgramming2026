#include <iostream>
#include "Averager.h"
#include "MovingAverager.h"
#include "PeriodicSampler.h"
#include "SimplePublisher.h"
#include "BacklogPublisher.h"
#include "Repository.h"

int main() {
    // --- Example from the task description ---
    Averager* avg      = new Averager("id1");
    MovingAverager* movAvg = new MovingAverager("id2", 5);
    PeriodicSampler* perSam = new PeriodicSampler("id3", 3);

    SimplePublisher pub;
    pub.subscribe(avg);
    pub.subscribe(movAvg);
    pub.subscribe(perSam);

    for (int i = 1; i <= 9; i++) {
        pub.signal(Message(i));
    }

    std::cout << "Averager (1..9):       " << avg->read()    << "\n"; // 5
    std::cout << "MovingAverager (5..9): " << movAvg->read() << "\n"; // 7
    std::cout << "PeriodicSampler:       " << perSam->read() << "\n"; // 7

    pub.unsubscribe(movAvg);
    pub.signal(Message(100));
    std::cout << "Averager after +100:   " << avg->read()    << "\n"; // 14.5
    std::cout << "MovingAverager (unsubscribed, still 7): " << movAvg->read() << "\n";

    delete avg;
    delete movAvg;
    delete perSam;

    // --- BacklogPublisher: late subscriber receives all past messages ---
    std::cout << "\n--- BacklogPublisher ---\n";
    BacklogPublisher backlogPub;
    backlogPub.signal(Message(10));
    backlogPub.signal(Message(20));
    backlogPub.signal(Message(30));

    Averager* lateJoiner = new Averager("late");
    backlogPub.subscribe(lateJoiner); // immediately receives 10, 20, 30
    std::cout << "Late joiner avg (10,20,30): " << lateJoiner->read() << "\n"; // 20

    backlogPub.signal(Message(40));
    std::cout << "After one more message:     " << lateJoiner->read() << "\n"; // 25
    delete lateJoiner;

    // --- Repository ---
    std::cout << "\n--- Repository ---\n";
    Repository repo;
    repo.add(new Averager("sensor-a"));
    repo.add(new MovingAverager("sensor-b", 3));

    SimplePublisher pub2;
    pub2.subscribe(repo.get("sensor-a"));
    pub2.subscribe(repo.get("sensor-b"));

    pub2.signal(Message(100));
    pub2.signal(Message(200));
    pub2.signal(Message(300));

    std::cout << "sensor-a avg:     " << repo.get("sensor-a")->read() << "\n"; // 200
    std::cout << "sensor-b avg(3):  " << repo.get("sensor-b")->read() << "\n"; // 200

    // dynamic_cast to access subscriber-specific interface
    MovingAverager* mb = dynamic_cast<MovingAverager*>(repo.get("sensor-b"));
    if (mb) {
        std::cout << "sensor-b windowSize: " << mb->windowSize << "\n"; // 3
    }
}
