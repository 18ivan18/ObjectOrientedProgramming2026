# Design Patterns

## Какво са Design Patterns?

Design patterns са **преизползваеми решения на често срещани проблеми** при проектирането на софтуер. Те не са готов код — по-скоро са шаблони (blueprints), които описват подход, приложим в различни контексти.

Формализирани са от "Gang of Four" (Gamma, Helm, Johnson, Vlissides) в книгата им "Design Patterns: Elements of Reusable Object-Oriented Software" (1994).

**Шаблон срещу алгоритъм:** Алгоритъмът е като готварска рецепта — дефинира ясен набор от стъпки за постигане на цел. Шаблонът е като архитектурен проект — описва резултата и структурата, но конкретната имплементация зависи от контекста. Кодът на един и същ шаблон в две различни програми може да изглежда съвсем различно.

**Защо да ги ползваме?**

- Говорим общ език: "ползвам Singleton" е по-ясно от дълго обяснение
- Доказани решения — изпитани в реални проекти
- Правят кода по-четим и по-лесен за промяна

## Видове Design Patterns

| Тип            | Цел                              | Примери                                |
| -------------- | -------------------------------- | -------------------------------------- |
| **Creational** | Как се създават обекти           | Singleton, Factory, Builder, Prototype |
| **Structural** | Как се композират класове/обекти | Adapter, Decorator, Facade, Composite  |
| **Behavioral** | Как обектите комуникират         | Command, Observer, Strategy, Iterator  |

---

## Singleton (Creational)

Singleton гарантира, че даден клас има **точно един екземпляр** и предоставя глобална точка за достъп до него.

**Кога да го ползваме:** Logger, конфигурация, pool от ресурси — навсякъде, където е нужен **контролиран достъп до споделен ресурс** (база данни, файл, хардуерен интерфейс).

Представи си, че вече имаш създаден обект и искаш да създадеш нов. Вместо нов обект, получаваш същия — без дори да го осъзнаваш. Това е невъзможно с обикновен конструктор (всяко `new` дава нов обект), затова Singleton го решава с `getInstance()`.

**Ключови елементи:**

- Частен (private) конструктор — предотвратява `new MyClass()` отвън
- Статичен частен член, пазещ единствения екземпляр
- Статичен публичен метод `getInstance()`

```cpp
class Logger {
    static Logger* instance;

    Logger() {}
    Logger(const Logger&) = delete;
    Logger& operator=(const Logger&) = delete;

public:
    static Logger* getInstance() {
        if (!instance) {
            instance = new Logger();
        }
        return instance;
    }

    void log(const char* msg) {
        std::cout << "[LOG] " << msg << "\n";
    }
};

Logger* Logger::instance = nullptr;

int main() {
    Logger::getInstance()->log("App started");
    Logger::getInstance()->log("Loading config...");
    // И двата извиквания връщат един и същи обект
}
```

Виж пълния пример: `examples/1-singleton/main.cpp`

**Singleton като базов клас (CRTP)**

Ако множество класове трябва да са Singleton, повтарящият се boilerplate (`static T* instance`, `nullptr` проверка, изтрит copy) може да се извлече в шаблонен базов клас:

```cpp
template<typename T>
class Singleton {
protected:
    Singleton() = default;
private:
    Singleton(const Singleton&) = delete;
    Singleton& operator=(const Singleton&) = delete;
public:
    static T& getInstance() {
        static T instance; // създава се веднъж при първото извикване (Meyers' Singleton)
        return instance;
    }
};
```

Всеки клас, наследяващ `Singleton<T>`, автоматично получава готов `getInstance()`:

```cpp
class Logger : public Singleton<Logger> {
    friend class Singleton<Logger>; // позволява на базата да извика частния конструктор
    Logger() {}
public:
    void log(const char* msg) { std::cout << "[LOG] " << msg << "\n"; }
};

int main() {
    Logger::getInstance().log("App started"); // забележи . вместо ->
    Logger::getInstance().log("Loading config...");
}
```

Две разлики спрямо ръчния вариант:
- `getInstance()` връща `T&` (референция), не `T*` — без проверки за `nullptr`, извикванията са с `.`
- **Meyers' Singleton** (`static T instance` вътре в метода) — инициализира се при първото извикване, унищожава се при изход от програмата; thread-safe от C++11 нататък

---

## Factory Method (Creational)

Factory методът делегира **създаването на обекти** на отделен метод или клас, като отделя създателя от конкретните продукти.

