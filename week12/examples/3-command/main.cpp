#include <iostream>

class Command {
public:
    virtual void execute() = 0;
    virtual void undo() = 0;
    virtual ~Command() {}
};

// Receiver
class Counter {
    int value;
public:
    Counter() : value(0) {}
    void add(int n)      { value += n; }
    void subtract(int n) { value -= n; }
    int get() const      { return value; }
};

// Concrete commands
class AddCommand : public Command {
    Counter& counter;
    int amount;
public:
    AddCommand(Counter& c, int n) : counter(c), amount(n) {}
    void execute() { counter.add(amount); }
    void undo()    { counter.subtract(amount); }
};

class SubtractCommand : public Command {
    Counter& counter;
    int amount;
public:
    SubtractCommand(Counter& c, int n) : counter(c), amount(n) {}
    void execute() { counter.subtract(amount); }
    void undo()    { counter.add(amount); }
};

// Invoker — пази историята и управлява undo/redo
class CommandHistory {
    static const int MAX = 100;
    Command* history[MAX];
    int size;
    int current; // индекс на последно изпълнената команда

public:
    CommandHistory() : size(0), current(-1) {}

    void execute(Command* cmd) {
        // Изтрий всичко след текущата позиция (redo историята)
        for (int i = current + 1; i < size; i++) {
            delete history[i];
        }
        size = current + 1;

        cmd->execute();
        history[size++] = cmd;
        current = size - 1;
    }

    void undo() {
        if (current < 0) {
            std::cout << "(nothing to undo)\n";
            return;
        }
        history[current--]->undo();
    }

    void redo() {
        if (current == size - 1) {
            std::cout << "(nothing to redo)\n";
            return;
        }
        history[++current]->execute();
    }

    ~CommandHistory() {
        for (int i = 0; i < size; i++) {
            delete history[i];
        }
    }
};

int main() {
    Counter counter;
    CommandHistory history;

    history.execute(new AddCommand(counter, 10));
    std::cout << "After +10:   " << counter.get() << "\n";  // 10

    history.execute(new AddCommand(counter, 5));
    std::cout << "After +5:    " << counter.get() << "\n";  // 15

    history.execute(new SubtractCommand(counter, 3));
    std::cout << "After -3:    " << counter.get() << "\n";  // 12

    history.undo();
    std::cout << "After undo:  " << counter.get() << "\n";  // 15

    history.undo();
    std::cout << "After undo:  " << counter.get() << "\n";  // 10

    history.redo();
    std::cout << "After redo:  " << counter.get() << "\n";  // 15

    history.execute(new AddCommand(counter, 100));
    std::cout << "After +100:  " << counter.get() << "\n";  // 115

    // Redo сега не е наличен — новата команда изтри redo историята
    history.redo();                                          // (nothing to redo)
}
