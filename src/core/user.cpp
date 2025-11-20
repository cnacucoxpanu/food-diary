#include "../../header.h"

User::User() : username(""), passwordHash(""), weight(0), height(0), age(0), 
               goal(Goal::MAINTENANCE), activity(ActivityLevel::MODERATE) {}

User::User(const std::string& username, double weight, double height, 
           int age, Goal goal, ActivityLevel activity)
    : username(username), passwordHash(""), weight(weight), height(height), 
      age(age), goal(goal), activity(activity) {}

User::~User() {}

void User::setWeight(double newWeight) {
    if (newWeight > 0) {
        weight = newWeight;
    }
}

double User::calculateDailyCalories() const {
    double bmr = 10 * weight + 6.25 * height - 5 * age + 5;
    
    double activityMultiplier = 1.2;
    switch (activity) {
        case ActivityLevel::SEDENTARY: activityMultiplier = 1.2; break;
        case ActivityLevel::LIGHT: activityMultiplier = 1.375; break;
        case ActivityLevel::MODERATE: activityMultiplier = 1.55; break;
        case ActivityLevel::ACTIVE: activityMultiplier = 1.725; break;
        case ActivityLevel::VERY_ACTIVE: activityMultiplier = 1.9; break;
    }
    
    double maintenanceCalories = bmr * activityMultiplier;
    
    switch (goal) {
        case Goal::WEIGHT_LOSS: return maintenanceCalories * 0.85;
        case Goal::MAINTENANCE: return maintenanceCalories;
        case Goal::WEIGHT_GAIN: return maintenanceCalories * 1.15;
    }
    
    return maintenanceCalories;
}