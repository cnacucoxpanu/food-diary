#include "../../header.h"

ProductContainer::ProductContainer() : nextId(1) {}

ProductContainer::~ProductContainer() {}

Product* ProductContainer::addProduct(const std::string& name, double calories, 
                                     double proteins, double fats, double carbs) {
    auto product = std::make_unique<Product>(nextId++, name, calories, proteins, fats, carbs);
    Product* ptr = product.get();
    items.push_back(std::move(product));
    return ptr;
}

Product* ProductContainer::addProductWithId(int id, const std::string& name, double calories, 
                                          double proteins, double fats, double carbs) {
    // Проверяем, нет ли уже продукта с таким ID
    if (findItem(id) != nullptr) {
        return nullptr;
    }
    
    auto product = std::make_unique<Product>(id, name, calories, proteins, fats, carbs);
    Product* ptr = product.get();
    items.push_back(std::move(product));
    
    // Обновляем nextId если необходимо
    if (id >= nextId) {
        nextId = id + 1;
    }
    
    return ptr;
}

Dish* ProductContainer::addDish(const std::string& name) {
    auto dish = std::make_unique<Dish>(nextId++, name);
    Dish* ptr = dish.get();
    items.push_back(std::move(dish));
    return ptr;
}

bool ProductContainer::removeItem(int id) {
    auto it = std::remove_if(items.begin(), items.end(),
        [id](const std::unique_ptr<NutritionItem>& item) {
            return item->getId() == id;
        });
    
    if (it != items.end()) {
        items.erase(it, items.end());
        return true;
    }
    return false;
}

NutritionItem* ProductContainer::findItem(int id) {
    for (auto& item : items) {
        if (item->getId() == id) {
            return item.get();
        }
    }
    return nullptr;
}

Product* ProductContainer::findProductByName(const std::string& name) {
    for (auto& item : items) {
        if (item->getName() == name && item->getType() == "PRODUCT") {
            return static_cast<Product*>(item.get());
        }
    }
    return nullptr;
}

bool ProductContainer::loadFromFile(const std::string& filename) {
    std::ifstream file(filename);
    if (!file.is_open()) {
        return false;
    }
    
    std::string line;
    while (std::getline(file, line)) {
        if (line.empty() || line[0] == '#') continue;
        
        std::vector<std::string> parts = StringUtils::split(line, '|');
        if (parts.size() == 6) {
            int id = std::stoi(parts[0]);
            std::string name = parts[1];
            double calories = std::stod(parts[2]);
            double proteins = std::stod(parts[3]);
            double fats = std::stod(parts[4]);
            double carbs = std::stod(parts[5]);
            
            // Используем addProductWithId для сохранения оригинальных ID
            if (!addProductWithId(id, name, calories, proteins, fats, carbs)) {
                std::cerr << "Предупреждение: Продукт с ID " << id << " уже существует. Пропускаем." << std::endl;
            }
        }
    }
    
    file.close();
    return true;
}

bool ProductContainer::saveToFile(const std::string& filename) const {
    std::ofstream file(filename);
    if (!file.is_open()) {
        return false;
    }
    
    file << "# id|name|calories|proteins|fats|carbs\n";
    for (const auto& item : items) {
        if (item->getType() == "PRODUCT") {
            file << item->getId() << "|"
                 << item->getName() << "|"
                 << item->getBaseCalories() << "|"
                 << item->getBaseProteins() << "|"
                 << item->getBaseFats() << "|"
                 << item->getBaseCarbs() << "\n";
        }
    }
    
    file.close();
    return true;
}

std::ostream& operator<<(std::ostream& os, const ProductContainer& container) {
    os << "Всего продуктов: " << container.items.size() << "\n";
    for (const auto& item : container.items) {
        os << *item << "\n";
    }
    return os;
}