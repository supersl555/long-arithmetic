#include "LongNumber.h"
#include <iomanip>
#include <vector>
#include <sstream>
#include <algorithm>

std::string LongNumber::toString() const {
    return digits;
}

// Установка точности
void LongNumber::setPrecision(int precision) {
    this->precision = precision;
}

LongNumber::LongNumber() : digits("0"), precision(2) {}

// Конструктор с инициализацией
LongNumber::LongNumber(const std::string& number, int precision) : digits(number), precision(precision) {}

// Конструктор с преобразованием из double
LongNumber::LongNumber(double number, int precision) : precision(precision) {
    std::ostringstream ss;
    ss << std::fixed << std::setprecision(precision) << number;
    digits = ss.str();
}

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

bool LongNumber::operator>(const LongNumber& other) const {
    std::string& digitsRef = const_cast<std::string&>(digits);
    if (digitsRef == "-0"){
        digitsRef = "0";
    }

    std::string& otherdigitsRef = const_cast<std::string&>(other.digits);
    if (otherdigitsRef == "-0"){
        otherdigitsRef = "0";
    }

    bool isNegative1 = (digits[0] == '-');
    bool isNegative2 = (other.digits[0] == '-');


    if (isNegative1 != isNegative2){
        return isNegative2;
    }

    if (isNegative1) {
        LongNumber negated1 = *this;
        negated1.digits = digits.substr(1);
        LongNumber negated2 = other;
        negated2.digits = other.digits.substr(1);
        bool res = negated2 > negated1;
        return res;
    }

    std::pair<std::string, std::string> num1Parts = splitNumber(digits);
    std::pair<std::string, std::string> num2Parts = splitNumber(other.digits);

    int size1 = num1Parts.first.size(), size2 = num2Parts.first.size();
    if (size1 > size2) {
        return true;
    } else if (size1 < size2) {
        return false;
    } else {
        for (size_t i = 0; i < size1; ++i) {
            if (num1Parts.first[i] > num2Parts.first[i]) {
                return true;
            } else if (num1Parts.first[i] < num2Parts.first[i]) {
                return false;
            }
        }
    }

    size1 = num1Parts.second.size(), size2 = num2Parts.second.size();
    int size = std::min(size1, size2);

    for (size_t i = 0; i < size; ++i) {
        if (num1Parts.second[i] > num2Parts.second[i]) {
            return true;
        } else if (num1Parts.second[i] < num2Parts.second[i]) {
            return false;
        }
    }

    return size1 > size2;

}

bool LongNumber::operator==(const LongNumber& other) const {
    bool larger = (*this) > other ? true : false;
    if (larger) {
        return false;
    } else {
        return other > (*this) ? false : true;
    }
}

bool LongNumber::operator!=(const LongNumber& other) const {
    return !((*this) == other);
}

bool LongNumber::operator<(const LongNumber& other) const {
    return other > (*this);
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

// Операция сложения
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
    // Проверяем на отрицательные числа
    if (digits[0] == '-' && other.digits[0] != '-'){
        std::string str = digits.substr(1);
        LongNumber temp(str, precision);
        return other - temp;
    }

    if (other.digits[0] == '-' && digits[0] != '-'){
        std::string str = other.digits.substr(1);
        LongNumber temp(str, other.precision);
        return (*this) - temp;
    }

    bool minus = false;
    if (other.digits[0] == '-' && digits[0] == '-'){
        minus = true;
    }

    // Вычисляем точность для результата как максимальную из точностей операндов
    int resultPrecision = std::max(precision, other.precision);
    std::cout << resultPrecision << std::endl;
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
        if (minus){
            sum = "-" + result_1 + "." + result_2;
        } else {
            sum = result_1 + "." + result_2;
        }
    } else {
        if (minus){
            sum = "-" + result_1;
        } else {
            sum = result_1;
        }
    }

    // Создаем новый объект LongNumber с полученной суммой и точностью
    return LongNumber(sum, resultPrecision);
}
// Операция вычитания
std::vector<int> subtractDigits(const std::vector<int>& digits1, const std::vector<int>& digits2, char flag) {
    std::vector<int> diffDigits;
    int borrow = 0;
    
    for (int i = digits1.size() - 1; i >= 0; --i) {
        int diff = digits1[i] - digits2[i] - borrow;
        if (diff < 0) {
            diff += 10;
            borrow = 1;
        } else {
            borrow = 0;
        }
        diffDigits.insert(diffDigits.begin(), diff);
    }

    // Удаляем ведущие нули
    if (flag){
        while (!diffDigits.empty() && diffDigits.front() == 0) {
            diffDigits.erase(diffDigits.begin());
        }
    }

    return diffDigits;
}

