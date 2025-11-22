#include "../../header.h"

NutritionContainer::NutritionContainer() : currentUsername("") {}

NutritionContainer::~NutritionContainer() {}

void NutritionContainer::setCurrentUser(const std::string& username) {
    currentUsername = username;
}

void NutritionContainer::addMeal(std::time_t date, NutritionItem* item, double quantity) {
    if (item && quantity > 0) {
        dailyMeals[date].emplace_back(item, quantity, std::time(0));
    }
}

void NutritionContainer::removeMeal(std::time_t date, int index) {
    auto it = dailyMeals.find(date);
    if (it != dailyMeals.end() && index >= 0 && index < it->second.size()) {
        it->second.erase(it->second.begin() + index);
        if (it->second.empty()) {
            dailyMeals.erase(it);
        }
    }
}

void NutritionContainer::editMeal(std::time_t date, int index, double newQuantity) {
    auto it = dailyMeals.find(date);
    if (it != dailyMeals.end() && index >= 0 && index < it->second.size() && newQuantity > 0) {
        Meal& meal = it->second[index];
        it->second[index] = Meal(meal.getItem(), newQuantity, meal.getTimestamp());
    }
}

const std::vector<Meal>& NutritionContainer::getMealsByDate(std::time_t date) const {
    static const std::vector<Meal> empty;
    auto it = dailyMeals.find(date);
    return (it != dailyMeals.end()) ? it->second : empty;
}

double NutritionContainer::getTotalCalories(std::time_t date) const {
    double total = 0;
    auto it = dailyMeals.find(date);
    if (it != dailyMeals.end()) {
        for (const auto& meal : it->second) {
            total += meal.getCalories();
        }
    }
    return total;
}

double NutritionContainer::getTotalProteins(std::time_t date) const {
    double total = 0;
    auto it = dailyMeals.find(date);
    if (it != dailyMeals.end()) {
        for (const auto& meal : it->second) {
            total += meal.getProteins();
        }
    }
    return total;
}

double NutritionContainer::getTotalFats(std::time_t date) const {
    double total = 0;
    auto it = dailyMeals.find(date);
    if (it != dailyMeals.end()) {
        for (const auto& meal : it->second) {
            total += meal.getFats();
        }
    }
    return total;
}

double NutritionContainer::getTotalCarbs(std::time_t date) const {
    double total = 0;
    auto it = dailyMeals.find(date);
    if (it != dailyMeals.end()) {
        for (const auto& meal : it->second) {
            total += meal.getCarbs();
        }
    }
    return total;
}

double NutritionContainer::getAverageDailyCalories(std::time_t startDate, std::time_t endDate) const {
    if (startDate > endDate) return 0;
    
    double total = 0;
    int days = 0;
    
    for (auto it = dailyMeals.lower_bound(startDate); 
         it != dailyMeals.end() && it->first <= endDate; ++it) {
        total += getTotalCalories(it->first);
        days++;
    }
    
    return (days > 0) ? total / days : 0;
}

void NutritionContainer::generateDailyReport(std::time_t date) const {
    std::cout << "=== ОТЧЕТ ЗА ДЕНЬ ===\n";
    std::tm* timeinfo = std::localtime(&date);
    char dateStr[11];
    std::strftime(dateStr, sizeof(dateStr), "%Y-%m-%d", timeinfo);
    std::cout << "Дата: " << dateStr << "\n";
    
    double calories = getTotalCalories(date);
    double proteins = getTotalProteins(date);
    double fats = getTotalFats(date);
    double carbs = getTotalCarbs(date);
    
    std::cout << "Общая калорийность: " << calories << " ккал\n";
    std::cout << "Белки: " << proteins << " г\n";
    std::cout << "Жиры: " << fats << " г\n";
    std::cout << "Углеводы: " << carbs << " г\n";
    
    const auto& meals = getMealsByDate(date);
    if (!meals.empty()) {
        std::cout << "\nПриемы пищи:\n";
        for (size_t i = 0; i < meals.size(); ++i) {
            std::cout << "  " << (i + 1) << ". " << meals[i] << "\n";
        }
    } else {
        std::cout << "\nПриемы пищи отсутствуют\n";
    }
}

void NutritionContainer::generatePeriodReport(std::time_t startDate, std::time_t endDate) const {
    std::cout << "=== ОТЧЕТ ЗА ПЕРИОД ===\n";
    std::tm* startInfo = std::localtime(&startDate);
    std::tm* endInfo = std::localtime(&endDate);
    char startStr[11], endStr[11];
    std::strftime(startStr, sizeof(startStr), "%Y-%m-%d", startInfo);
    std::strftime(endStr, sizeof(endStr), "%Y-%m-%d", endInfo);
    std::cout << "Период: " << startStr << " - " << endStr << "\n";
    
    double totalCalories = 0;
    double totalProteins = 0;
    double totalFats = 0;
    double totalCarbs = 0;
    int days = 0;
    
    for (auto it = dailyMeals.lower_bound(startDate); 
         it != dailyMeals.end() && it->first <= endDate; ++it) {
        totalCalories += getTotalCalories(it->first);
        totalProteins += getTotalProteins(it->first);
        totalFats += getTotalFats(it->first);
        totalCarbs += getTotalCarbs(it->first);
        days++;
    }
    
    std::cout << "Всего дней: " << days << "\n";
    std::cout << "Общая калорийность: " << totalCalories << " ккал\n";
    std::cout << "Среднедневная калорийность: " << (days > 0 ? totalCalories / days : 0) << " ккал\n";
    std::cout << "Белки: " << totalProteins << " г\n";
    std::cout << "Жиры: " << totalFats << " г\n";
    std::cout << "Углеводы: " << totalCarbs << " г\n";
}

bool NutritionContainer::loadFromFile(const std::string& filename) {
    std::ifstream file(filename);
    if (!file.is_open()) {
        return false;
    }
    
    dailyMeals.clear();
    
    std::string line;
    std::time_t currentDate = 0;
    
    while (std::getline(file, line)) {
        if (line.empty()) continue;
        
        if (line[0] == '#') {
            if (line.find("Дата:") != std::string::npos) {
                currentDate = std::time(0);
            }
            continue;
        }
        
        std::vector<std::string> parts = StringUtils::split(line, '|');
        if (parts.size() == 3) {
            int productId = std::stoi(parts[0]);
            double quantity = std::stod(parts[1]);
            std::time_t timestamp = std::stol(parts[2]);
        }
    }
    
    file.close();
    return true;
}

bool NutritionContainer::saveToFile(const std::string& filename) const {
    std::ofstream file(filename);
    if (!file.is_open()) {
        return false;
    }
    
    for (const auto& dateMeals : dailyMeals) {
        std::tm* timeinfo = std::localtime(&dateMeals.first);
        char dateStr[11];
        std::strftime(dateStr, sizeof(dateStr), "%Y-%m-%d", timeinfo);
        
        file << "# Дата: " << dateStr << "\n";
        for (const auto& meal : dateMeals.second) {
            file << meal.getItem()->getId() << "|"
                 << meal.getQuantity() << "|"
                 << meal.getTimestamp() << "\n";
        }
        file << "\n";
    }
    
    file.close();
    return true;
}

bool NutritionContainer::hasDate(std::time_t date) const {
    return dailyMeals.find(date) != dailyMeals.end();
}

std::ostream& operator<<(std::ostream& os, const NutritionContainer& container) {
    os << "Дневник питания пользователя: " << container.currentUsername << "\n";
    os << "Всего дней с записями: " << container.dailyMeals.size() << "\n";
    return os;
}