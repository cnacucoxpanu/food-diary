#ifndef PRODUCT_COMMANDS_H
#define PRODUCT_COMMANDS_H

#include "include/commands/command.h"
#include "include/containers/product_container.h"
#include <string>

class AddProductCommand : public Command {
private:
    ProductContainer& products;
    std::string name;
    double calories;
    double proteins;
    double fats;
    double carbs;

public:
    AddProductCommand(ProductContainer& products, const std::string& name, 
                     double calories, double proteins, double fats, double carbs);
    ~AddProductCommand();
    
    void execute() override;
    void undo() override;
    bool canUndo() const override { return true; }
    
    std::string getName() const override { return "AddProduct"; }
    std::string getDescription() const override { 
        return "Add product: " + name; 
    }
};

class RemoveProductCommand : public Command {
private:
    ProductContainer& products;
    int productId;

public:
    RemoveProductCommand(ProductContainer& products, int productId);
    ~RemoveProductCommand();
    
    void execute() override;
    void undo() override;
    bool canUndo() const override { return true; }
    
    std::string getName() const override { return "RemoveProduct"; }
    std::string getDescription() const override { 
        return "Remove product ID: " + std::to_string(productId); 
    }
};

#endif