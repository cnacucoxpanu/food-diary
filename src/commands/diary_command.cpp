#include "../../header.h"

AddMealCommand::AddMealCommand(NutritionContainer& nutrition, NutritionItem* item,
                             double quantity, std::time_t date)
    : nutrition(nutrition), item(item), quantity(quantity), date(date) {}

AddMealCommand::~AddMealCommand() {}

void AddMealCommand::execute() {
    nutrition.addMeal(date, item, quantity);
}


RemoveMealCommand::RemoveMealCommand(NutritionContainer& nutrition, std::time_t date, 
                                   int mealIndex)
    : nutrition(nutrition), date(date), mealIndex(mealIndex) {}

RemoveMealCommand::~RemoveMealCommand() {}

void RemoveMealCommand::execute() {
    nutrition.removeMeal(date, mealIndex);
}


EditMealCommand::EditMealCommand(NutritionContainer& nutrition, std::time_t date,
                               int mealIndex, double newQuantity)
    : nutrition(nutrition), date(date), mealIndex(mealIndex), newQuantity(newQuantity) {}

EditMealCommand::~EditMealCommand() {}

void EditMealCommand::execute() {
    // Сохраняем старое значение для отмены
    auto meals = nutrition.getMealsByDate(date);
    if (mealIndex >= 0 && mealIndex < meals.size()) {
        oldQuantity = meals[mealIndex].getQuantity();
        nutrition.editMeal(date, mealIndex, newQuantity);
    }
}

void EditMealCommand::undo() {
    if (oldQuantity > 0) {
        nutrition.editMeal(date, mealIndex, oldQuantity);
    }
}