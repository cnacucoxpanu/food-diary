#ifndef USER_CONTAINER_H
#define USER_CONTAINER_H

#include "../core/user.h"
#include <vector>
#include <map>
#include <iostream>

class UserContainer {
private:
    std::vector<User*> users;  // ИЗМЕНЕНО: указатели вместо объектов
    std::map<std::string, std::string> passwords; // username -> password
    User* currentUser;

public:
    UserContainer();
    ~UserContainer();
    
    // Запрещаем копирование и присваивание для предотвращения проблем с указателями
    UserContainer(const UserContainer&) = delete;
    UserContainer& operator=(const UserContainer&) = delete;
    
    void addUser(User* user, const std::string& password);  // ИЗМЕНЕНО: первый параметр
    User* findUser(const std::string& username) const;
    User* getCurrentUser() const;
    void setCurrentUser(User* user);
    void logout();
    
    bool checkPassword(const std::string& username, const std::string& password) const;
    bool usernameExists(const std::string& username) const;
    void updatePassword(const std::string& username, const std::string& newPassword);
    bool loadFromFile(const std::string& filename);
    bool saveToFile(const std::string& filename) const;
    bool loadPasswords(const std::string& filename);
    bool savePasswords(const std::string& filename) const;
    
    const std::vector<User*>& getAllUsers() const { return users; }  // ИЗМЕНЕНО
    
    friend std::ostream& operator<<(std::ostream& os, const UserContainer& container);
};

#endif