#ifndef AUTH_EXCEPTION_H
#define AUTH_EXCEPTION_H

#include "include/exceptions/base_exception.h"

class AuthException : public BaseException {
public:
    explicit AuthException(const std::string& msg) : BaseException(msg) {}    
};

class UserNotFoundException : public AuthException {
public: 
    UserNotFoundException() : AuthException("User not found.") {}
};

class InvalidPasswordException : public AuthException {
public:
    InvalidPasswordException() : AuthException("Invalid password.") {}
};

class UserExistsException : public AuthException {
public:
    UserExistsException() : AuthException("User already exists.") {}
};

#endif