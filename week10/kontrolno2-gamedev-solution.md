# Контролно 2 — Game Development Studio — Примерна архитектура

---

## Йерархия на класовете

```
Person
├── Designer<T>
└── Programmer

QABot<T>          (не наследява Person)
BugReport<T>
DevTeam<T>
GameProject<T>
Vector<S>

enum GameMode { SinglePlayer, Multiplayer, CoOp };
```

---

## Схема

```
┌───────────────────────────────────────────────┐
│                    Person                     │
├───────────────────────────────────────────────┤
│ private:                                      │
│   char* name                                  │
│   unsigned age                                │
│   bool sex                                    │
├───────────────────────────────────────────────┤
│ protected:                                    │
│   Person(const char* name,                    │
│           unsigned age, bool sex)             │
│   Person(const Person&)                       │
│   Person& operator=(const Person&)            │
│   Person(Person&&)                            │
│   Person& operator=(Person&&)                 │
│   ~Person()                                   │
│   void copyFrom(const Person&)                │
│   void clear()                                │
│   void moveFrom(Person&&)                     │
│   friend ostream& operator<<(ostream&,        │
│                    const Person&)             │
└───────────────────────────────────────────────┘
                       ▲
          ┌────────────┴────────────┐
          │                         │

┌─────────────────────────┐   ┌─────────────────────────┐
│      Designer<T>        │   │       Programmer        │
├─────────────────────────┤   ├─────────────────────────┤
│ private:                │   │ private:                │
│   char* degree          │   │   unsigned short rank   │
│   char* specialty       │   │   // 1–3                │
├─────────────────────────┤   ├─────────────────────────┤
│ public:                 │   │ public:                 │
│   Designer(...)         │   │   Programmer(...)       │
│   Designer(const        │   │   friend ostream&       │
│     Designer<T>&)       │   │   operator<<(ostream&,  │
│   Designer<T>&          │   │   const Programmer&)    │
│     operator=(const     │   └─────────────────────────┘
│     Designer<T>&)       │
│   Designer(Designer<T>&&)
│   Designer<T>&          │
│     operator=(          │
│     Designer<T>&&)      │
│   ~Designer()           │
│   bool analyze(const    │
│     BugReport<T>&) const│
│   friend ostream&       │
│   operator<<(ostream&,  │
│   const Designer<T>&)   │
└─────────────────────────┘

┌─────────────────────────────────────────────────────┐
│                      QABot<T>                       │
├─────────────────────────────────────────────────────┤
│ private:                                            │
│   unsigned id                                       │
│   Designer<T> creator                               │
│   unsigned batteryLevel                             │
│   unsigned reportsTaken                             │
├─────────────────────────────────────────────────────┤
│ public:                                             │
│   QABot(unsigned id, const Designer<T>& creator,   │
│          unsigned batteryLevel)                     │
│   QABot(const QABot<T>&)                            │
│   QABot<T>& operator=(const QABot<T>&)              │
│   QABot(QABot<T>&&)                                 │
│   QABot<T>& operator=(QABot<T>&&)                   │
│   ~QABot() = default                                │
│   BugReport<T> extractReport(                       │
│     GameMode mode, int complexity)                  │
│   friend ostream& operator<<(ostream&,              │
│                    const QABot<T>&)                 │
└─────────────────────────────────────────────────────┘

┌─────────────────────────────────────────────────────┐
│                    BugReport<T>                     │
├─────────────────────────────────────────────────────┤
│ private:                                            │
│   GameMode mode                                     │
│   int complexity                                    │
│   T moduleSample                                    │
│   unsigned id                                       │
├─────────────────────────────────────────────────────┤
│ public:                                             │
│   BugReport(unsigned id, const T& moduleSample,     │
│              GameMode mode, int complexity)          │
│   bool canBeTested(const char* specialty) const     │
│   friend ostream& operator<<(ostream&,              │
│                    const BugReport<T>&)             │
└─────────────────────────────────────────────────────┘

┌─────────────────────────────────────────────────────┐
│                     Vector<S>                       │
├─────────────────────────────────────────────────────┤
│ private:                                            │
│   S** array                                         │
│   size_t size                                       │
│   void resize(const size_t& newSize)                │
├─────────────────────────────────────────────────────┤
│ public:                                             │
│   Vector()                                          │
│   Vector(const Vector<S>&)                          │
│   Vector<S>& operator=(const Vector<S>&)            │
│   Vector(Vector<S>&&)                               │
│   Vector<S>& operator=(Vector<S>&&)                 │
│   ~Vector()                                         │
│   void push(const S& value)                         │
│   S& operator[](const size_t& index)                │
│   const S& operator[](const size_t& index) const    │
│   size_t length() const                             │
└─────────────────────────────────────────────────────┘

┌─────────────────────────────────────────────────────┐
│                    DevTeam<T>                       │
├─────────────────────────────────────────────────────┤
│ private:                                            │
│   Vector<Programmer> programmers                    │
│   Vector<QABot<T>> bots                             │
├─────────────────────────────────────────────────────┤
│ public:                                             │
│   DevTeam()                                         │
│   void addProgrammer(const Programmer&)             │
│   void addBot(const QABot<T>&)                      │
│   friend ostream& operator<<(ostream&,              │
│                    const DevTeam<T>&)               │
└─────────────────────────────────────────────────────┘

┌─────────────────────────────────────────────────────┐
│                  GameProject<T>                     │
├─────────────────────────────────────────────────────┤
│ private:                                            │
│   char* projectTitle                                │
│   DevTeam<T> devTeam                                │
│   Vector<Designer<T>> designTeam                    │
├─────────────────────────────────────────────────────┤
│ public:                                             │
│   GameProject(const char* title)                    │
│   GameProject(const GameProject<T>&)                │
│   GameProject<T>& operator=(const GameProject<T>&)  │
│   GameProject(GameProject<T>&&)                     │
│   GameProject<T>& operator=(GameProject<T>&&)       │
│   ~GameProject()                                    │
│   void addDesigner(const Designer<T>&)              │
│   void addProgrammer(const Programmer&)             │
│   void addBot(const QABot<T>&)                      │
│   friend ostream& operator<<(ostream&,              │
│                    const GameProject<T>&)           │
└─────────────────────────────────────────────────────┘
```

