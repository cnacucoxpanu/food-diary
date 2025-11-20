#include "../../header.h"

void ConsoleIO::printError(const std::string& message) {
    std::cout << RED << "⛔ " << message << RESET << std::endl;
}

void ConsoleIO::printSuccess(const std::string& message) {
    std::cout << GREEN << "✅ " << message << RESET << std::endl;
}

void ConsoleIO::printInfo(const std::string& message) {
    std::cout << BLUE << "ℹ️  " << message << RESET << std::endl;
}

void ConsoleIO::printWarning(const std::string& message) {
    std::cout << YELLOW << "⚠️  " << message << RESET << std::endl;
}

void ConsoleIO::printHeader(const std::string& message) {
    std::cout << MAGENTA << "✨ " << message << " ✨" << RESET << std::endl;
}

void ConsoleIO::printMenuOption(int number, const std::string& option) {
    std::cout << CYAN << number << ". " << RESET << option << std::endl;
}

std::string ConsoleIO::getString(const std::string& prompt) {
    std::cout << CYAN << prompt << RESET;
    std::string input;
    std::getline(std::cin, input);
    return StringUtils::trim(input);
}

double ConsoleIO::getDouble(const std::string& prompt) {
    while (true) {
        std::cout << CYAN << prompt << RESET;
        std::string input;
        std::getline(std::cin, input);
        try {
            return std::stod(input);
        } catch (const std::exception&) {
            printError("Неверный формат числа. Попробуйте снова.");
        }
    }
}

int ConsoleIO::getInt(const std::string& prompt) {
    while (true) {
        std::cout << CYAN << prompt << RESET;
        std::string input;
        std::getline(std::cin, input);
        try {
            return std::stoi(input);
        } catch (const std::exception&) {
            printError("Неверный формат числа. Попробуйте снова.");
        }
    }
}

void ConsoleIO::clearScreen() {
#ifdef _WIN32
    system("cls");
#else
    system("clear");
#endif
}

void ConsoleIO::waitForEnter() {
    std::cout << YELLOW << "Нажмите Enter для продолжения..." << RESET;
    std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
    std::cin.get();
}

void ConsoleIO::showUserMenu() {
    printHeader("МЕНЮ ПОЛЬЗОВАТЕЛЯ");
    printMenuOption(1, "📊 Мой дневник питания");
    printMenuOption(2, "🍎 Каталог продуктов");
    printMenuOption(3, "👨‍🍳 Управление блюдами");
    printMenuOption(4, "📈 Отчеты и статистика");
    printMenuOption(5, "👤 Мой профиль");
    printMenuOption(6, "🏆 Мои достижения");
    printMenuOption(0, "🚪 Выход");
}

void ConsoleIO::showAdminMenu() {
    printHeader("АДМИНИСТРАТИВНОЕ МЕНЮ");
    printMenuOption(1, "📦 Управление продуктами");
    printMenuOption(2, "👥 Управление пользователями");
    printMenuOption(3, "📊 Системная статистика");
    printMenuOption(4, "🔧 Настройки системы");
    printMenuOption(0, "🔙 Назад");
}

void ConsoleIO::showDiaryMenu() {
    printHeader("ДНЕВНИК ПИТАНИЯ");
    printMenuOption(1, "➕ Добавить прием пищи");
    printMenuOption(2, "👀 Просмотреть записи за день");
    printMenuOption(3, "✏️ Редактировать запись");
    printMenuOption(4, "🗑️ Удалить запись");
    printMenuOption(5, "📅 Выбрать другую дату");
    printMenuOption(0, "🔙 Назад");
}

void ConsoleIO::showProductsMenu() {
    printHeader("КАТАЛОГ ПРОДУКТОВ");
    printMenuOption(1, "🔍 Поиск продукта");
    printMenuOption(2, "📋 Список всех продуктов");
    printMenuOption(3, "➕ Добавить новый продукт");
    printMenuOption(4, "📁 Просмотр по категориям");
    printMenuOption(5, "⭐ Избранные продукты");
    printMenuOption(0, "🔙 Назад");
}

void ConsoleIO::showReportsMenu() {
    printHeader("ОТЧЕТЫ И СТАТИСТИКА");
    printMenuOption(1, "📅 Дневной отчет");
    printMenuOption(2, "📆 Отчет за период");
    printMenuOption(3, "📈 Анализ прогресса");
    printMenuOption(4, "🥗 Анализ питания");
    printMenuOption(5, "🎯 Рекомендации");
    printMenuOption(0, "🔙 Назад");
}