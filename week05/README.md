## Copy конструктор

Конструктор с параметър от тип `const <името-на-класа>&`. Като конструктор има инициализиращ списък. Целта му е да създаде нов обект със стойности на полетата същите като тези на другия подаден. Ако бъде пропуснат ще се генерира автоматично такъв от компилатора, който прави т. нар. `shallow copy`.

### Синтаксис

```c++
class Test {
private:
    int i;
    double d;
public:
    Test(const Test& other): i{other.i}, d{other.d} {}
};
```

### Кога се извиква

- При създаване на нови обекти от други обекти.
- Неявно при създаване на нов локален обект за дадена функция.
- При връщане на копие на обект от фунцкия

```c++
void doSomethingWithTest(Test t) {

}

Test doSomethingElseWithTest(Test t) {
    return t;
}

int main() {
    Test t, t1(t), t2 = t1;
}
```

## Оператор =

Дясно асоциативен оператор за присвояване на стойност на вече съществуващ обект. След извърване на промените по текущия обект, той се връща. Това позволява наслагване на равенство между няколко обекта.

### Синтаксис

```c++
class Test {
private:
    int i;
    double d;
public:
    // стандартна имплементация на operator=
    Test& operator=(const Test& rhs) {
        if(this != &rhs) {
            i = rhs.i;
            d = rhs.d;
        }
        return *this;
    }
};
```

### Кога се извиква

При присвояване на нова стойност на вече съществуващ обект.

```c++
int main() {
    Test t, t1(t), t2 = t1;
    t = t1;
    t = t1 = t2; // same as t.operator=(t1.operator=(t2));
}
```

## Shallow vs deep copy

Когато откопираме данните на обекти обикновено искаме всеки обект да разполага сам с паметта на данните си. Това означава да се заделя памет при създаване на обекта и да се изтрива при унищожаването му.

### Shallow copy

```c++
class Test {
private:
    int i;
    double d;
    char* name;
public:
    // shallow copy - the memory for name is now shared between this and other
    Test(const Test& other): i{other.i}, d{other.d}, name{other.name} {}
    Test& operator=(const Test& rhs) {
        i = rhs.i;
        d = rhs.d;
        name = rhs.name;
        return *this;
    }
};
```

### Deep copy

```c++
class Test {
private:
    int i;
    double d;
    char* name;
public:
    // deep copy - we now manage our own memory
    Test(const Test& other): i{other.i}, d{other.d}, name{new char[strlen(other.name) + 1]} {
        strcpy(name, other.name);
    }
    Test& operator=(const Test& rhs) {
        if(this != &rhs) {
            i = rhs.i;
            d = rhs.d;
            // here name already exists so we have to manage the memory first
            delete[] name;
            name = new char[strlen(other.name) + 1];
            strcpy(name, other.name);
        }
        return *this;
    }
};
```

## Предефиниране на оператори

### Syntax

Overloaded operators are functions with special function names:

## **operator op**

overloaded operator;

op - any of the following operators: `+` `-` `*` `/` `%` `^` `&` `|` `~` `!` `=` `<` `>` `+=` `-=` `*=` `/=` `%=` `^=` `&=` `|=` `<<` `>>` `>>=` `<<=` `==` `!=` `<=` `>=` `<=>` (since C++20) `&&` `||` `++` `--` `,` `->*` `->` `(` `)` `[` `]`

## **operator type**

user-defined conversion function;

Restrictions

- The operators :: (scope resolution), . (member access), .\* (member access through pointer to member), and ?: (ternary conditional) cannot be overloaded.
- New operators such as \*\*, <>, or &| cannot be created.
- It is not possible to change the precedence, grouping, or number of operands of operators.
- The overload of operator -> must either return a raw pointer, or return an object (by reference or by value) for which operator -> is in turn overloaded.

## **Stream extraction and insertion**

The overloads of `operator>>` and `operator<<` that take a `std::istream&` or `std::ostream&` as the left hand argument are known as insertion and extraction operators. Since they take the user-defined type as the right argument (b in a@b), they must be implemented as non-members.

```c++
std::ostream& operator<<(std::ostream& os, const T& obj)
{
    // write obj to stream
    return os;
}

std::istream& operator>>(std::istream& is, T& obj)
{
    // read obj from stream
    if( /* T could not be constructed */ )
        is.setstate(std::ios::failbit);
    return is;
}
```

These operators are sometimes implemented as friend functions.

# Задачи

## Задача 1

Напишете клас `Laptop`. Един лаптоп се нуждае от марка и модел (стринг с произволна дължина), цена, размер на екрана (в инчове), процесор (помислете как да представите процесора с нужните му характеристики - тактова честота, брой ядра и размер на КЕШ паметта), РАМ памет и капацитет на батерията. Напишете следните специални методи:

- Конструктор по подразбиране
- Конструктор за копиране
- Конструктор(и) с параметри, данните за един лаптоп
- Оператор за присвояване
- Деструктор
- Оператори <, >, ==, != за сравнение на размерите на екраните на два лаптопа

Напишете подходящи методи за upgrade на процесора и РАМ-а, както и метод за подходящо принтиране на информацията.

## Задача 2

Напишете клас `ToDo`, който описва задача, която трябва да се изпълни. Всяка задача си има id, описание и индикатор за това дали тя е изпълнена или не. Напишете следните специални методи на класа:

- Конструктор по подразбиране
- Конструктор за копиране
- Оператор за присвояване
- Деструктор

Напишете метод за изпълнение на задачата.

**Надграждане – клас ToDoList:** Създайте клас `ToDoList`, контейнер за `ToDo` задачи. Осигурете уникалност на id при добавяне – ако задача с дадено id вече съществува, не се добавя. Реализирайте методи за връщане на списък с изпълнени задачи и списък с неизпълнени задачи (всеки метод връща масив от копия на задачите и броя им чрез изходен параметър; извикващият отговаря за освобождаването на паметта).

## Задача 3

Напишете клас `SharedNote`, представляващ споделена бележка, която може да се преглежда и редактира от множество обекти едновременно. Съдържанието (символен низ) се споделя между всички копия на обекта – при копиране използвайте **shallow copy**, така че промяна чрез един обект да се отразява при всички останали.

Реализирайте конструктор по подразбиране, конструктор с параметър (съдържание), конструктор за копиране (shallow), оператор за присвояване (shallow), деструктор. Използвайте броене на референции за коректно освобождаване на паметта – когато последният обект, сочещ към съдържанието, се унищожи, паметта се освобождава.

Методи: `getContent()`, `setContent(const char*)`, `append(const char*)`.
