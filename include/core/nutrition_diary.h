#ifndef NUTRITION_DIARY_H
#define NUTRITION_DIARY_H

#include "include/containers/user_container.h"
#include "include/containers/product_container.h"
#include "include/containers/nutrition_container.h"

class NutritionDiary {
private:
    UserContainer users;
    ProductContainer products;
    NutritionContainer nutrition;

public:
    NutritionDiary();
    ~NutritionDiary();

    UserContainer& getUserManager() { return users; }
    ProductContainer& getProductManager() { return products; }
    NutritionContainer& getNutritionManager() { return nutrition; }
    
    bool loadAllData();
    bool saveAllData();
    
    void generateDailyReport(std::time_t date) const;
    void generatePeriodReport(std::time_t startDate, std::time_t endDate) const;
};

#endif