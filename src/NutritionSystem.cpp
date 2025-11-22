#include "../header.h"
#include "../NutritionSystem.h"

NutritionSystem::NutritionSystem() {}

void NutritionSystem::load() {
    ConsoleIO::printInfo("Загрузка данных системы...");
    
    // СНАЧАЛА загружаем пароли
    if (!diary.getUserManager().loadPasswords("data/passwords.txt")) {
        ConsoleIO::printWarning("Не удалось загрузить файл паролей!");
    }
    
    // ПОТОМ загружаем пользователей
    if (!diary.getUserManager().loadFromFile("data/users.txt")) {
        ConsoleIO::printWarning("Не удалось загрузить файл пользователей!");
    }
    
    if (!diary.loadAllData()) {
        ConsoleIO::printWarning("Не удалось загрузить некоторые данные.");
    }
    ConsoleIO::printSuccess("Система готова к работе!");
}

User* NutritionSystem::login() {
    while (true) {
        ConsoleIO::clearScreen();
        ConsoleIO::printHeader("🔐 АУТЕНТИФИКАЦИЯ");
        
        ConsoleIO::printMenuOption(1, "🔑 Вход в систему");
        ConsoleIO::printMenuOption(2, "📝 Регистрация");
        ConsoleIO::printMenuOption(0, "🚪 Выход");
        
        int choice = ConsoleIO::getInt("Выберите действие: ");
        
        if (choice == 1) {
            std::string username = ConsoleIO::getString("Имя пользователя: ");
            std::string password = ConsoleIO::getString("Пароль: ");
            
            try {
                LoginCommand cmd(diary.getUserManager(), username, password);
                cmd.execute();
                // Устанавливаем текущего пользователя в NutritionContainer
                User* user = diary.getUserManager().getCurrentUser();
                if (user) {
                    diary.getNutritionManager().setCurrentUser(user->getUsername());
                }
                ConsoleIO::printSuccess("Успешный вход!");
                return user;
            } catch (const AuthException& e) {
                ConsoleIO::printError(e.what());
                ConsoleIO::waitForEnter();
            }
        } 
        else if (choice == 2) {
            std::string username = ConsoleIO::getString("Имя пользователя: ");
            std::string password = ConsoleIO::getString("Пароль: ");
            double weight = ConsoleIO::getDouble("Вес (кг): ");
            double height = ConsoleIO::getDouble("Рост (см): ");
            int age = ConsoleIO::getInt("Возраст: ");
            
            // Выбор цели
            ConsoleIO::printInfo("🎯 Выберите цель:");
            ConsoleIO::printMenuOption(1, "📉 Похудение");
            ConsoleIO::printMenuOption(2, "⚖️ Поддержание веса");
            ConsoleIO::printMenuOption(3, "📈 Набор массы");
            int goalChoice = ConsoleIO::getInt("Ваш выбор: ");
            
            Goal goal = Goal::MAINTENANCE;
            switch (goalChoice) {
                case 1: goal = Goal::WEIGHT_LOSS; break;
                case 2: goal = Goal::MAINTENANCE; break;
                case 3: goal = Goal::WEIGHT_GAIN; break;
            }
            
            // Выбор активности
            ConsoleIO::printInfo("🏃‍♂️ Уровень активности:");
            ConsoleIO::printMenuOption(1, "💺 Сидячий образ жизни");
            ConsoleIO::printMenuOption(2, "🚶‍♂️ Легкая активность");
            ConsoleIO::printMenuOption(3, "🏃‍♂️ Умеренная активность");
            ConsoleIO::printMenuOption(4, "🔥 Высокая активность");
            ConsoleIO::printMenuOption(5, "💪 Очень высокая активность");
            int activityChoice = ConsoleIO::getInt("Ваш выбор: ");
            
            ActivityLevel activity = ActivityLevel::MODERATE;
            switch (activityChoice) {
                case 1: activity = ActivityLevel::SEDENTARY; break;
                case 2: activity = ActivityLevel::LIGHT; break;
                case 3: activity = ActivityLevel::MODERATE; break;
                case 4: activity = ActivityLevel::ACTIVE; break;
                case 5: activity = ActivityLevel::VERY_ACTIVE; break;
            }
            
            try {
                RegisterCommand cmd(diary.getUserManager(), username, password, 
                                  weight, height, age, goal, activity);
                cmd.execute();
                // Устанавливаем текущего пользователя в NutritionContainer
                User* user = diary.getUserManager().getCurrentUser();
                if (user) {
                    diary.getNutritionManager().setCurrentUser(user->getUsername());
                }
                ConsoleIO::printSuccess("Регистрация успешна!");
                return user;
            } catch (const AuthException& e) {
                ConsoleIO::printError(e.what());
                ConsoleIO::waitForEnter();
            }
        }
        else if (choice == 0) {
            return nullptr;
        }
        else {
            ConsoleIO::printError("Неверный выбор!");
            ConsoleIO::waitForEnter();
        }
    }
}

