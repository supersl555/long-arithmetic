#include <iostream>
#include <string>
#include <sstream>
#include <cmath>

class LongNumber {
private:
    std::string digits;
    int precision;
    std::string division(std::string strA, std::string strB) const;
public:
    // Конструкторы
    LongNumber();
    LongNumber(const std::string& number, int precision = 2);
    LongNumber(double number, int precision = 2);
    
    // Операции базовой арифметики
    LongNumber operator+(const LongNumber& other) const;
    LongNumber operator-(const LongNumber& other) const;
    LongNumber operator*(const LongNumber& other) const;
    LongNumber operator/(const LongNumber& other) const;
    
    // Операции сравнения
    bool operator==(const LongNumber& other) const;
    bool operator!=(const LongNumber& other) const;
    bool operator<(const LongNumber& other) const;
    bool operator>(const LongNumber& other) const;
    
    // Вычисление числа пи
    static LongNumber pi(int precision);
    
    // Преобразование длинного числа в строку
    std::string toString() const;
    
    // Метод для установки точности
    void setPrecision(int precision);
    
};
