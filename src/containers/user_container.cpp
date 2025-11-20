#include "../header.h" 

UserContainer::UserContainer() : currentUser(nullptr) {}

UserContainer::~UserContainer() {
    for (auto* user : users) {
        delete user;
    }
    users.clear();
}

void UserContainer::addUser(User* user, const std::string& password) {
    users.push_back(user);
    passwords[user->getUsername()] = password;
}

User* UserContainer::findUser(const std::string& username) const {
    for (const auto& user : users) {
        if (user && user->getUsername() == username) {
            return user;
        }
    }
    return nullptr;
}

User* UserContainer::getCurrentUser() const {
    return currentUser;
}

void UserContainer::setCurrentUser(User* user) {
    currentUser = user;
}

void UserContainer::logout() {
    currentUser = nullptr;
}

bool UserContainer::checkPassword(const std::string& username, const std::string& password) const {
    auto it = passwords.find(username);
    if (it != passwords.end()) {
        return it->second == password;
    }
    return false;
}

bool UserContainer::usernameExists(const std::string& username) const {
    // Проверяем наличие пользователя в векторе (основной источник)
    return findUser(username) != nullptr;
}

void UserContainer::updatePassword(const std::string& username, const std::string& newPassword) {
    // Обновляем пароль в карте, даже если его еще нет (для новых пользователей)
    passwords[username] = newPassword;
}

bool UserContainer::loadFromFile(const std::string& filename) {
    std::ifstream file(filename);
    if (!file.is_open()) {
        return false;
    }
    
    std::string line;
    while (std::getline(file, line)) {
        // Пропускаем пустые строки и комментарии
        if (line.empty() || line[0] == '#') continue;
        
        // Убираем пробелы в начале и конце
        line = StringUtils::trim(line);
        if (line.empty()) continue;
        
        std::vector<std::string> parts = StringUtils::split(line, '|');
        if (parts.size() == 6) {
            try {
                std::string username = StringUtils::trim(parts[0]);
                double weight = std::stod(StringUtils::trim(parts[1]));
                double height = std::stod(StringUtils::trim(parts[2]));
                int age = std::stoi(StringUtils::trim(parts[3]));
                
                // Проверяем, что username не пустой и пользователь еще не существует
                if (username.empty() || findUser(username) != nullptr) {
                    continue; // Пропускаем дубликаты и пустые имена
                }
                
                Goal goal = Goal::MAINTENANCE;
                std::string goalStr = StringUtils::trim(parts[4]);
                if (goalStr == "WEIGHT_LOSS") goal = Goal::WEIGHT_LOSS;
                else if (goalStr == "WEIGHT_GAIN") goal = Goal::WEIGHT_GAIN;
                
                ActivityLevel activity = ActivityLevel::MODERATE;
                std::string activityStr = StringUtils::trim(parts[5]);
                if (activityStr == "SEDENTARY") activity = ActivityLevel::SEDENTARY;
                else if (activityStr == "LIGHT") activity = ActivityLevel::LIGHT;
                else if (activityStr == "ACTIVE") activity = ActivityLevel::ACTIVE;
                else if (activityStr == "VERY_ACTIVE") activity = ActivityLevel::VERY_ACTIVE;
                
                users.push_back(new User(username, weight, height, age, goal, activity));
            } catch (const std::exception& e) {
                // Пропускаем строки с ошибками парсинга
                continue;
            }
        }
    }
    
    file.close();
    return true;
}

bool UserContainer::saveToFile(const std::string& filename) const {
    std::ofstream file(filename);
    if (!file.is_open()) {
        return false;
    }
    
    file << "# username|weight|height|age|goal|activity_level\n";
    for (const auto& user : users) {
        if (user) {
            file << user->getUsername() << "|"
                 << user->getWeight() << "|"
                 << user->getHeight() << "|"
                 << user->getAge() << "|";
            
            switch (user->getGoal()) {
                case Goal::WEIGHT_LOSS: file << "WEIGHT_LOSS"; break;
                case Goal::MAINTENANCE: file << "MAINTENANCE"; break;
                case Goal::WEIGHT_GAIN: file << "WEIGHT_GAIN"; break;
            }
            file << "|";
            
            switch (user->getActivity()) {
                case ActivityLevel::SEDENTARY: file << "SEDENTARY"; break;
                case ActivityLevel::LIGHT: file << "LIGHT"; break;
                case ActivityLevel::MODERATE: file << "MODERATE"; break;
                case ActivityLevel::ACTIVE: file << "ACTIVE"; break;
                case ActivityLevel::VERY_ACTIVE: file << "VERY_ACTIVE"; break;
            }
            file << "\n";
        }
    }
    
    file.close();
    return true;
}

bool UserContainer::loadPasswords(const std::string& filename) {
    std::ifstream file(filename);
    if (!file.is_open()) {
        return false;
    }
    
    passwords.clear();
    std::string line;
    
    while (std::getline(file, line)) {
        // Пропускаем пустые строки и комментарии
        if (line.empty() || line[0] == '#') continue;
        
        // Убираем пробелы в начале и конце
        line = StringUtils::trim(line);
        if (line.empty()) continue;
        
        std::vector<std::string> parts = StringUtils::split(line, '|');
        if (parts.size() == 2) {
            std::string username = StringUtils::trim(parts[0]);
            std::string password = StringUtils::trim(parts[1]);
            
            // Проверяем, что username и password не пустые
            if (!username.empty() && !password.empty()) {
                passwords[username] = password;
            }
        }
    }
    
    file.close();
    return true;
}

bool UserContainer::savePasswords(const std::string& filename) const {
    std::ofstream file(filename);
    if (!file.is_open()) {
        return false;
    }
    
    file << "# username|password\n";
    for (const auto& [username, password] : passwords) {
        file << username << "|" << password << "\n";
    }
    
    file.close();
    return true;
}

std::ostream& operator<<(std::ostream& os, const UserContainer& container) {
    os << "Всего пользователей: " << container.users.size() << "\n";
    for (const auto& user : container.users) {
        if (user) {
            os << *user << "\n";
        }
    }
    return os;
}