void NutritionSystem::menuUser(User* user) {
    if (!user) return;
    
    bool running = true;
    while (running) {
        ConsoleIO::clearScreen();
        ConsoleIO::printHeader("👤 ГЛАВНОЕ МЕНЮ");
        ConsoleIO::printSuccess("Пользователь: " + user->getUsername());
        std::cout << "🎯 Дневная норма: " << user->calculateDailyCalories() << " ккал\n\n";
        
        ConsoleIO::printMenuOption(1, "📊 Дневник питания");
        ConsoleIO::printMenuOption(2, "🍎 Продукты");
        ConsoleIO::printMenuOption(3, "👨‍🍳 Блюда");
        ConsoleIO::printMenuOption(4, "📈 Отчеты");
        ConsoleIO::printMenuOption(5, "⚙️ Профиль");
        ConsoleIO::printMenuOption(0, "🚪 Выход");
        
        int choice = ConsoleIO::getInt("Выберите пункт: ");
        
        switch (choice) {
            case 1: showDiaryMenu(); break;
            case 2: showProductsMenu(); break;
            case 3: showDishesMenu(); break;
            case 4: showReportsMenu(); break;
            case 5: showProfileMenu(user); break;
            case 0: running = false; break;
            default: 
                ConsoleIO::printError("Неверный выбор!");
                ConsoleIO::waitForEnter();
        }
    }
}

void NutritionSystem::logout() {
    diary.getUserManager().logout();
    ConsoleIO::printSuccess("Выход выполнен!");
}

void NutritionSystem::save() {
    if (diary.saveAllData()) {
        ConsoleIO::printSuccess("Данные успешно сохранены!");
    } else {
        ConsoleIO::printError("Ошибка при сохранении данных.");
    }
}

// Приватные методы меню
void NutritionSystem::showDiaryMenu() {
    bool inMenu = true;
    while (inMenu) {
        ConsoleIO::clearScreen();
        ConsoleIO::printHeader("📊 ДНЕВНИК ПИТАНИЯ");
        
        // Показать сегодняшний итог
        // Нормализуем дату (убираем время, оставляем только дату)
        std::time_t now = std::time(0);
        std::tm* timeinfo = std::localtime(&now);
        timeinfo->tm_hour = 0;
        timeinfo->tm_min = 0;
        timeinfo->tm_sec = 0;
        std::time_t today = std::mktime(timeinfo);
        
        double todayCalories = diary.getNutritionManager().getTotalCalories(today);
        auto user = diary.getUserManager().getCurrentUser();
        double dailyGoal = user ? user->calculateDailyCalories() : 0;
        
        std::cout << "📅 Сегодня: ";
        std::tm* dateInfo = std::localtime(&today);
        char dateStr[11];
        std::strftime(dateStr, sizeof(dateStr), "%Y-%m-%d", dateInfo);
        std::cout << dateStr << "\n";
        std::cout << "🔥 Потреблено: " << todayCalories << " / " << dailyGoal << " ккал\n";
        std::cout << "📊 Прогресс: " << (dailyGoal > 0 ? (todayCalories / dailyGoal * 100) : 0) << "%\n\n";
        
        ConsoleIO::printMenuOption(1, "➕ Добавить прием пищи");
        ConsoleIO::printMenuOption(2, "👀 Просмотреть приемы пищи");
        ConsoleIO::printMenuOption(3, "✏️ Редактировать прием пищи");
        ConsoleIO::printMenuOption(4, "🗑️ Удалить прием пищи");
        ConsoleIO::printMenuOption(0, "🔙 Назад");
        
        int choice = ConsoleIO::getInt("Выберите действие: ");
        
        switch (choice) {
            case 1: addMeal(); break;
            case 2: 
                viewMeals();
                break;
            case 3:
                editMeal();
                break;
            case 4:
                removeMeal();
                break;
            case 0: inMenu = false; break;
            default: ConsoleIO::printError("Неверный выбор!");
        }
    }
}

