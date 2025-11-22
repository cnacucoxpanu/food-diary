#include "../header.h"  // ПРАВИЛЬНЫЙ ПУТЬ ИЗ src/commands/

RegisterCommand::RegisterCommand(UserContainer& users, const std::string& username, 
                               const std::string& password, double weight, double height, 
                               int age, Goal goal, ActivityLevel activity)
    : users(users), username(username), password(password), weight(weight), 
      height(height), age(age), goal(goal), activity(activity) {}

RegisterCommand::~RegisterCommand() {}

void RegisterCommand::execute() {
    // Валидация входных данных
    if (username.empty()) {
        throw AuthException("Имя пользователя не может быть пустым.");
    }
    
    if (password.empty()) {
        throw AuthException("Пароль не может быть пустым.");
    }
    
    if (users.usernameExists(username)) {
        throw UserExistsException();
    }
    
    // Валидация физических параметров
    if (weight <= 0 || height <= 0 || age <= 0) {
        throw AuthException("Вес, рост и возраст должны быть положительными числами.");
    }
    
    User* newUser = new User(username, weight, height, age, goal, activity);
    users.addUser(newUser, password);
    users.setCurrentUser(users.findUser(username));
}


LoginCommand::LoginCommand(UserContainer& users, const std::string& username, 
                         const std::string& password)
    : users(users), username(username), password(password) {}

LoginCommand::~LoginCommand() {}

void LoginCommand::execute() {
    // Валидация входных данных
    if (username.empty()) {
        throw AuthException("Имя пользователя не может быть пустым.");
    }
    
    if (password.empty()) {
        throw AuthException("Пароль не может быть пустым.");
    }
    
    User* user = users.findUser(username);
    if (!user) {
        throw UserNotFoundException();
    }
    
    if (!users.checkPassword(username, password)) {
        throw InvalidPasswordException();
    }
    
    users.setCurrentUser(user);
}


LogoutCommand::LogoutCommand(UserContainer& users) : users(users) {}

LogoutCommand::~LogoutCommand() {}

void LogoutCommand::execute() {
    users.logout();
}
