#include "Restaurant.h"
#include <cstring>
#include <fstream>
#include <iostream>
#include <limits>
#include <new>
#include <utility>

const size_t LINE_BUF = 4096;

void Restaurant::freeAll()
{
    delete[] recipes;
    recipes = nullptr;
    recipeCount = 0;
    recipeCapacity = 0;
    delete[] pendingOrders;
    pendingOrders = nullptr;
    pendingCount = 0;
    pendingCapacity = 0;
}

Restaurant::Restaurant()
    : recipes(nullptr), recipeCount(0), recipeCapacity(0), pendingOrders(nullptr), pendingCount(0),
      pendingCapacity(0)
{
}

Restaurant::Restaurant(const char *recipesTextPath)
    : recipes(nullptr), recipeCount(0), recipeCapacity(0), pendingOrders(nullptr), pendingCount(0),
      pendingCapacity(0)
{
    if (recipesTextPath == nullptr) {
        std::cerr << "Грешка: липсва път до файл с рецепти.\n";
        return;
    }

    std::ifstream in(recipesTextPath);
    if (!in.is_open()) {
        std::cerr << "Грешка: не може да се отвори файлът с рецепти: " << recipesTextPath << '\n';
        return;
    }

    char line[LINE_BUF];
    std::size_t nRecipes = 0;
    if (!(in >> nRecipes)) {
        std::cerr << "Грешка: невалиден брой рецепти в началото на файла.\n";
        return;
    }
    in.ignore(std::numeric_limits<std::streamsize>::max(), '\n');

    for (std::size_t r = 0; r < nRecipes; r++) {
        if (!in.getline(line, LINE_BUF)) {
            std::cerr << "Грешка: неочакван край на файл при четене на рецепта.\n";
            freeAll();
            return;
        }
        {
            std::size_t n = std::strlen(line);
            if (n > 0 && line[n - 1] == '\r') {
                line[n - 1] = '\0';
            }
        }
        if (line[0] == '\0') {
            std::cerr << "Грешка: празно име на рецепта.\n";
            freeAll();
            return;
        }
        if (std::strlen(line) > RECIPE_MAX_DISH_NAME_LEN) {
            std::cerr << "Грешка: име на рецепта твърде дълго.\n";
            freeAll();
            return;
        }
        if (hasRecipeNamed(line)) {
            std::cerr << "Предупреждение: пропускане на дублирана рецепта \"" << line << "\".\n";
            std::size_t skipM = 0;
            if (!(in >> skipM)) {
                freeAll();
                return;
            }
            in.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
            for (std::size_t p = 0; p < skipM; p++) {
                if (!in.getline(line, LINE_BUF)) {
                    freeAll();
                    return;
                }
            }
            continue;
        }

        Recipe recipe;
        if (!recipe.setDishName(line)) {
            std::cerr << "Грешка: невалидно име на ястие.\n";
            freeAll();
            return;
        }

        std::size_t m = 0;
        if (!(in >> m)) {
            std::cerr << "Грешка: невалиден брой продукти.\n";
            freeAll();
            return;
        }
        in.ignore(std::numeric_limits<std::streamsize>::max(), '\n');

        for (std::size_t p = 0; p < m; p++) {
            if (!in.getline(line, LINE_BUF)) {
                std::cerr << "Грешка: липсва ред с продукт.\n";
                freeAll();
                return;
            }
            {
                std::size_t n = std::strlen(line);
                if (n > 0 && line[n - 1] == '\r') {
                    line[n - 1] = '\0';
                }
            }
            if (!recipe.addProduct(line)) {
                std::cerr << "Грешка: неуспешно добавяне на продукт.\n";
                freeAll();
                return;
            }
        }

        appendRecipe(recipe);
    }
}

Restaurant::Restaurant(const Restaurant &other)
    : recipes(nullptr), recipeCount(0), recipeCapacity(0), pendingOrders(nullptr), pendingCount(0),
      pendingCapacity(0)
{
    for (size_t i = 0; i < other.recipeCount; i++) {
        appendRecipe(other.recipes[i]);
    }
    for (size_t i = 0; i < other.pendingCount; i++) {
        appendPendingOrder(other.pendingOrders[i]);
    }
}

Restaurant::Restaurant(Restaurant &&other) noexcept
    : recipes(other.recipes),
      recipeCount(other.recipeCount),
      recipeCapacity(other.recipeCapacity),
      pendingOrders(other.pendingOrders),
      pendingCount(other.pendingCount),
      pendingCapacity(other.pendingCapacity)
{
    other.recipes = nullptr;
    other.recipeCount = 0;
    other.recipeCapacity = 0;
    other.pendingOrders = nullptr;
    other.pendingCount = 0;
    other.pendingCapacity = 0;
}

Restaurant &Restaurant::operator=(const Restaurant &other)
{
    if (this != &other) {
        Restaurant tmp(other);
        *this = std::move(tmp);
    }
    return *this;
}

Restaurant &Restaurant::operator=(Restaurant &&other) noexcept
{
    if (this != &other) {
        freeAll();
        recipes = other.recipes;
        recipeCount = other.recipeCount;
        recipeCapacity = other.recipeCapacity;
        pendingOrders = other.pendingOrders;
        pendingCount = other.pendingCount;
        pendingCapacity = other.pendingCapacity;
        other.recipes = nullptr;
        other.recipeCount = 0;
        other.recipeCapacity = 0;
        other.pendingOrders = nullptr;
        other.pendingCount = 0;
        other.pendingCapacity = 0;
    }
    return *this;
}