void NutritionSystem::showProductsMenu() {
    bool inMenu = true;
    while (inMenu) {
        ConsoleIO::clearScreen();
        ConsoleIO::printHeader("🍎 УПРАВЛЕНИЕ ПРОДУКТАМИ");
        
        ConsoleIO::printMenuOption(1, "🔍 Поиск продукта");
        ConsoleIO::printMenuOption(2, "📋 Все продукты");
        ConsoleIO::printMenuOption(3, "📁 Продукты по категориям");
        ConsoleIO::printMenuOption(4, "➕ Добавить продукт");
        ConsoleIO::printMenuOption(5, "🗑️ Удалить продукт");
        ConsoleIO::printMenuOption(0, "🔙 Назад");
        
        int choice = ConsoleIO::getInt("Выберите действие: ");
        
        switch (choice) {
            case 1: searchProduct(); break;
            case 2: listAllProducts(); break;
            case 3: showProductsByCategory(); break;
            case 4: addProduct(); break;
            case 5:
                {
                    int productId = ConsoleIO::getInt("ID продукта для удаления: ");
                    if (diary.getProductManager().removeItem(productId)) {
                        ConsoleIO::printSuccess("Продукт удален!");
                    } else {
                        ConsoleIO::printError("Продукт не найден!");
                    }
                    ConsoleIO::waitForEnter();
                }
                break;
            case 0: inMenu = false; break;
            default: ConsoleIO::printError("Неверный выбор!");
        }
    }
}

void NutritionSystem::showDishesMenu() {
    bool inMenu = true;
    while (inMenu) {
        ConsoleIO::clearScreen();
        ConsoleIO::printHeader("👨‍🍳 УПРАВЛЕНИЕ БЛЮДАМИ");
        
        ConsoleIO::printMenuOption(1, "➕ Создать блюдо");
        ConsoleIO::printMenuOption(2, "📋 Мои блюда");
        ConsoleIO::printMenuOption(3, "✏️ Редактировать блюдо");
        ConsoleIO::printMenuOption(4, "🗑️ Удалить блюдо");
        ConsoleIO::printMenuOption(0, "🔙 Назад");
        
        int choice = ConsoleIO::getInt("Выберите действие: ");
        
        switch (choice) {
            case 1:
                {
                    std::string name = ConsoleIO::getString("Название блюда: ");
                    Dish* dish = diary.getProductManager().addDish(name);
                    if (dish) {
                        ConsoleIO::printSuccess("Блюдо создано: " + name);
                        
                        // Добавление ингредиентов
                        bool addingIngredients = true;
                        while (addingIngredients) {
                            ConsoleIO::printInfo("Добавление ингредиентов:");
                            listAllProducts();
                            
                            int productId = ConsoleIO::getInt("ID продукта (0 - закончить): ");
                            if (productId == 0) break;
                            
                            Product* product = dynamic_cast<Product*>(diary.getProductManager().findItem(productId));
                            if (product) {
                                double quantity = ConsoleIO::getDouble("Количество (г): ");
                                dish->addIngredient(product, quantity);
                                ConsoleIO::printSuccess("Ингредиент добавлен!");
                            } else {
                                ConsoleIO::printError("Продукт не найден!");
                            }
                        }
                    }
                    ConsoleIO::waitForEnter();
                }
                break;
            case 2:
                {
                    const auto& items = diary.getProductManager().getAllItems();
                    std::cout << "📋 Список блюд:\n";
                    for (const auto& item : items) {
                        if (item->getType() == "DISH") {
                            std::cout << *item << "\n";
                        }
                    }
                    ConsoleIO::waitForEnter();
                }
                break;
            case 3:
                ConsoleIO::printInfo("Редактирование блюда...");
                ConsoleIO::waitForEnter();
                break;
            case 4:
                {
                    int dishId = ConsoleIO::getInt("ID блюда для удаления: ");
                    if (diary.getProductManager().removeItem(dishId)) {
                        ConsoleIO::printSuccess("Блюдо удалено!");
                    } else {
                        ConsoleIO::printError("Блюдо не найдено!");
                    }
                    ConsoleIO::waitForEnter();
                }
                break;
            case 0: inMenu = false; break;
            default: ConsoleIO::printError("Неверный выбор!");
        }
    }
}

