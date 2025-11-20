#ifndef DIARY_COMMANDS_H
#define DIARY_COMMANDS_H

#include "include/commands/command.h"
#include "include/containers/nutrition_container.h"
#include "include/core/nutrition_item.h"
#include <ctime>

class AddMealCommand : public Command {
private:
    NutritionContainer& nutrition;
    NutritionItem* item;
    double quantity;
    std::time_t date;

public:
    AddMealCommand(NutritionContainer& nutrition, NutritionItem* item, double quantity, std::time_t date);
    ~AddMealCommand();
    
    void execute() override;
    void undo() override;
    bool canUndo() const override { return true; }
    
    std::string getName() const override { return "AddMeal"; }
    std::string getDescription() const override { 
        return "Add meal with: " + item->getName(); 
    }
};

class RemoveMealCommand : public Command {
private:
    NutritionContainer& nutrition;
    std::time_t date;
    int mealIndex;

public:
    RemoveMealCommand(NutritionContainer& nutrition, std::time_t date, int mealIndex);
    ~RemoveMealCommand();
    
    void execute() override;
    void undo() override;
    bool canUndo() const override { return true; }
    
    std::string getName() const override { return "RemoveMeal"; }
    std::string getDescription() const override { 
        return "Remove meal at index: " + std::to_string(mealIndex); 
    }
};

class EditMealCommand : public Command {
private:
    NutritionContainer& nutrition;
    std::time_t date;
    int mealIndex;
    double oldQuantity;
    double newQuantity;

public:
    EditMealCommand(NutritionContainer& nutrition, std::time_t date, int mealIndex, double newQuantity);
    ~EditMealCommand();
    
    void execute() override;
    void undo() override;
    bool canUndo() const override { return true; }
    
    std::string getName() const override { return "EditMeal"; }
    std::string getDescription() const override { 
        return "Edit meal quantity at index: " + std::to_string(mealIndex); 
    }
};

#endif