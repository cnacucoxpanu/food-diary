#include "../../header.h"

AddProductCommand::AddProductCommand(ProductContainer& products, const std::string& name,
                                   double calories, double proteins, double fats, double carbs)
    : products(products), name(name), calories(calories), proteins(proteins), 
      fats(fats), carbs(carbs) {}

AddProductCommand::~AddProductCommand() {}

void AddProductCommand::execute() {
    products.addProduct(name, calories, proteins, fats, carbs);
}

void AddProductCommand::undo() {
    // В реальном приложении здесь должна быть логика отмены добавления
}

RemoveProductCommand::RemoveProductCommand(ProductContainer& products, int productId)
    : products(products), productId(productId) {}

RemoveProductCommand::~RemoveProductCommand() {}

void RemoveProductCommand::execute() {
    products.removeItem(productId);
}

void RemoveProductCommand::undo() {
    // В реальном приложении здесь должна быть логика восстановления удаленного продукта
}