void NutritionSystem::showReportsMenu() {
    bool inMenu = true;
    while (inMenu) {
        ConsoleIO::clearScreen();
        ConsoleIO::printHeader("📈 ОТЧЕТЫ И АНАЛИТИКА");
        
        ConsoleIO::printMenuOption(1, "📅 Отчет за сегодня");
        ConsoleIO::printMenuOption(2, "📆 Отчет за неделю");
        ConsoleIO::printMenuOption(3, "📊 Отчет за месяц");
        ConsoleIO::printMenuOption(4, "🥗 Анализ питания");
        ConsoleIO::printMenuOption(0, "🔙 Назад");
        
        int choice = ConsoleIO::getInt("Выберите действие: ");
        
        std::time_t now = std::time(0);
        switch (choice) {
            case 1:
                diary.generateDailyReport(now);
                ConsoleIO::waitForEnter();
                break;
            case 2:
                diary.generatePeriodReport(now - 7*24*60*60, now);
                ConsoleIO::waitForEnter();
                break;
            case 3:
                diary.generatePeriodReport(now - 30*24*60*60, now);
                ConsoleIO::waitForEnter();
                break;
            case 4:
                {
                    auto user = diary.getUserManager().getCurrentUser();
                    if (user) {
                        std::cout << "📊 АНАЛИЗ ПИТАНИЯ\n";
                        std::cout << "👤 Пользователь: " << user->getUsername() << "\n";
                        std::cout << "🎯 Цель: ";
                        switch (user->getGoal()) {
                            case Goal::WEIGHT_LOSS: std::cout << "Похудение\n"; break;
                            case Goal::MAINTENANCE: std::cout << "Поддержание веса\n"; break;
                            case Goal::WEIGHT_GAIN: std::cout << "Набор массы\n"; break;
                        }
                        std::cout << "🔥 Рекомендуемая норма: " << user->calculateDailyCalories() << " ккал\n";
                        std::cout << "⚖️ Текущий вес: " << user->getWeight() << " кг\n";
                    }
                    ConsoleIO::waitForEnter();
                }
                break;
            case 0: inMenu = false; break;
            default: ConsoleIO::printError("Неверный выбор!");
        }
    }
}

void NutritionSystem::showProfileMenu(User* user) {
    bool inMenu = true;
    while (inMenu) {
        ConsoleIO::clearScreen();
        ConsoleIO::printHeader("⚙️ ПРОФИЛЬ ПОЛЬЗОВАТЕЛЯ");
        
        std::cout << "👤 Имя: " << user->getUsername() << "\n";
        std::cout << "⚖️ Вес: " << user->getWeight() << " кг\n";
        std::cout << "📏 Рост: " << user->getHeight() << " см\n";
        std::cout << "🎂 Возраст: " << user->getAge() << " лет\n";
        std::cout << "🎯 Цель: ";
        switch (user->getGoal()) {
            case Goal::WEIGHT_LOSS: std::cout << "Похудение\n"; break;
            case Goal::MAINTENANCE: std::cout << "Поддержание веса\n"; break;
            case Goal::WEIGHT_GAIN: std::cout << "Набор массы\n"; break;
        }
        std::cout << "🏃‍♂️ Активность: ";
        switch (user->getActivity()) {
            case ActivityLevel::SEDENTARY: std::cout << "Сидячий образ жизни\n"; break;
            case ActivityLevel::LIGHT: std::cout << "Легкая активность\n"; break;
            case ActivityLevel::MODERATE: std::cout << "Умеренная активность\n"; break;
            case ActivityLevel::ACTIVE: std::cout << "Высокая активность\n"; break;
            case ActivityLevel::VERY_ACTIVE: std::cout << "Очень высокая активность\n"; break;
        }
        std::cout << "🔥 Дневная норма калорий: " << user->calculateDailyCalories() << " ккал\n\n";
        
        ConsoleIO::printMenuOption(1, "✏️ Изменить вес");
        ConsoleIO::printMenuOption(2, "🔒 Сменить пароль");
        ConsoleIO::printMenuOption(3, "🎯 Изменить цель");
        ConsoleIO::printMenuOption(0, "🔙 Назад");
        
        int choice = ConsoleIO::getInt("Выберите действие: ");
        
        switch (choice) {
            case 1: changeUserWeight(user); break;
            case 2:
                {
                    std::string newPassword = ConsoleIO::getString("Новый пароль: ");
                    user->setPassword(newPassword);
                    diary.getUserManager().updatePassword(user->getUsername(), newPassword);
                    ConsoleIO::printSuccess("Пароль изменен!");
                    ConsoleIO::waitForEnter();
                }
                break;
            case 3:
                {
                    ConsoleIO::printInfo("🎯 Выберите новую цель:");
                    ConsoleIO::printMenuOption(1, "📉 Похудение");
                    ConsoleIO::printMenuOption(2, "⚖️ Поддержание веса");
                    ConsoleIO::printMenuOption(3, "📈 Набор массы");
                    int goalChoice = ConsoleIO::getInt("Ваш выбор: ");
                    
                    Goal newGoal = Goal::MAINTENANCE;
                    switch (goalChoice) {
                        case 1: newGoal = Goal::WEIGHT_LOSS; break;
                        case 2: newGoal = Goal::MAINTENANCE; break;
                        case 3: newGoal = Goal::WEIGHT_GAIN; break;
                    }
                    user->setGoal(newGoal);
                    ConsoleIO::printSuccess("Цель изменена!");
                    ConsoleIO::waitForEnter();
                }
                break;
            case 0: inMenu = false; break;
            default: ConsoleIO::printError("Неверный выбор!");
        }
    }
}

