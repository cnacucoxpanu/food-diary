#ifndef USER_H
#define USER_H

#include <string>
#include <iostream>

enum class Goal { WEIGHT_LOSS, MAINTENANCE, WEIGHT_GAIN };
enum class ActivityLevel { SEDENTARY, LIGHT, MODERATE, ACTIVE, VERY_ACTIVE };

class User {
private:
    std::string username;
    std::string passwordHash;  // ДОБАВЛЕНО
    double weight;
    double height;
    int age;
    Goal goal;
    ActivityLevel activity;

public:
    User();
    User(const std::string& username, double weight, double height, 
         int age, Goal goal, ActivityLevel activity);
    ~User();
    
    std::string getUsername() const { return username; }
    std::string getPasswordHash() const { return passwordHash; }  // ДОБАВЛЕНО
    
    double getWeight() const { return weight; }
    double getHeight() const { return height; }
    int getAge() const { return age; }
    Goal getGoal() const { return goal; }
    ActivityLevel getActivity() const { return activity; }
    
    void setWeight(double newWeight);
    void setPassword(const std::string& password) { passwordHash = password; }  // ДОБАВЛЕНО
    void setGoal(Goal newGoal) { goal = newGoal; }
    void setActivity(ActivityLevel newActivity) { activity = newActivity; }
    
    double calculateDailyCalories() const;
    
    friend std::ostream& operator<<(std::ostream& os, const User& user) {
        os << "User: " << user.username << " (Weight: " << user.weight
           << "kg, Height: " << user.height << "cm, Age: " << user.age << ")";
        return os;
    }
    
    bool operator==(const User& other) const {
        return username == other.username;
    }
};

#endif