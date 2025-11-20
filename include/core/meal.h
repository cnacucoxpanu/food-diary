#ifndef MEAL_H
#define MEAL_H

#include "../core/nutrition_item.h"
#include <ctime>
#include <iostream>

class Meal {
private:
    std::time_t timestamp;
    NutritionItem* item;
    double quantity;

public:
    Meal();
    Meal(NutritionItem* item, double quantity, std::time_t timestamp = std::time(0));
    ~Meal();
    
    std::time_t getTimestamp() const { return timestamp; }
    NutritionItem* getItem() const { return item; }
    double getQuantity() const { return quantity; }
    
    double getCalories() const { return item->getTotalCalories() * (quantity / 100.0); }
    double getProteins() const { return item->getTotalProteins() * (quantity / 100.0); }
    double getFats() const { return item->getTotalFats() * (quantity / 100.0); }
    double getCarbs() const { return item->getTotalCarbs() * (quantity / 100.0); }
    
    friend std::ostream& operator<<(std::ostream& os, const Meal& meal);
};

#endif