// НОВЫЙ МЕТОД: Показ продуктов по категориям
void NutritionSystem::showProductsByCategory() {
    bool inMenu = true;
    while (inMenu) {
        ConsoleIO::clearScreen();
        ConsoleIO::printHeader("📁 ВЫБЕРИТЕ КАТЕГОРИЮ ПРОДУКТОВ");
        
        ConsoleIO::printMenuOption(1, "🍎 Фрукты");
        ConsoleIO::printMenuOption(2, "🥦 Овощи");
        ConsoleIO::printMenuOption(3, "🥛 Напитки");
        ConsoleIO::printMenuOption(4, "🍗 Белковые продукты");
        ConsoleIO::printMenuOption(5, "🌾 Крупы и злаки");
        ConsoleIO::printMenuOption(0, "🔙 Назад");
        
        int choice = ConsoleIO::getInt("Выберите категорию: ");
        
        std::string categoryName;
        std::vector<int> categoryIds;
        
        switch (choice) {
            case 1: 
                categoryName = "🍎 ФРУКТЫ";
                categoryIds = {1, 9, 10, 11, 12, 13, 34, 35, 36, 37, 38};
                break;
            case 2:
                categoryName = "🥦 ОВОЩИ";
                categoryIds = {7, 14, 15, 16, 17, 18, 39, 40, 41, 42, 43, 44};
                break;
            case 3:
                categoryName = "🥛 НАПИТКИ";
                categoryIds = {4, 19, 20, 21, 22, 23, 45, 46, 47, 48, 49};
                break;
            case 4:
                categoryName = "🍗 БЕЛКОВЫЕ ПРОДУКТЫ";
                categoryIds = {2, 5, 24, 25, 26, 27, 28, 50, 51, 52, 53, 54, 55};
                break;
            case 5:
                categoryName = "🌾 КРУПЫ И ЗЛАКИ";
                categoryIds = {3, 6, 8, 29, 30, 31, 32, 33, 56, 57, 58, 59, 60};
                break;
            case 0: 
                inMenu = false;
                continue;
            default:
                ConsoleIO::printError("Неверный выбор!");
                ConsoleIO::waitForEnter();
                continue;
        }
        
        // Показываем продукты выбранной категории
        showCategoryProducts(categoryName, categoryIds);
    }
}

// Вспомогательный метод для показа продуктов категории
void NutritionSystem::showCategoryProducts(const std::string& categoryName, const std::vector<int>& productIds) {
    ConsoleIO::clearScreen();
    ConsoleIO::printHeader(categoryName);
    
    std::cout << "📋 Список продуктов в категории:\n\n";
    
    int foundCount = 0;
    for (int id : productIds) {
        NutritionItem* item = diary.getProductManager().findItem(id);
        if (item) {
            std::cout << "ID: " << item->getId() << " | " << item->getName() 
                      << " | Калории: " << item->getTotalCalories() 
                      << " | Белки: " << item->getTotalProteins() << "г"
                      << " | Жиры: " << item->getTotalFats() << "г"
                      << " | Углеводы: " << item->getTotalCarbs() << "г\n";
            foundCount++;
        }
    }
    
    if (foundCount == 0) {
        ConsoleIO::printWarning("В этой категории пока нет продуктов.");
    } else {
        std::cout << "\n💡 Запомните ID продукта для добавления в дневник питания.\n";
    }
    
    ConsoleIO::waitForEnter();
}

