#ifndef NUTRITION_EXCEPTION_H
#define NUTRITION_EXCEPTION_H

#include "include/exceptions/base_exception.h"

class NutritionException : public BaseException {
public:
    explicit NutritionException(const std::string& msg) : BaseException(msg) {}
};

class ProductNotFoundException : public NutritionException {
public:
    ProductNotFoundException(int id) : NutritionException("Product not found: " + std::to_string(id)) {}
};

class InvalidNutritionValue : public NutritionException {
public:
    InvalidNutritionValue(const std::string& nutrient) : NutritionException("Invalid " + nutrient + "value") {}
};

#endif