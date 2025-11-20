#ifndef NUTRITION_CALCULATOR_H
#define NUTRITION_CALCULATOR_H

#include "../core/meal.h"
#include "../core/user.h"
#include <vector>

class NutritionCalculator {
public:
    static double calculateTotalCalories(const std::vector<Meal>& meals);
    static double calculateTotalProteins(const std::vector<Meal>& meals);
    static double calculateTotalFats(const std::vector<Meal>& meals);
    static double calculateTotalCarbs(const std::vector<Meal>& meals);

    static double calculateBMR(double weight, double height, int age, bool isMale);
    static double calculateDailyCalories(double bmr, ActivityLevel activity, Goal goal);
};

#endif