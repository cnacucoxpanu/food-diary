#ifndef HEADER_H
#define HEADER_H

#include <iostream>
#include <fstream>
#include <vector>
#include <map>
#include <memory>
#include <string>
#include <sstream>
#include <ctime>
#include <algorithm>
#include <functional>
#include <limits>
#include <iomanip>
#include <cstring>

// Базовые исключения
#include "include/exceptions/base_exception.h"

// Утилиты
#include "include/utils/string_utils.h"
#include "include/utils/file_utils.h"
#include "include/utils/nutrition_calculator.h"

// Ядра системы
#include "include/core/nutrition_item.h"
#include "include/core/product.h"
#include "include/core/dish.h"
#include "include/core/meal.h"
#include "include/core/user.h"
#include "include/core/nutrition_diary.h"

// Контейнеры
#include "include/containers/user_container.h"
#include "include/containers/product_container.h"
#include "include/containers/nutrition_container.h"
#include "include/containers/listNode.h"

// Консольный интерфейс
#include "include/console/colors.h"
#include "include/console/console_io.h"

// Исключения
#include "include/exceptions/auth_exception.h"
#include "include/exceptions/nutrition_exception.h"
#include "include/exceptions/data_exception.h"

// Константы
#define MAX_STR 256
#define DATA_PATH "data/"

// Вспомогательные функции
inline void waitForAnyKey() {
    std::cout << "\nНажмите Enter для продолжения...";
    std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
    std::cin.get();
}

#endif