#include "header.h"
#include "NutritionSystem.h"
#include <windows.h>

int main()
{
    SetConsoleOutputCP(65001);
    SetConsoleCP(65001);

    NutritionSystem system;
    User* user = nullptr;
    
    system.load();
    user = system.login();
    
    if (user) {
        system.menuUser(user);
        system.logout();
    }

    system.save();
    return 0;
}