bool allZeros(const std::vector<int>& vec) {
    for (int num : vec) {
        if (num != 0) {
            return false;
        }
    }
    return true;
}

LongNumber LongNumber::operator-(const LongNumber& other) const {
    // Вычисляем точность для результата как максимальную из точностей операндов
    int resultPrecision = std::max(precision, other.precision);
    // Разбиваем числа на целую и дробную части
    std::pair<std::string, std::string> num1Parts = splitNumber(digits);
    std::pair<std::string, std::string> num2Parts = splitNumber(other.digits);

    // Если числа имеют разный знак, выполняем операцию сложения
    if (digits[0] == '-' && other.digits[0] != '-'){
        std::string temp_str = digits.substr(1);
        LongNumber sum(temp_str, precision);
        LongNumber result = sum + other;
        result.digits = "-" + result.digits;
        return result;
    }

    if (digits[0] != '-' && other.digits[0] == '-'){
        std::string temp_str = other.digits.substr(1);
        LongNumber sum(temp_str, other.precision);
        LongNumber result = sum + (*this);
        return result;
    }

    // Переводим строки в векторы цифр
    std::vector<int> digits1 = convertToDigitsVector(num1Parts.first);
    std::vector<int> digits2 = convertToDigitsVector(num2Parts.first);

    // Если числа одного знака, определяем большее по модулю
    bool minus = false;

    bool num1IsBigger = false;
    if (digits[0] == '-'){
        std::string str1 = digits.substr(1);
        std::string str2 = other.digits.substr(1);
        LongNumber num1(str1, precision);
        LongNumber num2(str2, other.precision);
        num1IsBigger = num1 > num2;
        if (num1IsBigger){
            minus = true;
        }
    } else {
        num1IsBigger = (*this) > other;
        if (!num1IsBigger){
            minus = true;
        }
    }


    alignVectors_1(digits1, digits2);
    
    // Вычитание в зависимости от размера целой части
    std::vector<int> diffDigits;
    std::vector<int> diffDigitsFraction;

    if (num1IsBigger) {
        diffDigits = subtractDigits(digits1, digits2, 1);

        digits1 = convertToDigitsVector(num1Parts.second);
        digits2 = convertToDigitsVector(num2Parts.second);

        // Добавляем нули в конец векторов, чтобы выровнять их по длине
        alignVectors_2(digits1, digits2);
    
        int borrow = 0;
    
        for (int i = digits1.size() - 1; i >= 0; --i) {
            int diff = digits1[i] - digits2[i] - borrow;
            if (diff < 0) {
                diff += 10;
                borrow = 1;
            } else {
                borrow = 0;
            }
            diffDigitsFraction.insert(diffDigitsFraction.begin(), diff);
        }

        if (borrow > 0){
            std::vector OnesVector(1, 1);
            alignVectors_1(diffDigits, OnesVector);
            diffDigits = subtractDigits(diffDigits, OnesVector, 1);
        }

    } else {
        diffDigits = subtractDigits(digits2, digits1, 1);

        digits1 = convertToDigitsVector(num1Parts.second);
        digits2 = convertToDigitsVector(num2Parts.second);

        // Добавляем нули в конец векторов, чтобы выровнять их по длине
        alignVectors_2(digits1, digits2);

        int borrow = 0;
    
        for (int i = digits2.size() - 1; i >= 0; --i) {
            int diff = digits2[i] - digits1[i] - borrow;
            if (diff < 0) {
                diff += 10;
                borrow = 1;
            } else {
                borrow = 0;
            }
            diffDigitsFraction.insert(diffDigitsFraction.begin(), diff);
        }

        if (borrow > 0){
            std::vector OnesVector(1, 1);
            alignVectors_1(diffDigits, OnesVector);
            diffDigits = subtractDigits(diffDigits, OnesVector, 1);
        }

    }

    // Преобразуем результаты в строки
    std::string result_1;
    for (int digit : diffDigits) {
        result_1 += std::to_string(digit);
    }

    if (result_1.size() == 0){
        result_1 += "0";
    }

    std::string result_2;
    for (int digit : diffDigitsFraction){
        result_2 += std::to_string(digit);
    }

    // Меняем строку до заданной точности
    int len = result_2.length();
    if (resultPrecision > len){
        result_2 += std::string(resultPrecision - len, '0');
    } else {
        result_2 = result_2.substr(0, resultPrecision);
    }

    std::string diff;
    if (resultPrecision > 0){
        if (minus){
            diff = "-" + result_1 + "." + result_2;
        } else {
            diff = result_1 + "." + result_2;
        }
    } else {
        if (minus){
            diff = "-" + result_1;
        } else {
            diff = result_1;
        }
    }

    // Создаем новый объект LongNumber с полученной разностью
    return LongNumber(diff, resultPrecision);
}