// Обновленный метод добавления приема пищи
void NutritionSystem::addMeal() {
    ConsoleIO::clearScreen();
    ConsoleIO::printHeader("➕ ДОБАВЛЕНИЕ ПРИЕМА ПИЩИ");
    
    ProductContainer& products = diary.getProductManager();
    NutritionContainer& nutrition = diary.getNutritionManager();
    
    // Спрашиваем, как пользователь хочет выбрать продукт
    ConsoleIO::printInfo("Как вы хотите выбрать продукт?");
    ConsoleIO::printMenuOption(1, "📁 Выбрать из категорий");
    ConsoleIO::printMenuOption(2, "🔍 Ввести ID продукта вручную");
    ConsoleIO::printMenuOption(3, "📋 Показать все продукты");
    
    int choice = ConsoleIO::getInt("Выберите способ: ");
    
    int itemId = 0;
    
    switch (choice) {
        case 1:
            // Показываем категории и запоминаем выбранный ID
            {
                bool selecting = true;
                while (selecting) {
                    ConsoleIO::clearScreen();
                    ConsoleIO::printHeader("📁 ВЫБЕРИТЕ КАТЕГОРИЮ");
                    
                    ConsoleIO::printMenuOption(1, "🍎 Фрукты");
                    ConsoleIO::printMenuOption(2, "🥦 Овощи");
                    ConsoleIO::printMenuOption(3, "🥛 Напитки");
                    ConsoleIO::printMenuOption(4, "🍗 Белковые продукты");
                    ConsoleIO::printMenuOption(5, "🌾 Крупы и злаки");
                    ConsoleIO::printMenuOption(0, "🔙 Назад");
                    
                    int categoryChoice = ConsoleIO::getInt("Выберите категорию: ");
                    
                    std::string categoryName;
                    std::vector<int> categoryIds;
                    
                    switch (categoryChoice) {
                        case 1: 
                            categoryName = "🍎 ФРУКТЫ";
                            categoryIds = {1, 9, 10, 11, 12, 13, 34, 35, 36, 37, 38};
                            break;
                        case 2:
                            categoryName = "🥦 ОВОЩИ";
                            categoryIds = {7, 14, 15, 16, 17, 18, 39, 40, 41, 42, 43, 44};
                            break;
                        case 3:
                            categoryName = "🥛 НАПИТКИ";
                            categoryIds = {4, 19, 20, 21, 22, 23, 45, 46, 47, 48, 49};
                            break;
                        case 4:
                            categoryName = "🍗 БЕЛКОВЫЕ ПРОДУКТЫ";
                            categoryIds = {2, 5, 24, 25, 26, 27, 28, 50, 51, 52, 53, 54, 55};
                            break;
                        case 5:
                            categoryName = "🌾 КРУПЫ И ЗЛАКИ";
                            categoryIds = {3, 6, 8, 29, 30, 31, 32, 33, 56, 57, 58, 59, 60};
                            break;
                        case 0: 
                            return;
                        default:
                            ConsoleIO::printError("Неверный выбор!");
                            ConsoleIO::waitForEnter();
                            continue;
                    }
                    
                    // Показываем продукты категории и просим выбрать ID
                    ConsoleIO::clearScreen();
                    ConsoleIO::printHeader(categoryName);
                    
                    std::cout << "📋 Продукты в категории:\n\n";
                    
                    for (int id : categoryIds) {
                        NutritionItem* item = products.findItem(id);
                        if (item) {
                            std::cout << "ID: " << item->getId() << " | " << item->getName() 
                                      << " | Калории: " << item->getTotalCalories() << "/100г\n";
                        }
                    }
                    
                    itemId = ConsoleIO::getInt("\nВведите ID продукта: ");
                    NutritionItem* selectedItem = products.findItem(itemId);
                    
                    if (selectedItem) {
                        selecting = false;
                    } else {
                        ConsoleIO::printError("Продукт с таким ID не найден в этой категории!");
                        ConsoleIO::waitForEnter();
                    }
                }
            }
            break;
            
        case 2:
            // Ручной ввод ID
            itemId = ConsoleIO::getInt("Введите ID продукта: ");
            break;
            
        case 3:
            // Показываем все продукты
            listAllProducts();
            itemId = ConsoleIO::getInt("\nВведите ID продукта: ");
            break;
            
        default:
            ConsoleIO::printError("Неверный выбор!");
            return;
    }
    
    // Проверяем существование продукта
    NutritionItem* item = products.findItem(itemId);
    if (!item) {
        ConsoleIO::printError("Продукт/блюдо с таким ID не найден!");
        ConsoleIO::waitForEnter();
        return;
    }
    
    // Запрашиваем количество
    double quantity = ConsoleIO::getDouble("Введите количество в граммах: ");
    
    // Нормализуем дату (убираем время, оставляем только дату)
    std::time_t now = std::time(0);
    std::tm* timeinfo = std::localtime(&now);
    timeinfo->tm_hour = 0;
    timeinfo->tm_min = 0;
    timeinfo->tm_sec = 0;
    std::time_t today = std::mktime(timeinfo);
    
    // Добавляем meal на текущую дату
    nutrition.addMeal(today, item, quantity);
    
    ConsoleIO::printSuccess("✅ Прием пищи добавлен: " + item->getName() + " (" + std::to_string(quantity) + "г)");
    ConsoleIO::waitForEnter();
}

