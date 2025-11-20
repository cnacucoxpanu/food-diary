#ifndef PRODUCT_H
#define PRODUCT_H

#include "nutrition_item.h"

class Product : public NutritionItem {
public:
    Product();
    Product(int id, const std::string& name, double calories, double proteins, double fats, double carbs);
    ~Product();

    double getTotalCalories() const override;
    double getTotalProteins() const override;
    double getTotalFats() const override;
    double getTotalCarbs() const override;
    
    std::string getType() const override;
};

#endif