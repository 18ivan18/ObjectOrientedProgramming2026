# Примери: файлове и типични постановки (седмица 7)

## Фиксирано поле за име (`char name[64]` в `Record`)

Общата структура [`Record`](Record.h) е **без динамична памет вътре в обекта**, за да може да се записва със `read`/`write` в двоичен файл на целия `Record`. За текстов формат: ред на запис `id|score|име` (името не трябва да съдържа `|`).

Парсването на ред без `sscanf` е в [`parse_record_line.h`](parse_record_line.h) (`strchr`, `atoi`, `atof`, `strncpy`).

За текстов файл и конзола се преизползват **`operator<<` и `operator>>`** като **свободни функции** (не членове, не `friend`) — [`RecordTextFormat.h`](RecordTextFormat.h) за `Record`, [`RecordDynamicTextFormat.h`](RecordDynamicTextFormat.h) за `RecordDynamic`. Те ползват само публичните **get/set** методи. Полетата в класовете са **private**; създаване с **конструктор** `Record(id, score, name)` / `RecordDynamic(...)`.

Така записът във файл и отпечатването са еднакви: `out << r << '\n';`, `std::cout << r << '\n';`.

**Статичен vs динамичен масив (текст):** форматът е един и същ — брой записи + редове; при фиксиран максимум четете в `Record arr[MAX]`, при неизвестен брой — `new Record[n]`. Примерът по-долу показва само динамичния вариант.

| Файл | Постановка |
|------|------------|
| [`text_dynamic_array.cpp`](text_dynamic_array.cpp) | Текстов файл: брой записи + редове; при зареждане **`new Record[n]`**. |
| [`binary_single_object.cpp`](binary_single_object.cpp) | Един `Record` в двоичен файл — `write`/`read` на `sizeof(Record)`. |
| [`binary_fixed_array.cpp`](binary_fixed_array.cpp) | **Статичен** масив с фиксиран `N` — един блок `sizeof(масив)`. |
| [`binary_dynamic_array.cpp`](binary_dynamic_array.cpp) | Първо `size_t` **брой**, после `count * sizeof(Record)`; при четене — `new Record[count]`. |

## Без конструктор по подразбиране ([`StrictRecord`](StrictRecord.h))

Ако класът има **само** конструктор с параметри, `new StrictRecord[count]` не е приложимо, когато `count` идва от файл. Обичайният подход е **динамичен масив от указатели** `StrictRecord**`: заделя се `new StrictRecord*[count]`, за всеки ред се прави `arr[i] = new StrictRecord(id, score, name)` след парсване; освобождаване — `delete arr[i]` за всеки индекс, после `delete[] arr`. В [`text_dynamic_array_strict.cpp`](text_dynamic_array_strict.cpp) е показано това, заедно с [`StrictRecordTextFormat.h`](StrictRecordTextFormat.h) (само `operator<<` за ред във файл).

## Динамично име (`char*` — клас [`RecordDynamic`](RecordDynamic.h))

Тук **не** може да се запише целият обект с един `write` — указателят към името няма смисъл след зареждане от файл. Текстовият формат остава `id|score|име`. В двоичен вид вижте [`binary_io_dynamic_name.h`](binary_io_dynamic_name.h): записват се `id`, `score`, **дължина на името**, после байтовете на низа.

| Файл | Постановка |
|------|------------|
| [`text_dynamic_array_dynamic_name.cpp`](text_dynamic_array_dynamic_name.cpp) | Текст с `RecordDynamic`: **същият** формат и идея като при `Record`; при зареждане `new RecordDynamic[n]`. |
| [`binary_single_object_dynamic_name.cpp`](binary_single_object_dynamic_name.cpp) | Един `RecordDynamic` в двоичен файл. |
| [`binary_fixed_array_dynamic_name.cpp`](binary_fixed_array_dynamic_name.cpp) | Статичен масив с известен `N` — **N пъти** последователен запис (променлива дължина на всеки ред във файла). |
| [`binary_dynamic_array_dynamic_name.cpp`](binary_dynamic_array_dynamic_name.cpp) | Първо `count`, после `count` пъти запис в същия двоичен формат. |

## Компилиране (от тази директория)

```bash
g++ -std=c++17 -o text_dyn text_dynamic_array.cpp && ./text_dyn
g++ -std=c++17 -o bin_one binary_single_object.cpp && ./bin_one
g++ -std=c++17 -o bin_fixed binary_fixed_array.cpp && ./bin_fixed
g++ -std=c++17 -o bin_dyn binary_dynamic_array.cpp && ./bin_dyn

g++ -std=c++17 -o text_dyn_strict text_dynamic_array_strict.cpp && ./text_dyn_strict

g++ -std=c++17 -o text_dyn_dn text_dynamic_array_dynamic_name.cpp && ./text_dyn_dn
g++ -std=c++17 -o bin_one_dn binary_single_object_dynamic_name.cpp && ./bin_one_dn
g++ -std=c++17 -o bin_fixed_dn binary_fixed_array_dynamic_name.cpp && ./bin_fixed_dn
g++ -std=c++17 -o bin_dyn_dn binary_dynamic_array_dynamic_name.cpp && ./bin_dyn_dn
```

## Бележки за задачи

- **Текст**: форматът е удобен за четене от човек и за дебъг; трябва ясно правило за разделители и за полета с интервали.
- **Двоичен с фиксиран `Record`**: не записвайте класове с указатели към динамична памет — „както е в RAM“ указателите няма да са валидни след зареждане.
- **Двоичен с динамично име**: записвайте дължина + байтове; при `size_t` за брой/дължини файлът може да не е преносим между платформи — за устойчиви формати се ползват фиксирани ширини (напр. `uint32_t`).
