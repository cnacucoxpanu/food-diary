#ifndef NUTRITION_ITEM_H
#define NUTRITION_ITEM_H

#include <string>
#include <iostream>

class NutritionItem {
protected:
    int id;
    std::string name;
    double calories;
    double proteins;
    double fats;
    double carbs;

public:
    NutritionItem();
    NutritionItem(int id, const std::string& name, double calories, double proteins, double fats, double carbs);
    virtual ~NutritionItem() = default;

    virtual double getTotalCalories() const = 0;
    virtual double getTotalProteins() const = 0;
    virtual double getTotalFats() const = 0;
    virtual double getTotalCarbs() const = 0;
    
    virtual std::string getType() const = 0;
    
    int getId() const { return id; }
    std::string getName() const { return name; }
    double getBaseCalories() const { return calories; }
    double getBaseProteins() const { return proteins; }
    double getBaseFats() const { return fats; }
    double getBaseCarbs() const { return carbs; }

    void setName(const std::string& newName) { name = newName; }
    void setNutrition(double cal, double prot, double fat, double carb) {
        calories = cal; proteins = prot; fats = fat; carbs = carb;
    }
    
    friend std::ostream& operator<<(std::ostream& os, const NutritionItem& item);
};

#endif