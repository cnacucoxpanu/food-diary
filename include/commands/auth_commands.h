#ifndef AUTH_COMMANDS_H
#define AUTH_COMMANDS_H

#include "include/commands/command.h"
#include "include/containers/user_container.h"
#include <string>

class RegisterCommand : public Command {
private:
    UserContainer& users;
    std::string username;
    std::string password;
    double weight;
    double height;
    int age;
    Goal goal;
    ActivityLevel activity;

public:
    RegisterCommand(UserContainer& users, const std::string& username, const std::string& password,
                   double weight, double height, int age, Goal goal, ActivityLevel activity);
    ~RegisterCommand();
    
    void execute() override;
    
    std::string getName() const override { return "Register"; }
    std::string getDescription() const override { 
        return "Register new user: " + username; 
    }
};

class LoginCommand : public Command {
private:
    UserContainer& users;
    std::string username;
    std::string password;

public:
    LoginCommand(UserContainer& users, const std::string& username, const std::string& password);
    ~LoginCommand();
    
    void execute() override;
    
    std::string getName() const override { return "Login"; }
    std::string getDescription() const override { 
        return "Login user: " + username; 
    }
};

class LogoutCommand : public Command {
private:
    UserContainer& users;

public:
    explicit LogoutCommand(UserContainer& users);
    ~LogoutCommand();
    
    void execute() override;
    
    std::string getName() const override { return "Logout"; }
    std::string getDescription() const override { return "Logout current user"; }
};

#endif