// tests.cpp
#include <iostream>
#include "LongNumber.h" 

int main() {
    // Тесты сложения
    LongNumber number1("9999.94384", 7);
    LongNumber number2("-1.91", 2);

    LongNumber sum = number1 + number2;

    std::cout << "Sum: " << sum.toString() << std::endl;

    LongNumber number3("---0.1", 3);
    LongNumber number4("-0.8", 3);

    LongNumber sum2 = number3 + number4;

    std::cout << "Sum: " << sum2.toString() << std::endl;

    LongNumber number5("3.141592653589793238462643", 3);
    LongNumber number6("2.718281828", 9);

    LongNumber sum3 = number5 + number6;

    std::cout << "Sum: " << sum3.toString() << std::endl;

    // Тесты вычитания
    LongNumber number7("123.12", 2);
    LongNumber number8("123.12", 2);

    LongNumber difference = number7 - number8;

    std::cout << "Diff: " << difference.toString() << std::endl;
    
    // Тесты сравнений
    bool islarger_1 = number7 > number8;
    bool islarger_2 = number7 < number8;

    std::cout << "Larger: " << islarger_1 << std::endl;
    std::cout << "Larger: " << islarger_2 << std::endl;

    LongNumber number9("123.1", 3);
    LongNumber number10("123.1", 3);

    bool equality_1 = number10 == number9;
    bool equality_2 = number10 != number9;

    std::cout << "Equality: " << equality_1 << std::endl;
    std::cout << "Equality: " << equality_2 << std::endl;
    return 0;
}