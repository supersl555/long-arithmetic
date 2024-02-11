#include "LongNumber.h"
#include <iomanip>
#include <vector>
#include <sstream>

// Конструктор по умолчанию
LongNumber::LongNumber() : digits("0"), precision(2) {}

// Конструктор с инициализацией
LongNumber::LongNumber(const std::string& number, int precision) : digits(number), precision(precision) {}

// Конструктор с преобразованием из double
LongNumber::LongNumber(double number, int precision) : precision(precision) {
    std::ostringstream ss;
    ss << std::fixed << std::setprecision(precision) << number;
    digits = ss.str();
}

// Операция сложения
std::pair<std::string, std::string> splitNumber(const std::string& number) {
    std::istringstream iss(number);
    std::string integerPart;
    std::string fractionalPart;

    // Читаем целую часть
    if (std::getline(iss, integerPart, '.')) {
        // Если есть дробная часть, читаем ее
        std::getline(iss, fractionalPart);
    }

    return std::make_pair(integerPart, fractionalPart);
}

std::vector<int> convertToDigitsVector(const std::string& numberString) {
    std::vector<int> digits;
    for (char digitChar : numberString) {
        if (isdigit(digitChar)) {
            digits.push_back(digitChar - '0');
        }
    }
    return digits;
}

void alignVectors_1(std::vector<int>& vec1, std::vector<int>& vec2) {
    int size1 = vec1.size();
    int size2 = vec2.size();
    
    // Если размеры векторов уже совпадают, выход
    if (size1 == size2) return;

    // Добавляем ведущие нули к меньшему вектору
    if (size1 < size2) {
        int len = size2 - size1;
        vec1.insert(vec1.begin(), len, 0);
    } else {
        int len = size1 - size2;
        vec2.insert(vec2.begin(), len, 0);
    }
}

void alignVectors_2(std::vector<int>& vec1, std::vector<int>& vec2) {
    int size1 = vec1.size();
    int size2 = vec2.size();
    
    // Если размеры векторов уже совпадают, выход
    if (size1 == size2) return;

    // Добавляем ведущие нули к меньшему вектору
    if (size1 < size2) {
        int len = size2 - size1;
        vec1.insert(vec1.end(), len, 0);
    } else {
        int len = size1 - size2;
        vec2.insert(vec2.end(), len, 0);
    }
}

std::vector<int> addDigits(const std::vector<int>& digits1, const std::vector<int>& digits2) {
    std::vector<int> sumDigits;
    int carry = 0;
    
    for (int i = digits1.size() - 1; i >= 0; --i) {
        int sum = digits1[i] + digits2[i] + carry;
        sumDigits.insert(sumDigits.begin(), sum % 10);
        carry = sum / 10;
    }
    
    if (carry > 0) {
        sumDigits.insert(sumDigits.begin(), carry);
    }
    
    return sumDigits;
}

LongNumber LongNumber::operator+(const LongNumber& other) const {
    // Вычисляем точность для результата как максимальную из точностей операндов
    int resultPrecision = std::max(precision, other.precision);

    // Разбиваем числа на целую и дробную части
    std::pair<std::string, std::string> num1Parts = splitNumber(digits);
    std::pair<std::string, std::string> num2Parts = splitNumber(other.digits);

    // Сложение целой части 
    // Переводим строки в векторы цифр
    std::vector<int> digits1 = convertToDigitsVector(num1Parts.first);
    std::vector<int> digits2 = convertToDigitsVector(num2Parts.first);
    
    // Выравниваем векторы по длине
    alignVectors_1(digits1, digits2);
    
    // Выполняем сложение цифр
    std::vector<int> sumDigits = addDigits(digits1, digits2);



    // Складываем дробные части с учетом точности
    // Преобразуем строки в векторы цифр
    std::string result_2;
    digits1 = convertToDigitsVector(num1Parts.second);
    digits2 = convertToDigitsVector(num2Parts.second);

    // Добавляем нули в конец векторов, чтобы выровнять их по длине
    alignVectors_2(digits1, digits2);

    // Выполняем сложение
    int carry = 0;
    for (int i = digits1.size() - 1; i >= 0; --i) {
        int sum = digits1[i] + digits2[i] + carry;
        result_2.insert(result_2.begin(), sum % 10 + '0');
        carry = sum / 10;
    }

    // Если остался перенос, добавляем его к целой части
    if (carry > 0) {
        std::vector<int> onesVector(1, carry);
        alignVectors_1(sumDigits, onesVector);
        sumDigits = addDigits(sumDigits, onesVector);
    }

    // Меняем строку до заданной точности
    int len = result_2.length();
    if (resultPrecision > len){
        result_2 += std::string(resultPrecision - len, '0');
    } else {
        result_2 = result_2.substr(0, resultPrecision);
    }



    // Преобразуем результаты в строку
    std::string result_1;
    for (int digit : sumDigits) {
        result_1 += std::to_string(digit);
    }

    std::string sum;
    if (resultPrecision > 0){
        sum = result_1 + "." + result_2;
    } else {
        sum = result_1;
    }

    // Создаем новый объект LongNumber с полученной суммой и точностью
    return LongNumber(sum, resultPrecision);
}


// // Операция вычитания
// LongNumber LongNumber::operator-(const LongNumber& other) const {
   
// }

// // Операция умножения
// LongNumber LongNumber::operator*(const LongNumber& other) const {
   
// }

// // Операция деления
// LongNumber LongNumber::operator/(const LongNumber& other) const {
    
// }

// // Операция сравнения ==
// bool LongNumber::operator==(const LongNumber& other) const {
    
// }

// // Операция сравнения !=
// bool LongNumber::operator!=(const LongNumber& other) const {
    
// }

// // Операция сравнения <
// bool LongNumber::operator<(const LongNumber& other) const {
    
// }

// // Операция сравнения >
// bool LongNumber::operator>(const LongNumber& other) const {
    
// }

// // Создание из литерала с плавающей точкой
// LongNumber LongNumber::fromDouble(double number, int precision) {
//     return LongNumber(number, precision);
// }

// Преобразование в строку
std::string LongNumber::toString() const {
    return digits;
}

// Установка точности
void LongNumber::setPrecision(int precision) {
    this->precision = precision;
}
