#ifndef CONSOLE_IO_H
#define CONSOLE_IO_H

#include "colors.h"
#include <iostream>
#include <string>

class ConsoleIO {
public:
    static void printError(const std::string& message);
    static void printSuccess(const std::string& message);
    static void printInfo(const std::string& message);
    static void printWarning(const std::string& message);
    static void printHeader(const std::string& message);
    static void printMenuOption(int number, const std::string& option);
    
    static std::string getString(const std::string& prompt);
    static double getDouble(const std::string& prompt);
    static int getInt(const std::string& prompt);
    
    static void clearScreen();
    static void waitForEnter();
    
    static void showUserMenu();
    static void showAdminMenu();
    static void showDiaryMenu();
    static void showProductsMenu();
    static void showReportsMenu();
};

#endif