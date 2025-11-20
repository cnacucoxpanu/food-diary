#include "../../header.h"

Product::Product() : NutritionItem() {}

Product::Product(int id, const std::string& name, double calories, 
                double proteins, double fats, double carbs)
    : NutritionItem(id, name, calories, proteins, fats, carbs) {}

Product::~Product() {}

double Product::getTotalCalories() const { return calories; }
double Product::getTotalProteins() const { return proteins; }
double Product::getTotalFats() const { return fats; }
double Product::getTotalCarbs() const { return carbs; }

std::string Product::getType() const { return "PRODUCT"; }