**Кога да го ползваме:** Когато знаем какъв интерфейс ни трябва, но конкретният тип се определя по runtime — например при четене от файл, потребителски избор, конфигурация.

**Ключови елементи:**

- Абстрактен базов клас (или интерфейс) — `Product`
- Конкретни класове — `ConcreteProductA`, `ConcreteProductB`
- Фабрика — `Factory::create(type)` връща `Product*`

```cpp
class Animal {
public:
    virtual void speak() const = 0;
    virtual ~Animal() {}
};

class Dog : public Animal {
public:
    void speak() const { std::cout << "Woof!\n"; }
};

class Cat : public Animal {
public:
    void speak() const { std::cout << "Meow!\n"; }
};

class AnimalFactory {
public:
    static Animal* create(const char* type) {
        if (std::strcmp(type, "dog") == 0) { return new Dog(); }
        if (std::strcmp(type, "cat") == 0) { return new Cat(); }
        return nullptr;
    }
};

int main() {
    Animal* a = AnimalFactory::create("dog");
    a->speak(); // Woof!
    delete a;
}
```

Виж пълния пример: `examples/2-factory/main.cpp`

---

## Command (Behavioral)

Command шаблонът **капсулира заявка като обект**. Това позволява:

- Поставяне на заявки в опашка или лог
- Поддръжка на **undo/redo**
- Параметризиране на обекти с операции

**Ключови елементи:**

- `Command` интерфейс с `execute()` и `undo()`
- Конкретни команди — знаят как да извикат _receiver_ обекта
- _Invoker_ — пази история от команди и управлява undo/redo

```cpp
class Command {
public:
    virtual void execute() = 0;
    virtual void undo() = 0;
    virtual ~Command() {}
};

class Counter {
    int value;
public:
    Counter() : value(0) {}
    void add(int n)      { value += n; }
    void subtract(int n) { value -= n; }
    int get() const      { return value; }
};

class AddCommand : public Command {
    Counter& counter;
    int amount;
public:
    AddCommand(Counter& c, int n) : counter(c), amount(n) {}
    void execute() { counter.add(amount); }
    void undo()    { counter.subtract(amount); }
};
```

Виж пълния пример: `examples/3-command/main.cpp`

---

## Задачи

### Задача 1 — Singleton: HighScoreBoard

Имплементирай `HighScoreBoard` Singleton за игра, който:

- Пази до 10 резултата (двойки `name` / `score`) в паметта
- При първото извикване на `getInstance()` зарежда резултатите от файл `scores.txt` (ако съществува)
- При всяко добавяне на нов резултат записва актуалния списък обратно във файла — така данните оцеляват между стартирания на програмата

Интерфейс:
```cpp
HighScoreBoard* board = HighScoreBoard::getInstance();
board->add("Alice", 4200);
board->add("Bob",   3800);
board->printTop(5);  // принтира до 5-те най-добри резултата, наредени низходящо
```

Изисквания:
- Невъзможно е да се създаде повече от един `HighScoreBoard`
- Ако списъкът е пълен (10 резултата), новият резултат измества най-ниския само ако е по-висок
- Демонстрирай, че при повторно стартиране на програмата резултатите се зареждат от файла

**Разширение — Singleton като базов клас:** Рефакторирай `HighScoreBoard` да наследява `Singleton<HighScoreBoard>` вместо да имплементира механиката ръчно. `getInstance()` трябва да връща `HighScoreBoard&`. Добави необходимото `friend` обявление и обнови извикванията от `->` на `.`.

---

### Задача 2 — Abstract Factory: UI теми

До момента Factory Method създаваше **един тип обект**. Abstract Factory надгражда идеята — тя създава **семейство от свързани обекти**, като гарантира, че всички те са съвместими помежду си.

**Пример:** UI библиотека с тъмна и светла тема. Ако изберем тъмна тема, искаме всички компоненти (бутони, чекбоксове, полета) да са от тъмната тема — не микс.

**Структура (hint):**

```
Button (abstract)       ←  DarkButton,  LightButton
TextBox (abstract)      ←  DarkTextBox, LightTextBox
Checkbox (abstract)     ←  DarkCheckbox, LightCheckbox

UIFactory (abstract)
  + createButton()   → Button*
  + createTextBox()  → TextBox*
  + createCheckbox() → Checkbox*

DarkThemeFactory  : UIFactory   (създава Dark-варианти)
LightThemeFactory : UIFactory   (създава Light-варианти)
```