---

## Декларации с коментари

```cpp
enum GameMode { SinglePlayer, Multiplayer, CoOp };

// ─────────────────────────────────────────────────────────────
// Person — базов клас за всички участници с лични данни.
// Конструкторите са protected — Person не може да се
// инстанцира директно; само Designer и Programmer са конкретни.
// ─────────────────────────────────────────────────────────────
class Person {
    char* name;       // динамично заделено име с произволна дължина
    unsigned age;
    bool sex;
protected:
    void copyFrom(const Person& other); // копира name (ново заделяне), age, sex
    void clear();                       // освобождава name
    void moveFrom(Person&& other);      // прехвърля name, зануля other.name

    Person(const char* name, unsigned age, bool sex);
    Person(const Person& other);
    Person& operator=(const Person& other);
    Person(Person&& other);
    Person& operator=(Person&& other);
    ~Person();

    // извежда name, age, sex в os
    friend ostream& operator<<(ostream& os, const Person& obj);
};

// ─────────────────────────────────────────────────────────────
// Designer<T> — дизайнер; наследява Person.
// Притежава degree и specialty като динамични низове.
// ─────────────────────────────────────────────────────────────
template <typename T>
class Designer : public Person {
    char* degree;       // академична степен с произволна дължина
    char* specialty;    // специалност с произволна дължина

    void copyFrom(const Designer<T>& other); // копира degree и specialty
    void clear();                            // освобождава degree и specialty
    void moveFrom(Designer<T>&& other);      // прехвърля degree и specialty
public:
    Designer(const char* name, unsigned age, bool sex,
             const char* degree, const char* specialty);
    Designer(const Designer<T>& other);
    Designer<T>& operator=(const Designer<T>& other);
    Designer(Designer<T>&& other);
    Designer<T>& operator=(Designer<T>&& other);
    ~Designer();

    // извиква report.canBeTested(specialty) и връща резултата
    bool analyze(const BugReport<T>& report) const;

    // извежда Person данните, degree и specialty в os
    friend ostream& operator<<(ostream& os, const Designer<T>& obj);
};

// ─────────────────────────────────────────────────────────────
// Programmer — програмист; наследява Person.
// rank е стойностен тип — Big6 се наследява от Person.
// ─────────────────────────────────────────────────────────────
class Programmer : public Person {
    unsigned short rank;    // ниво на старшинство, 1–5
public:
    Programmer(const char* name, unsigned age, bool sex, unsigned short rank);

    // извежда Person данните и rank в os
    friend ostream& operator<<(ostream& os, const Programmer& obj);
};

// ─────────────────────────────────────────────────────────────
// QABot<T> — автономен бот за тестване; не е Person.
// Притежава creator по стойност — изисква Big6.
// ─────────────────────────────────────────────────────────────
template <typename T>
class QABot {
    unsigned id;
    Designer<T> creator;    // пълен обект — бота притежава копие
    unsigned batteryLevel;
    unsigned reportsTaken;  // брой извлечени доклади; използва се за генериране на ID
public:
    QABot(unsigned id, const Designer<T>& creator, unsigned batteryLevel);
    QABot(const QABot<T>& other);
    QABot<T>& operator=(const QABot<T>& other);
    QABot(QABot<T>&& other);
    QABot<T>& operator=(QABot<T>&& other);
    ~QABot() = default;

    // конструира T(mode, complexity), увеличава reportsTaken с 1,
    // връща BugReport с id = (id * 1000 + reportsTaken) и новия модул
    BugReport<T> extractReport(GameMode mode, int complexity);

    // извежда id, creator и batteryLevel в os
    friend ostream& operator<<(ostream& os, const QABot<T>& obj);
};

// ─────────────────────────────────────────────────────────────
// BugReport<T> — доклад за грешки, извлечен от игрови модул.
// ─────────────────────────────────────────────────────────────
template <typename T>
class BugReport {
    GameMode mode;      // режим на игра на модула
    int complexity;     // рейтинг на сложност на модула
    T moduleSample;     // копие на модула, от който е извлечен докладът
    unsigned id;        // идентификатор: botId * 1000 + поредност
public:
    BugReport(unsigned id, const T& moduleSample,
              GameMode mode, int complexity);

    // извиква moduleSample.canBeTested(specialty) и връща резултата
    bool canBeTested(const char* specialty) const;

    // извежда id, mode, complexity и moduleSample в os
    friend ostream& operator<<(ostream& os, const BugReport<T>& obj);
};

// ─────────────────────────────────────────────────────────────
// Vector<S> — динамичен масив с произволен тип.
// Използва масив от указатели за избягване на нарязване при
// полиморфни типове.
// ─────────────────────────────────────────────────────────────
template <typename S>
class Vector {
    S** array;      // динамично заделен масив от указатели
    size_t size;

    // преоразмерява вътрешния масив до newSize, копира съществуващите елементи
    void resize(const size_t& newSize);
public:
    Vector();
    Vector(const Vector<S>& other);
    Vector<S>& operator=(const Vector<S>& other);
    Vector(Vector<S>&& other);
    Vector<S>& operator=(Vector<S>&& other);
    ~Vector();

    // заделя ново копие на value, добавя указателя в края; извиква resize ако е необходимо
    void push(const S& value);

    S& operator[](const size_t& index);               // връща референция към елемент на позиция index
    const S& operator[](const size_t& index) const;   // константна версия на горното
    size_t length() const;                             // връща size
};

// ─────────────────────────────────────────────────────────────
// DevTeam<T> — екип за разработка: програмисти и QA ботове.
// ─────────────────────────────────────────────────────────────
template <typename T>
class DevTeam {
    Vector<Programmer> programmers;
    Vector<QABot<T>> bots;
public:
    DevTeam(); // инициализира двата вектора като празни

    // добавя копие на programmer в programmers чрез Vector::push
    void addProgrammer(const Programmer& programmer);

    // добавя копие на bot в bots чрез Vector::push
    void addBot(const QABot<T>& bot);

    // извежда всички програмисти и ботове в os
    friend ostream& operator<<(ostream& os, const DevTeam<T>& obj);
};

// ─────────────────────────────────────────────────────────────
// GameProject<T> — главен клас; обединява двата екипа.
// ─────────────────────────────────────────────────────────────
template <typename T>
class GameProject {
    char* projectTitle;             // динамично заделено наименование
    DevTeam<T> devTeam;
    Vector<Designer<T>> designTeam;

    void copyFrom(const GameProject<T>& other); // копира projectTitle, devTeam, designTeam
    void clear();                               // освобождава projectTitle
    void moveFrom(GameProject<T>&& other);      // прехвърля projectTitle, зануля other
public:
    // заделя projectTitle; двата екипа се инициализират като празни
    GameProject(const char* title);
    GameProject(const GameProject<T>& other);
    GameProject<T>& operator=(const GameProject<T>& other);
    GameProject(GameProject<T>&& other);
    GameProject<T>& operator=(GameProject<T>&& other);
    ~GameProject();

    // добавя копие на designer в designTeam чрез Vector::push
    void addDesigner(const Designer<T>& designer);

    // делегира към devTeam.addProgrammer
    void addProgrammer(const Programmer& programmer);

    // делегира към devTeam.addBot
    void addBot(const QABot<T>& bot);

    // извежда projectTitle, designTeam и devTeam в os
    friend ostream& operator<<(ostream& os, const GameProject<T>& obj);
};
```
