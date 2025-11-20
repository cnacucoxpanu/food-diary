#include "../../header.h"

Meal::Meal() : timestamp(std::time(0)), item(nullptr), quantity(0) {}

Meal::Meal(NutritionItem* item, double quantity, std::time_t timestamp)
    : timestamp(timestamp), item(item), quantity(quantity) {}

Meal::~Meal() {}

std::ostream& operator<<(std::ostream& os, const Meal& meal) {
    std::tm* timeinfo = std::localtime(&meal.timestamp);
    char timeStr[9];
    std::strftime(timeStr, sizeof(timeStr), "%H:%M:%S", timeinfo);
    
    os << timeStr << " | " << meal.item->getName() 
       << " | " << meal.quantity << "г"
       << " | Калории: " << meal.getCalories()
       << " | Белки: " << meal.getProteins() << "г";
    return os;
}