void NutritionSystem::viewMeals() {
    ConsoleIO::clearScreen();
    ConsoleIO::printHeader("👀 ПРОСМОТР ПРИЕМОВ ПИЩИ");
    
    // Нормализуем дату (убираем время, оставляем только дату)
    std::time_t now = std::time(0);
    std::tm* timeinfo = std::localtime(&now);
    timeinfo->tm_hour = 0;
    timeinfo->tm_min = 0;
    timeinfo->tm_sec = 0;
    std::time_t today = std::mktime(timeinfo);
    
    NutritionContainer& nutrition = diary.getNutritionManager();
    
    // Показываем отчет за сегодня
    nutrition.generateDailyReport(today);
    
    ConsoleIO::waitForEnter();
}

void NutritionSystem::editMeal() {
    ConsoleIO::clearScreen();
    ConsoleIO::printHeader("✏️ РЕДАКТИРОВАНИЕ ПРИЕМА ПИЩИ");
    
    // Нормализуем дату (убираем время, оставляем только дату)
    std::time_t now = std::time(0);
    std::tm* timeinfo = std::localtime(&now);
    timeinfo->tm_hour = 0;
    timeinfo->tm_min = 0;
    timeinfo->tm_sec = 0;
    std::time_t today = std::mktime(timeinfo);
    
    NutritionContainer& nutrition = diary.getNutritionManager();
    
    // Показываем приемы пищи за сегодня
    const auto& meals = nutrition.getMealsByDate(today);
    
    if (meals.empty()) {
        ConsoleIO::printWarning("На сегодня нет приемов пищи.");
        ConsoleIO::waitForEnter();
        return;
    }
    
    std::cout << "📋 Приемы пищи за сегодня:\n\n";
    for (size_t i = 0; i < meals.size(); ++i) {
        std::cout << "  " << (i + 1) << ". " << meals[i] << "\n";
    }
    
    int mealIndex = ConsoleIO::getInt("\nВведите номер приема пищи для редактирования: ") - 1;
    
    if (mealIndex < 0 || mealIndex >= static_cast<int>(meals.size())) {
        ConsoleIO::printError("Неверный номер приема пищи!");
        ConsoleIO::waitForEnter();
        return;
    }
    
    double newQuantity = ConsoleIO::getDouble("Введите новое количество (г): ");
    
    if (newQuantity <= 0) {
        ConsoleIO::printError("Количество должно быть положительным числом!");
        ConsoleIO::waitForEnter();
        return;
    }
    
    nutrition.editMeal(today, mealIndex, newQuantity);
    ConsoleIO::printSuccess("✅ Прием пищи отредактирован!");
    ConsoleIO::waitForEnter();
}

