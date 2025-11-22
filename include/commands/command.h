#ifndef COMMAND_H
#define COMMAND_H

#include <string>
#include <iostream>

class Command {
public:
    Command();
    virtual ~Command();
    
    virtual void execute() = 0;
    virtual void undo() {}  // Пустая реализация по умолчанию
    
    virtual std::string getName() const = 0;
    virtual std::string getDescription() const = 0;
    
    friend std::ostream& operator<<(std::ostream& os, const Command& cmd);
};

#endif