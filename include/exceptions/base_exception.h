#ifndef BASE_EXCEPTION_H
#define BASE_EXCEPTION_H
#include <string>
#include <exception>
#include <iostream>

class BaseException : public std::exception {
protected:
    std::string message;

public: 
    explicit BaseException (const std::string& msg) : message(msg) {}
    virtual const char* what() const noexcept override { return message.c_str(); }

    virtual void printDetails() const {
        std::cerr << "Exception: " << message << std::endl;
    }

    friend std::ostream& operator<<(std::ostream& os, const BaseException& ex) {
        os << "Exception: " << ex.message;
        return os;
    }
};

#endif