void NutritionSystem::removeMeal() {
    ConsoleIO::clearScreen();
    ConsoleIO::printHeader("🗑️ УДАЛЕНИЕ ПРИЕМА ПИЩИ");
    
    // Нормализуем дату (убираем время, оставляем только дату)
    std::time_t now = std::time(0);
    std::tm* timeinfo = std::localtime(&now);
    timeinfo->tm_hour = 0;
    timeinfo->tm_min = 0;
    timeinfo->tm_sec = 0;
    std::time_t today = std::mktime(timeinfo);
    
    NutritionContainer& nutrition = diary.getNutritionManager();
    
    // Показываем приемы пищи за сегодня
    const auto& meals = nutrition.getMealsByDate(today);
    
    if (meals.empty()) {
        ConsoleIO::printWarning("На сегодня нет приемов пищи.");
        ConsoleIO::waitForEnter();
        return;
    }
    
    std::cout << "📋 Приемы пищи за сегодня:\n\n";
    for (size_t i = 0; i < meals.size(); ++i) {
        std::cout << "  " << (i + 1) << ". " << meals[i] << "\n";
    }
    
    int mealIndex = ConsoleIO::getInt("\nВведите номер приема пищи для удаления: ") - 1;
    
    if (mealIndex < 0 || mealIndex >= static_cast<int>(meals.size())) {
        ConsoleIO::printError("Неверный номер приема пищи!");
        ConsoleIO::waitForEnter();
        return;
    }
    
    // Подтверждение удаления
    std::cout << "\nВы уверены, что хотите удалить этот прием пищи? (1 - да, 0 - нет): ";
    int confirm = ConsoleIO::getInt("");
    
    if (confirm == 1) {
        nutrition.removeMeal(today, mealIndex);
        ConsoleIO::printSuccess("✅ Прием пищи удален!");
    } else {
        ConsoleIO::printInfo("Удаление отменено.");
    }
    
    ConsoleIO::waitForEnter();
}

void NutritionSystem::addProduct() {
    ConsoleIO::clearScreen();
    ConsoleIO::printHeader("➕ ДОБАВЛЕНИЕ ПРОДУКТА");
    
    std::string name = ConsoleIO::getString("Название продукта: ");
    double calories = ConsoleIO::getDouble("Калории на 100г: ");
    double proteins = ConsoleIO::getDouble("Белки на 100г: ");
    double fats = ConsoleIO::getDouble("Жиры на 100г: ");
    double carbs = ConsoleIO::getDouble("Углеводы на 100г: ");
    
    Product* newProduct = diary.getProductManager().addProduct(name, calories, proteins, fats, carbs);
    if (newProduct) {
        ConsoleIO::printSuccess("Продукт успешно добавлен: " + name);
    } else {
        ConsoleIO::printError("Ошибка при добавлении продукта!");
    }
    ConsoleIO::waitForEnter();
}

void NutritionSystem::searchProduct() {
    ConsoleIO::clearScreen();
    ConsoleIO::printHeader("🔍 ПОИСК ПРОДУКТА");
    
    std::string name = ConsoleIO::getString("Название продукта для поиска: ");
    Product* product = diary.getProductManager().findProductByName(name);
    if (product) {
        std::cout << "✅ Найден продукт:\n";
        std::cout << *product << std::endl;
    } else {
        ConsoleIO::printError("❌ Продукт не найден");
    }
    ConsoleIO::waitForEnter();
}

void NutritionSystem::listAllProducts() {
    ConsoleIO::clearScreen();
    ConsoleIO::printHeader("📋 ВСЕ ПРОДУКТЫ");
    
    const auto& items = diary.getProductManager().getAllItems();
    if (items.empty()) {
        ConsoleIO::printWarning("Нет продуктов в базе данных.");
    } else {
        for (const auto& item : items) {
            std::cout << *item << "\n";
        }
    }
    ConsoleIO::waitForEnter();
}

void NutritionSystem::changeUserWeight(User* user) {
    ConsoleIO::clearScreen();
    ConsoleIO::printHeader("✏️ ИЗМЕНЕНИЕ ВЕСА");
    
    std::cout << "Текущий вес: " << user->getWeight() << " кг\n";
    double newWeight = ConsoleIO::getDouble("Новый вес (кг): ");
    
    user->setWeight(newWeight);
    ConsoleIO::printSuccess("✅ Вес обновлен! Новая дневная норма: " + 
                          std::to_string(user->calculateDailyCalories()) + " ккал");
    ConsoleIO::waitForEnter();
}