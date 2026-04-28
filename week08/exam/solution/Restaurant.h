#pragma once

#include "Order.h"
#include "Recipe.h"
#include <cstddef>

class Restaurant
{
private:
    Recipe *recipes;
    size_t recipeCount;
    size_t recipeCapacity;
    Order *pendingOrders;
    size_t pendingCount;
    size_t pendingCapacity;

    void freeAll();
    void ensureRecipeCapacity();
    void ensurePendingCapacity();
    void appendRecipe(const Recipe &recipe);
    void appendRecipe(Recipe &&recipe);
    void appendPendingOrder(const Order &order);
    void appendPendingOrder(Order &&order);
    const Recipe *findRecipeByName(const char *dishName) const;
    bool hasRecipeNamed(const char *name) const;

public:
    Restaurant();
    Restaurant(const char *recipesTextPath);
    Restaurant(const Restaurant &other);
    Restaurant(Restaurant &&other) noexcept;
    Restaurant &operator=(const Restaurant &other);
    Restaurant &operator=(Restaurant &&other) noexcept;
    ~Restaurant();

    void newOrder(const char *binaryOrdersPath, size_t orderIndex);
    void report(const char *outputTextPath) const;
};
