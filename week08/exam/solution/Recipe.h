#pragma once

#include <cstddef>

const std::size_t RECIPE_MAX_DISH_NAME_LEN = 127;

class Recipe
{
private:
    char dishName[RECIPE_MAX_DISH_NAME_LEN + 1];
    char **products;
    size_t productCount;
    size_t productCapacity;

    void freeProducts();
    void growProducts();
    char *copyStr(const char *s);

public:
    Recipe();
    Recipe(const char *name);
    Recipe(const Recipe &other);
    Recipe(Recipe &&other) noexcept;
    Recipe &operator=(const Recipe &other);
    Recipe &operator=(Recipe &&other) noexcept;
    ~Recipe();

    bool setDishName(const char *name);
    bool addProduct(const char *productName);

    const char *getDishName() const;
    size_t getProductCount() const;
    const char *getProduct(size_t index) const;
};
