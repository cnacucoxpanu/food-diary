#include "../../header.h"

NutritionDiary::NutritionDiary() {}

NutritionDiary::~NutritionDiary() {}

bool NutritionDiary::loadAllData() {
    bool success = true;
    
    // Загрузка пользователей и паролей уже выполнена в NutritionSystem::load()
    // Здесь загружаем только продукты и данные питания
    
    // Загрузка продуктов из разных категорий (БЕЗ products.txt)
    std::vector<std::string> productFiles = {
        "data/fruits.txt", "data/vegetables.txt",
        "data/drinks.txt", "data/proteins.txt", "data/grains.txt"
    };
    
    for (const auto& file : productFiles) {
        if (!products.loadFromFile(file)) {
            success = false;
        }
    }
    
    // Загрузка данных питания для всех пользователей
    for (const auto& user : users.getAllUsers()) {
        if (user) {
            std::string nutritionFile = "data/nutrition_logs/user_" + user->getUsername() + "_logs.txt";
            nutrition.setCurrentUser(user->getUsername());
            if (!nutrition.loadFromFile(nutritionFile)) {
                success = false;
            }
        }
    }
    
    return success;
}

bool NutritionDiary::saveAllData() {
    bool success = true;
    
    if (!users.saveToFile("data/users.txt")) {
        success = false;
    }
    
    if (!users.savePasswords("data/passwords.txt")) {
        success = false;
    }
    
    // Сохранение данных питания для всех пользователей
    for (const auto& user : users.getAllUsers()) {
        if (user) {
            std::string nutritionFile = "data/nutrition_logs/user_" + user->getUsername() + "_logs.txt";
            nutrition.setCurrentUser(user->getUsername());
            if (!nutrition.saveToFile(nutritionFile)) {
                success = false;
            }
        }
    }
    
    return success;
}

void NutritionDiary::generateDailyReport(std::time_t date) const {
    nutrition.generateDailyReport(date);
}

void NutritionDiary::generatePeriodReport(std::time_t startDate, std::time_t endDate) const {
    nutrition.generatePeriodReport(startDate, endDate);
}