Имплементирай горната структура. Всеки компонент има метод `render() const`, който принтира нещо от вида `[Dark] Button: Submit` / `[Light] Checkbox: ☐`.

Напиши функция `buildLoginForm(UIFactory& factory)`, която използва фабриката за да създаде и рендерира:
- един `Button` с надпис "Login"
- едно `TextBox` с placeholder "Username"
- едно `Checkbox` с надпис "Remember me"

Демонстрирай, че извикването на `buildLoginForm` с `DarkThemeFactory` и `LightThemeFactory` произвежда различен изход — без да се променя кодът на функцията.

---

### Задача 3 — Command: Интерактивен текстов редактор (CLI)

Имплементирай конзолен текстов редактор, работещ в цикъл: програмата чете команди от стандартния вход и ги изпълнява до получаване на `quit`.

**Команди:**

| Команда | Описание |
|---------|----------|
| `insert <pos> <char>` | Вмъква символ на позиция `pos` |
| `delete <pos>` | Трие символа на позиция `pos` |
| `replace <pos> <char>` | Заменя символа на позиция `pos` |
| `print` | Принтира текущото съдържание на буфера |
| `undo` | Отменя последната операция |
| `redo` | Повтаря последно отмененото |
| `quit` | Излиза от програмата |

**Примерна сесия:**
```
> insert 0 H
> insert 1 i
> insert 2 !
> print
Hi!
> delete 2
> print
Hi
> undo
> print
Hi!
> undo
> print
Hi
> redo
> print
Hi!
> quit
```

Изисквания:
- Всяка операция (`InsertCommand`, `DeleteCommand`, `ReplaceCommand`) имплементира `Command` интерфейса с `execute()` и `undo()`
- `TextEditor` пази `char` буфер и предоставя методи за вмъкване, триене и замяна
- `CommandHistory` управлява undo/redo стека — нова команда изтрива redo историята
- Невалидни позиции се игнорират с подходящо съобщение

---

### Задача 4 — CRTP: Уникален идентификатор

Много системи изискват всеки обект да има уникален числов идентификатор — game engine entities, записи в база данни, мрежови възли. Класическият C++ подход използва **статичен брояч в базовия клас**.

**Стъпка 1 — споделен брояч (въведение)**

Разгледай следния базов клас:

```cpp
class Entity {
    static int nextId;
    const int id;
public:
    Entity() : id(nextId++) {}
    Entity(const Entity&) : id(nextId++) {} // копието е нов обект — нов id
    int getId() const { return id; }
};
int Entity::nextId = 0;
```

```cpp
Entity a, b, c;
// a.getId() == 0,  b.getId() == 1,  c.getId() == 2
Entity d = a;    // копие — получава id 3, не 0
```

**Проблем:** ако `Animal` и `Vehicle` наследяват `Entity`, те споделят един брояч. `Animal` с id=5 и `Vehicle` с id=5 могат да съществуват едновременно — няма гаранция за уникалност в рамките на един и същ тип.

**Стъпка 2 — брояч per-клас с CRTP**

**CRTP (Curiously Recurring Template Pattern)** е техника, при която клас наследява шаблон, параметризиран със самия себе си:

```cpp
class Animal : public UniqueIdentifiable<Animal> { ... };
//                                       ^^^^^^
//                          Animal предава самия себе си като параметър
```

Резултатът: `UniqueIdentifiable<Animal>` и `UniqueIdentifiable<Vehicle>` са **различни класове** с **независими статични броячи**.

Имплементирай `UniqueIdentifiable<T>` така, че:
- `const int id` — задава се при конструиране, не може да се промени
- Конструктор по подразбиране — взима следващия id от брояча на `T`
- Копиращ конструктор — копието получава **нов** id (то е нов различен обект)
- Move конструктор — преместеният обект **запазва** id-то си
- `int getId() const`
- `static int count()` — връща колко инстанции на `T` са създадени досега

```cpp
Animal a1, a2, a3; // ids: 0, 1, 2
Vehicle v1, v2;    // ids: 0, 1  (собствен брояч, независим от Animal)

std::cout << Animal::count();  // 3
std::cout << Vehicle::count(); // 2

Animal a4 = a1;    // копие — a4.getId() == 3, Animal::count() == 4
Animal a5 = std::move(a4); // преместване — a5.getId() == 3 (запазва), Animal::count() == 4
```

Демонстрирай с поне два несвързани класа, че броячите им са независими.

Виж пълния пример: `examples/4-unique-id/main.cpp`
