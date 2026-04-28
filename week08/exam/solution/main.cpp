#include "Order.h"
#include "Restaurant.h"
#include <fstream>
#include <iostream>

bool writeOrdersBinary(const char *path, const Order *orders, size_t count)
{
    std::ofstream out(path, std::ios::binary);
    if (!out.is_open()) {
        return false;
    }
    out.write(reinterpret_cast<const char *>(&count), sizeof(count));
    for (size_t i = 0; i < count; i++) {
        if (!orders[i].serialize(out)) {
            return false;
        }
    }
    return out.good();
}

int main()
{
    const char *recipesPath = "recipes.txt";
    const char *ordersPath = "orders.bin";
    const char *reportPath = "report.txt";

    Order demo[3];

    demo[0].setTableNumber(5);
    demo[0].setTime(12, 30);
    demo[0].addDish("musaka");

    demo[1].setTableNumber(1);
    demo[1].setTime(26, 0);
    demo[1].addDish("musaka");

    demo[2].setTableNumber(3);
    demo[2].setTime(9, 15);
    demo[2].addDish("musaka");
    demo[2].addDish("fried eggs");

    if (!writeOrdersBinary(ordersPath, demo, 3)) {
        std::cerr << "Неуспешен запис на демо двоичен файл с поръчки.\n";
        return 1;
    }

    Restaurant restaurant(recipesPath);

    std::cout << "Добавяне на поръчка 0 (валидна)...\n";
    restaurant.newOrder(ordersPath, 0);

    std::cout << "Добавяне на поръчка 1 (очаква се отказ — невалидно време)...\n";
    restaurant.newOrder(ordersPath, 1);

    std::cout << "Добавяне на поръчка 2 (валидна)...\n";
    restaurant.newOrder(ordersPath, 2);

    std::cout << "Генериране на отчет в " << reportPath << "...\n";
    restaurant.report(reportPath);

    std::cout << "Готово.\n";
}
