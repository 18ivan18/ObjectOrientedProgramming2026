#include "Recipe.h"
#include <cstring>
#include <new>
#include <utility>

void Recipe::freeProducts()
{
    for (size_t i = 0; i < productCount; i++) {
        delete[] products[i];
    }
    delete[] products;
    products = nullptr;
    productCount = 0;
    productCapacity = 0;
}

char *Recipe::copyStr(const char *s)
{
    if (s == nullptr) {
        return nullptr;
    }
    size_t len = std::strlen(s);
    char *p = new char[len + 1];
    strcpy(p, s);
    return p;
}

void Recipe::growProducts()
{
    size_t newCap = productCapacity == 0 ? 4 : productCapacity * 2;
    char **next = new char *[newCap];
    for (size_t i = 0; i < productCount; i++) {
        next[i] = products[i];
    }
    delete[] products;
    products = next;
    productCapacity = newCap;
}

Recipe::Recipe() : products(nullptr), productCount(0), productCapacity(0)
{
    dishName[0] = '\0';
}

Recipe::Recipe(const char *name) : products(nullptr), productCount(0), productCapacity(0)
{
    dishName[0] = '\0';
    if (name != nullptr && std::strlen(name) > 0) {
        setDishName(name);
    }
}

Recipe::Recipe(const Recipe &other) : products(nullptr), productCount(0), productCapacity(0)
{
    strcpy(dishName, other.dishName);
    for (size_t i = 0; i < other.productCount; i++) {
        addProduct(other.products[i]);
    }
}

Recipe::Recipe(Recipe &&other) noexcept
    : products(other.products), productCount(other.productCount), productCapacity(other.productCapacity)
{
    strcpy(dishName, other.dishName);
    other.dishName[0] = '\0';
    other.products = nullptr;
    other.productCount = 0;
    other.productCapacity = 0;
}

Recipe &Recipe::operator=(const Recipe &other)
{
    if (this != &other) {
        Recipe tmp(other);
        *this = std::move(tmp);
    }
    return *this;
}

Recipe &Recipe::operator=(Recipe &&other) noexcept
{
    if (this != &other) {
        freeProducts();
        strcpy(dishName, other.dishName);
        products = other.products;
        productCount = other.productCount;
        productCapacity = other.productCapacity;
        other.dishName[0] = '\0';
        other.products = nullptr;
        other.productCount = 0;
        other.productCapacity = 0;
    }
    return *this;
}

Recipe::~Recipe()
{
    freeProducts();
}

bool Recipe::setDishName(const char *name)
{
    if (name == nullptr) {
        return false;
    }
    size_t len = std::strlen(name);
    if (len > RECIPE_MAX_DISH_NAME_LEN) {
        return false;
    }
    std::strncpy(dishName, name, RECIPE_MAX_DISH_NAME_LEN);
    dishName[RECIPE_MAX_DISH_NAME_LEN] = '\0';
    return true;
}

bool Recipe::addProduct(const char *productName)
{
    if (productName == nullptr) {
        return false;
    }
    if (productCount == productCapacity) {
        growProducts();
    }
    products[productCount] = copyStr(productName);
    productCount++;
    return true;
}

const char *Recipe::getDishName() const
{
    return dishName;
}

size_t Recipe::getProductCount() const
{
    return productCount;
}

const char *Recipe::getProduct(size_t index) const
{
    if (index >= productCount) {
        return nullptr;
    }
    return products[index];
}