Restaurant::~Restaurant()
{
    freeAll();
}

void Restaurant::ensureRecipeCapacity()
{
    if (recipeCount < recipeCapacity) {
        return;
    }
    size_t newCap = recipeCapacity == 0 ? 4 : recipeCapacity * 2;
    Recipe *next = new Recipe[newCap];
    for (size_t i = 0; i < recipeCount; i++) {
        next[i] = std::move(recipes[i]);
    }
    delete[] recipes;
    recipes = next;
    recipeCapacity = newCap;
}

void Restaurant::ensurePendingCapacity()
{
    if (pendingCount < pendingCapacity) {
        return;
    }
    size_t newCap = pendingCapacity == 0 ? 4 : pendingCapacity * 2;
    Order *next = new Order[newCap];
    for (size_t i = 0; i < pendingCount; i++) {
        next[i] = std::move(pendingOrders[i]);
    }
    delete[] pendingOrders;
    pendingOrders = next;
    pendingCapacity = newCap;
}

void Restaurant::appendRecipe(const Recipe &recipe)
{
    ensureRecipeCapacity();
    recipes[recipeCount] = recipe;
    recipeCount++;
}

void Restaurant::appendRecipe(Recipe &&recipe)
{
    ensureRecipeCapacity();
    recipes[recipeCount] = std::move(recipe);
    recipeCount++;
}

void Restaurant::appendPendingOrder(const Order &order)
{
    ensurePendingCapacity();
    pendingOrders[pendingCount] = order;
    pendingCount++;
}

void Restaurant::appendPendingOrder(Order &&order)
{
    ensurePendingCapacity();
    pendingOrders[pendingCount] = std::move(order);
    pendingCount++;
}

const Recipe *Restaurant::findRecipeByName(const char *dishName) const
{
    if (dishName == nullptr) {
        return nullptr;
    }
    for (size_t i = 0; i < recipeCount; i++) {
        if (std::strcmp(recipes[i].getDishName(), dishName) == 0) {
            return recipes + i;
        }
    }
    return nullptr;
}

bool Restaurant::hasRecipeNamed(const char *name) const
{
    return findRecipeByName(name) != nullptr;
}

void Restaurant::newOrder(const char *binaryOrdersPath, size_t orderIndex)
{
    if (binaryOrdersPath == nullptr) {
        std::cerr << "Грешка: липсва път до двоичен файл с поръчки.\n";
        return;
    }

    std::ifstream in(binaryOrdersPath, std::ios::binary);
    if (!in.is_open()) {
        std::cerr << "Грешка: двоичният файл не съществува или не може да се отвори: " << binaryOrdersPath
                  << '\n';
        return;
    }

    size_t orderCount = 0;
    in.read(reinterpret_cast<char *>(&orderCount), sizeof(orderCount));
    if (!in) {
        std::cerr << "Грешка: неуспешно четене на брой поръчки от двоичния файл.\n";
        return;
    }

    if (orderIndex >= orderCount) {
        std::cerr << "Грешка: номерът на поръчката е извън диапазона (има " << orderCount << " поръчки).\n";
        return;
    }

    for (size_t i = 0; i < orderIndex; i++) {
        if (!skipOrderSerialized(in)) {
            std::cerr << "Грешка: повреден двоичен файл при прескачане към поръчка " << orderIndex << ".\n";
            return;
        }
    }

    Order loaded;
    if (!loaded.deserialize(in)) {
        std::cerr << "Грешка: неуспешно четене на поръчка от двоичния файл.\n";
        return;
    }

    if (!loaded.isValid()) {
        std::cerr << "Поръчката е невалидна (невалидно време) и няма да бъде добавена.\n";
        return;
    }

    appendPendingOrder(std::move(loaded));
}

void Restaurant::report(const char *outputTextPath) const
{
    if (outputTextPath == nullptr) {
        std::cerr << "Грешка: липсва път за изходен отчет.\n";
        return;
    }

    std::ofstream out(outputTextPath);
    if (!out.is_open()) {
        std::cerr << "Грешка: не може да се създаде изходният файл: " << outputTextPath << '\n';
        return;
    }

    out << "Брой поръчки за изпълнение: " << pendingCount << "\n\n";

    for (size_t o = 0; o < pendingCount; o++) {
        const Order &ord = pendingOrders[o];
        out << "--- Поръчка " << (o + 1) << " ---\n";
        out << "Маса: " << ord.getTableNumber() << '\n';
        unsigned h = 0;
        unsigned m = 0;
        ord.getTime(h, m);
        out << "Час: " << h << ':' << m << '\n';
        out << "Ястия и продукти:\n";

        for (size_t d = 0; d < ord.getDishCount(); d++) {
            const char *dname = ord.getDishName(d);
            out << "  * " << dname << '\n';
            const Recipe *rec = findRecipeByName(dname);
            if (rec == nullptr) {
                out << "      (няма рецепта в ресторанта)\n";
            } else {
                out << "      Продукти: ";
                for (size_t p = 0; p < rec->getProductCount(); p++) {
                    if (p > 0) {
                        out << " | ";
                    }
                    out << rec->getProduct(p);
                }
                out << '\n';
            }
        }
        out << '\n';
    }
}
