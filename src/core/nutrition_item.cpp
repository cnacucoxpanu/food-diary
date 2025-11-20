#include "../../header.h"

NutritionItem::NutritionItem() : id(0), name(""), calories(0), proteins(0), fats(0), carbs(0) {}

NutritionItem::NutritionItem(int id, const std::string& name, double calories, 
                           double proteins, double fats, double carbs)
    : id(id), name(name), calories(calories), proteins(proteins), fats(fats), carbs(carbs) {}

std::ostream& operator<<(std::ostream& os, const NutritionItem& item) {
    os << item.getType() << " [" << item.id << "] " << item.name 
       << " | Калории: " << item.calories 
       << " | Белки: " << item.proteins << "г"
       << " | Жиры: " << item.fats << "г"
       << " | Углеводы: " << item.carbs << "г";
    return os;
}