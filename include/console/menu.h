#ifndef MENU_H
#define MENU_H

#include "include/console/colors.h"
#include "include/commands/command.h"
#include <vector>
#include <memory>

class Menu {
private:
    std::string title;
    std::vector<std::string> options;
    std::vector<std::unique_ptr<Command>> commands;
    
public:
    Menu(const std::string& title);
    Menu();
    ~Menu();
    void addOption(const std::string& option, std::unique_ptr<Command> command);
    void display() const;
    void executeOption(int choice);
    int getChoice() const;

    int getOptionCount() const { return options.size(); }
};

#endif