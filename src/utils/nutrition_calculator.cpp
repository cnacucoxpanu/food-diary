#include "../../header.h"

double NutritionCalculator::calculateTotalCalories(const std::vector<Meal>& meals) {
    double total = 0;
    for (const auto& meal : meals) {
        total += meal.getCalories();
    }
    return total;
}

double NutritionCalculator::calculateTotalProteins(const std::vector<Meal>& meals) {
    double total = 0;
    for (const auto& meal : meals) {
        total += meal.getProteins();
    }
    return total;
}

double NutritionCalculator::calculateTotalFats(const std::vector<Meal>& meals) {
    double total = 0;
    for (const auto& meal : meals) {
        total += meal.getFats();
    }
    return total;
}

double NutritionCalculator::calculateTotalCarbs(const std::vector<Meal>& meals) {
    double total = 0;
    for (const auto& meal : meals) {
        total += meal.getCarbs();
    }
    return total;
}

double NutritionCalculator::calculateBMR(double weight, double height, int age, bool isMale) {
    if (isMale) {
        return 88.362 + (13.397 * weight) + (4.799 * height) - (5.677 * age);
    } else {
        return 447.593 + (9.247 * weight) + (3.098 * height) - (4.330 * age);
    }
}

double NutritionCalculator::calculateDailyCalories(double bmr, ActivityLevel activity, Goal goal) {
    double multiplier = 1.2;
    switch (activity) {
        case ActivityLevel::SEDENTARY: multiplier = 1.2; break;
        case ActivityLevel::LIGHT: multiplier = 1.375; break;
        case ActivityLevel::MODERATE: multiplier = 1.55; break;
        case ActivityLevel::ACTIVE: multiplier = 1.725; break;
        case ActivityLevel::VERY_ACTIVE: multiplier = 1.9; break;
    }
    
    double maintenance = bmr * multiplier;
    
    switch (goal) {
        case Goal::WEIGHT_LOSS: return maintenance * 0.85;
        case Goal::MAINTENANCE: return maintenance;
        case Goal::WEIGHT_GAIN: return maintenance * 1.15;
    }
    
    return maintenance;
}