#ifndef DISH_H
#define DISH_H

#include "include/core/product.h"
#include <vector>

class Dish : public Product {
private:
    std::vector<std::pair<Product*, double>> ingredients; // продукт + количество в граммах

public:
    Dish();
    Dish(int id, const std::string& name);
    ~Dish();

    void addIngredient(Product* product, double quantity);
    void removeIngredient(int productId);
    
    // Переопределение методов для расчета на основе ингредиентов
    double getTotalCalories() const override;
    double getTotalProteins() const override;
    double getTotalFats() const override;
    double getTotalCarbs() const override;
    
    std::string getType() const override { return "DISH"; }
    
    const auto& getIngredients() const { return ingredients; }
};

#endif