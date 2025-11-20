#include "../../header.h"

Menu::Menu(const std::string& title) : title(title) {}

Menu::Menu() : title("Меню") {}

Menu::~Menu() {}

void Menu::addOption(const std::string& option, std::unique_ptr<Command> command) {
    options.push_back(option);
    commands.push_back(std::move(command));
}

void Menu::display() const {
    std::cout << BOLD_BLUE << "=== " << title << " ===" << RESET << std::endl;
    for (size_t i = 0; i < options.size(); ++i) {
        std::cout << i + 1 << ". " << options[i] << std::endl;
    }
    std::cout << "0. 🔙 Назад" << std::endl;
}

void Menu::executeOption(int choice) {
    if (choice > 0 && choice <= static_cast<int>(commands.size())) {
        try {
            commands[choice - 1]->execute();
        } catch (const std::exception& e) {
            ConsoleIO::printError(e.what());
        }
    }
}

int Menu::getChoice() const {
    int choice;
    std::cout << CYAN << "Выберите пункт: " << RESET;
    std::cin >> choice;
    std::cin.ignore();
    return choice;
}