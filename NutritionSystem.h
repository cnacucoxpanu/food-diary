#ifndef NUTRITION_SYSTEM_H
#define NUTRITION_SYSTEM_H

#include "include/core/nutrition_diary.h"

class NutritionSystem {
private:
    NutritionDiary diary;
    
    void showDiaryMenu();
    void showProductsMenu();
    void showReportsMenu();
    void showProfileMenu(User* user);
    void showDishesMenu();
    
    void addMeal();
    void viewMeals();
    void editMeal();
    void removeMeal();
    void addProduct();
    void searchProduct();
    void listAllProducts();
    void changeUserWeight(User* user);
    void showProductsByCategory();
    void showCategoryProducts(const std::string& categoryName, const std::vector<int>& productIds);

public:
    NutritionSystem();
    
    void load();
    User* login();
    void menuUser(User* user);
    void logout();
    void save();
};

#endif