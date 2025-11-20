#include "../../header.h"

Dish::Dish() : Product() {}

Dish::Dish(int id, const std::string& name) : Product(id, name, 0, 0, 0, 0) {}

Dish::~Dish() {}

void Dish::addIngredient(Product* product, double quantity) {
    if (product) {
        ingredients.push_back(std::make_pair(product, quantity));
    }
}

void Dish::removeIngredient(int productId) {
    ingredients.erase(
        std::remove_if(ingredients.begin(), ingredients.end(),
            [productId](const auto& ingredient) {
                return ingredient.first->getId() == productId;
            }),
        ingredients.end()
    );
}

double Dish::getTotalCalories() const {
    double total = 0;
    for (const auto& ingredient : ingredients) {
        total += ingredient.first->getTotalCalories() * (ingredient.second / 100.0);
    }
    return total;
}

double Dish::getTotalProteins() const {
    double total = 0;
    for (const auto& ingredient : ingredients) {
        total += ingredient.first->getTotalProteins() * (ingredient.second / 100.0);
    }
    return total;
}

double Dish::getTotalFats() const {
    double total = 0;
    for (const auto& ingredient : ingredients) {
        total += ingredient.first->getTotalFats() * (ingredient.second / 100.0);
    }
    return total;
}

double Dish::getTotalCarbs() const {
    double total = 0;
    for (const auto& ingredient : ingredients) {
        total += ingredient.first->getTotalCarbs() * (ingredient.second / 100.0);
    }
    return total;
}