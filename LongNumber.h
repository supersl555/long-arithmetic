#include <iostream>
#include <string>
#include <sstream>
#include <cmath>

class LongNumber {
private:
    std::string digits;
    int precision;

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
    
    // Создание из литерала с плавающей точкой
    static LongNumber fromDouble(double number, int precision = 2);
    
    // Преобразование длинного числа в строку
    std::string toString() const;
    
    // Метод для установки точности
    void setPrecision(int precision);
    
    // Другие методы
};
