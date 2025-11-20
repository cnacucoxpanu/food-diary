#ifndef DATA_EXCEPTION_H
#define DATA_EXCEPTION_H

#include "include/exceptions/base_exception.h"

class DataException : public BaseException {
public:
    explicit DataException(const std::string& msg) : BaseException(msg) {}
};

class FileNotFoundException : public DataException {
public: 
    FileNotFoundException(const std::string& filename) : DataException("File not found: " + filename) {}
};

class ParseException : public DataException {
public:
    ParseException(const std::string& data) : DataException("Parse error: " + data) {}
};

#endif