#ifndef PRODUCT_CONTAINER_H
#define PRODUCT_CONTAINER_H

#include "../core/nutrition_item.h"
#include "../core/product.h"
#include "../core/dish.h"
#include <vector>
#include <memory>
#include <iostream>

class ProductContainer {
private:
    std::vector<std::unique_ptr<NutritionItem>> items;
    int nextId;

public:
    ProductContainer();
    ~ProductContainer();
    
    Product* addProduct(const std::string& name, double calories, double proteins, double fats, double carbs);
    Product* addProductWithId(int id, const std::string& name, double calories, double proteins, double fats, double carbs);
    Dish* addDish(const std::string& name);
    bool removeItem(int id);
    NutritionItem* findItem(int id);
    Product* findProductByName(const std::string& name);
    
    bool loadFromFile(const std::string& filename);
    bool saveToFile(const std::string& filename) const;
    
    const auto& getAllItems() const { return items; }
    friend std::ostream& operator<<(std::ostream& os, const ProductContainer& container);
};

#endif