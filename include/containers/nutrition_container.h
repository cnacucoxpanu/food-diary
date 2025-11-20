#ifndef NUTRITION_CONTAINER_H
#define NUTRITION_CONTAINER_H

#include "../core/meal.h"
#include <map>
#include <vector>
#include <iostream>

class NutritionContainer {
private:
    std::map<std::time_t, std::vector<Meal>> dailyMeals;
    std::string currentUsername;

public:
    NutritionContainer();
    ~NutritionContainer();
    
    void setCurrentUser(const std::string& username);
    void addMeal(std::time_t date, NutritionItem* item, double quantity);
    void removeMeal(std::time_t date, int index);
    void editMeal(std::time_t date, int index, double newQuantity);
    
    const std::vector<Meal>& getMealsByDate(std::time_t date) const;
    double getTotalCalories(std::time_t date) const;
    double getTotalProteins(std::time_t date) const;
    double getTotalFats(std::time_t date) const;
    double getTotalCarbs(std::time_t date) const;
    
    double getAverageDailyCalories(std::time_t startDate, std::time_t endDate) const;
    void generateDailyReport(std::time_t date) const;
    void generatePeriodReport(std::time_t startDate, std::time_t endDate) const;
    
    bool loadFromFile(const std::string& filename);
    bool saveToFile(const std::string& filename) const;
    
    bool hasDate(std::time_t date) const;
    
    friend std::ostream& operator<<(std::ostream& os, const NutritionContainer& container);
};

#endif