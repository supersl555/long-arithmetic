#include "LongNumber.h"
#include <iomanip>
#include <vector>
#include <algorithm>
#include <regex>

LongNumber operator ""_ln(const char *str, size_t size);

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
    // Выравниваем дробные части
    if (size1 > size2){
        for (int i = 0; i < size1 - size2; ++i){
            num2Parts.second += "0";
        }
    } else if (size1 < size2){
        for (int i = 0; i < size2 - size1; ++i){
            num1Parts.second += "0";
        }
    }

    int size = num1Parts.second.size();

    for (size_t i = 0; i < size; ++i) {
        if (num1Parts.second[i] > num2Parts.second[i]) {
            return true;
        } else if (num1Parts.second[i] < num2Parts.second[i]) {
            return false;
        }
    }

    return false;

}

bool LongNumber::operator==(const LongNumber& other) const {
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
        return false;
    }

    std::pair<std::string, std::string> num1Parts = splitNumber(digits);
    std::pair<std::string, std::string> num2Parts = splitNumber(other.digits);

    int size1 = num1Parts.first.size(), size2 = num2Parts.first.size();
    if (size1 > size2) {
        return false;
    } else if (size1 < size2) {
        return false;
    } else {
        for (size_t i = 0; i < size1; ++i) {
            if (num1Parts.first[i] > num2Parts.first[i]) {
                return false;
            } else if (num1Parts.first[i] < num2Parts.first[i]) {
                return false;
            }
        }
    }

    size1 = num1Parts.second.size(), size2 = num2Parts.second.size();
    // Выравниваем дробные части
    if (size1 > size2){
        for (int i = 0; i < size1 - size2; ++i){
            num2Parts.second += "0";
        }
    } else if (size1 < size2){
        for (int i = 0; i < size2 - size1; ++i){
            num1Parts.second += "0";
        }
    }

    int size = num1Parts.second.size();

    for (size_t i = 0; i < size; ++i) {
        if (num1Parts.second[i] > num2Parts.second[i]) {
            return false;
        } else if (num1Parts.second[i] < num2Parts.second[i]) {
            return false;
        }
    }

    return true;
}

bool LongNumber::operator!=(const LongNumber& other) const {
    return !((*this) == other);
}

bool LongNumber::operator<(const LongNumber& other) const {
    return other > (*this);
}

std::vector<char> convertToDigitsVector(const std::string& numberString) {
    std::vector<char> digits;
    for (char digitChar : numberString) {
        if (isdigit(digitChar)) {
            digits.push_back(digitChar - '0');
        }
    }
    return digits;
}

void alignVectorsBegin(std::vector<char>& vec1, std::vector<char>& vec2) {
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

void alignVectorsEnd(std::vector<char>& vec1, std::vector<char>& vec2) {
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
    // Разбиваем числа на целую и дробную части
    std::pair<std::string, std::string> num1Parts = splitNumber(digits);
    std::pair<std::string, std::string> num2Parts = splitNumber(other.digits);


    // Складываем дробные части с учетом точности
    // Преобразуем строки в векторы цифр
    std::string result_2;
    std::vector<char> digits1 = convertToDigitsVector(num1Parts.second);
    std::vector<char> digits2 = convertToDigitsVector(num2Parts.second);

    // Добавляем нули в конец векторов, чтобы выровнять их по длине
    alignVectorsEnd(digits1, digits2);

    // Выполняем сложение
    int carry = 0;
    for (int i = digits1.size() - 1; i >= 0; --i) {
        int sum = digits1[i] + digits2[i] + carry;
        result_2.insert(result_2.begin(), sum % 10 + '0');
        carry = sum / 10;
    }

    // Сложение целой части 
    // Переводим строки в векторы цифр
    digits1 = convertToDigitsVector(num1Parts.first);
    digits2 = convertToDigitsVector(num2Parts.first);
    
    // Выравниваем векторы по длине
    alignVectorsBegin(digits1, digits2);

    // Складываем целые части
    std::vector<char> sumDigits;
    
    for (int i = digits1.size() - 1; i >= 0; --i) {
        int sum = digits1[i] + digits2[i] + carry;
        sumDigits.insert(sumDigits.begin(), sum % 10);
        carry = sum / 10;
    }
    
    if (carry > 0) {
        sumDigits.insert(sumDigits.begin(), carry);
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
            minus = num2 > num1 ? false : true; 
        }
    } else {
        num1IsBigger = (*this) > other;
        if (!num1IsBigger){
            minus = other > (*this) ? true : false; 
        }
    }

    // Переводим строки в векторы цифр
    std::vector<char> digits1 = convertToDigitsVector(num1Parts.second);
    std::vector<char> digits2 = convertToDigitsVector(num2Parts.second);


    alignVectorsEnd(digits1, digits2);
    
    // Вычитание в зависимости от размера целой части
    std::vector<char> diffDigits;
    std::vector<char> diffDigitsFraction;

    if (num1IsBigger) {
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

        digits1 = convertToDigitsVector(num1Parts.first);
        digits2 = convertToDigitsVector(num2Parts.first);

        // Добавляем нули в конец векторов, чтобы выровнять их по длине
        alignVectorsBegin(digits1, digits2);
    
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
        while (!diffDigits.empty() && diffDigits.front() == 0) {
            diffDigits.erase(diffDigits.begin());
        }
    } else {
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

        digits1 = convertToDigitsVector(num1Parts.first);
        digits2 = convertToDigitsVector(num2Parts.first);

        // Добавляем нули в конец векторов, чтобы выровнять их по длине
        alignVectorsBegin(digits1, digits2);
    
        for (int i = digits2.size() - 1; i >= 0; --i) {
            int diff = digits2[i] - digits1[i] - borrow;
            if (diff < 0) {
                diff += 10;
                borrow = 1;
            } else {
                borrow = 0;
            }
            diffDigits.insert(diffDigits.begin(), diff);
        }

        // Удаляем ведущие нули
        while (!diffDigits.empty() && diffDigits.front() == 0) {
            diffDigits.erase(diffDigits.begin());
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

int countCharactersAfterDot(const std::string& str) {
    size_t dotPosition = str.find('.');
    if (dotPosition != std::string::npos) {
        return str.size() - dotPosition - 1;
    }
    return 0;
}

std::string deletePointer(std::string inStr){
    std::string outStr;
    for (char c : inStr){
        if (isdigit(c)){
            outStr += c;
        }
    }
    return outStr;
}

std::string findSum(std::string str1, std::string str2) {

    if (str1.length() > str2.length()){
        swap(str1, str2);
    }
    std::string str = "";

    int n1 = str1.length();
    int n2 = str2.length();

    reverse(str1.begin(), str1.end());
    reverse(str2.begin(), str2.end());
 
    int carry = 0;
    for (int i = 0; i < n1; i++) {
 
        int sum
            = ((str1[i] - '0')
               + (str2[i] - '0')
               + carry);
        str.push_back(sum % 10 + '0');

        carry = sum / 10;
    }

    for (int i = n1; i < n2; i++) {
        int sum = ((str2[i] - '0') + carry);
        str.push_back(sum % 10 + '0');
        carry = sum / 10;
    }

    if (carry)
        str.push_back(carry + '0');

    reverse(str.begin(), str.end());
 
    return str;
}

std::string findDiff(std::string str1, std::string str2){

    std::string str = "";

    int n1 = str1.length(), n2 = str2.length();

    reverse(str1.begin(), str1.end());
    reverse(str2.begin(), str2.end());
 
    int carry = 0;
 
    for (int i = 0; i < n2; i++) {
 
        int sub = ((str1[i] - '0') - (str2[i] - '0')- carry);

        if (sub < 0) {
            sub = sub + 10;
            carry = 1;
        }
        else
            carry = 0;
 
        str.push_back(sub + '0');
    }

    for (int i = n2; i < n1; i++) {
        int sub = ((str1[i] - '0') - carry);

        if (sub < 0) {
            sub = sub + 10;
            carry = 1;
        }
        else
            carry = 0;
 
        str.push_back(sub + '0');
    }

    reverse(str.begin(), str.end());

    return str;
}

std::string removeLeadingZeros(std::string str){
    const std::regex pattern("^0+(?!$)");

    str = std::regex_replace(str, pattern, "");
    return str;
}

std::string Karatsuba(std::string A, std::string B){
    if (A.length() > B.length()){
        swap(A, B);
    }
    int n1 = A.length(), n2 = B.length();
    while (n2 > n1) {
        A = "0" + A;
        n1++;
    }

    if (n1 == 1) {
        int ans = stoi(A) * stoi(B);
        return std::to_string(ans);
    }

    if (n1 % 2 == 1) {
        n1++;
        A = "0" + A;
        B = "0" + B;
    }
 
    std::string Al, Ar, Bl, Br;

    for (int i = 0; i < n1 / 2; ++i) {
        Al += A[i];
        Bl += B[i];
        Ar += A[n1 / 2 + i];
        Br += B[n1 / 2 + i];
    }
 
    std::string p = Karatsuba(Al, Bl);
 
    std::string q = Karatsuba(Ar, Br);
 
    std::string r = findDiff(Karatsuba(findSum(Al, Ar),findSum(Bl, Br)),findSum(p, q));

    for (int i = 0; i < n1; ++i){
        p = p + "0";
    }
    for (int i = 0; i < n1 / 2; ++i){
        r = r + "0";
    }
    std::string ans = findSum(p, findSum(q, r));
 
    ans = removeLeadingZeros(ans);
 
    return ans;
}

std::string insertDot(std::string str, int n) {
    int pos = str.length() - n;
    if (pos > 0) {
        str.insert(pos, ".");
    }
    return str;
}

LongNumber LongNumber::operator*(const LongNumber& other) const {
    if ((*this) == 0 || other == 0){
        return LongNumber("0", 0); 
    }
    // Определяем знак числа
    bool minus = false;
    if (digits[0] == '-' || other.digits[0] == '-'){
        minus = (digits[0] == '-' && other.digits[0] == '-') ? false : true;
    }

    // Считаем кол-во цифр в дробной части
    int charactersAfterFirst = countCharactersAfterDot(digits);
    int charactersAfterSecond = countCharactersAfterDot(other.digits);
    int charactersAfterMultiply = charactersAfterFirst + charactersAfterSecond;

    // Вычисляем точность для результата как максимальную из точностей операндов
    int resultPrecision = std::max(precision, other.precision);
    // Убираем точку из представления числа
    std::string firstNum = deletePointer(digits);
    std::string secondNum = deletePointer(other.digits);

    std::string result = Karatsuba(firstNum, secondNum);
     

    int len = result.length();
    if (len > charactersAfterMultiply){
        if (charactersAfterMultiply > 0){
            result = insertDot(result, charactersAfterMultiply);
            if (resultPrecision < charactersAfterMultiply){
                int n = charactersAfterMultiply - resultPrecision;
                result.erase(len - n, n);
            } else if (resultPrecision > charactersAfterMultiply){
                int n = resultPrecision - charactersAfterMultiply;
                for (int i = 0; i < n; ++i) {
                    result += '0';
                }
            }
        } else {
            if (resultPrecision > 0){
                result += '.';
                for (int i = 0; i < resultPrecision; ++i) {
                    result += '0';
                }
            }
        }
    } else {
        for (int i = 0; i < charactersAfterMultiply - len; ++i){
            result = '0' + result;
        }
        int new_len = result.length();
        if (resultPrecision > new_len){
            for (int i = 0; i < resultPrecision - new_len; ++i){
                result += '0';
            }
        } else if (resultPrecision < new_len){
            result.erase(resultPrecision, new_len - resultPrecision);
        }

        if (resultPrecision != 0){
            result = '.' + result;
            result = '0' + result;
        } else {
            result = '0' + result;
        }
    }

    if (minus){
        result = '-' + result;
    }

    return LongNumber(result, resultPrecision);
}

LongNumber operator ""_ln(const char *str, size_t size){
    return LongNumber(str, countCharactersAfterDot(str));
}

std::string LongNumber::division(std::string strA, std::string strB) const{
    if(strB == "0")
        throw("Arithmetic Error: Division By 0");
    if(LongNumber(strA, 0) < LongNumber(strB, 0))
        return "0";
    if(LongNumber(strA, 0) == LongNumber(strB, 0)){
        return "1";
    }
    std::reverse(strA.begin(), strA.end());
    
    LongNumber a(strA, 0);
    LongNumber b(strB, 0);

    int i, lgcat = 0, cc;
    int n = strA.length(), m = strB.length();
    std::vector<int> cat(n, 0);
    LongNumber t("0", 0);
    LongNumber ten("10", 0);
    for (i = n - 1; t * ten + LongNumber(std::string(1, a.digits[i]), 0) < b; i--){
        t = t * ten;
        t = t + LongNumber(std::string(1, a.digits[i]), 0);
    }

    for (; i >= 0; i--){
        t = t * ten + LongNumber(std::string(1, a.digits[i]), 0);
        for (cc = 9; LongNumber(cc, 0) * b > t; cc--);
        t = t - LongNumber(cc, 0) * b;
        cat[lgcat++] = cc;
    }

    std::string resultStr;
    for (int i = 0; i < lgcat; i++) {
        resultStr += std::to_string(cat[i]);
    }

    return resultStr;
}


// Функция для подготовки числа к делению
std::pair<std::string, std::string> prepareNumbers(std::string num1, int precision1, std::string num2, int precision2) {
    std::string preparedNum1 = deletePointer(num1);
    std::string preparedNum2 = deletePointer(num2);
    preparedNum1 = removeLeadingZeros(preparedNum1);
    preparedNum2 = removeLeadingZeros(preparedNum2);

    if (precision1 > precision2){
        for (int i = 0; precision1 - precision2 > i; ++i){
            preparedNum2 += "0";
        }
    } else {
        for (int i = 0; precision2 - precision1 > i; ++i){
            preparedNum1 += "0";
        }
    }
    return std::make_pair(preparedNum1, preparedNum2);
}

LongNumber LongNumber::operator/(const LongNumber& other) const{
    // Определяем знак числа
    bool minus = false;
    if (digits[0] == '-' || other.digits[0] == '-'){
        minus = (digits[0] == '-' && other.digits[0] == '-') ? false : true;
    }

    // Считаем кол-во цифр в дробной части
    int charactersAfterFirst = countCharactersAfterDot(digits);
    int charactersAfterSecond = countCharactersAfterDot(other.digits);
    int charactersAfterMultiply = charactersAfterFirst + charactersAfterSecond;

    // Вычисляем точность для результата как максимальную из точностей операндов
    int resultPrecision = std::max(precision, other.precision);
    // Готовим числа к делению
    std::pair<std::string, std::string> Num = 
    prepareNumbers(digits, charactersAfterFirst, other.digits, charactersAfterSecond);

    std::string intDiv = division(Num.first, Num.second);
    std::string fracDiv;
    
    LongNumber multiplyResSecond = LongNumber(intDiv, 0) * LongNumber(Num.second, 0);
    if (multiplyResSecond == LongNumber(Num.first)){
        return LongNumber(intDiv, 0);
    } else {
        if (resultPrecision > 0){
            std::string remainder = (LongNumber(Num.first, 0) - multiplyResSecond).toString() + "0";
            for (int i = 0; i < resultPrecision; ++i){
                std::string remainderDiv = division(remainder, Num.second);
                fracDiv += remainderDiv;
                remainder = (LongNumber(remainder, 0) - LongNumber(remainderDiv, 0) 
                * LongNumber(Num.second, 0)).toString() + "0";
            }
        }
    }

    if (fracDiv.size() > 0){
        if (minus){
            return LongNumber("-" + intDiv + "." + fracDiv, resultPrecision);
        } else {
            return LongNumber(intDiv + "." + fracDiv, resultPrecision);
        }
    } else {
        if (minus) {
            return LongNumber("-" + intDiv, resultPrecision);
        } else {
            return LongNumber(intDiv, resultPrecision);
        }
    }
}

// формула Бэйли — Боруэйна — Плаффа
LongNumber LongNumber::pi(int precision){
    LongNumber result("0", precision + 2);
    if (precision > 0){
        for (int k = 0; k < precision; ++k){
            LongNumber k_8 = LongNumber(std::to_string(k), precision + 2) * LongNumber("8", precision + 2);

            LongNumber fraction1 = LongNumber("-2", precision + 2) / (k_8 + LongNumber("4", precision + 2));
            LongNumber fraction2 = LongNumber("-1", precision + 2) / (k_8 + LongNumber("5", precision + 2));
            LongNumber fraction3 = LongNumber("-1", precision + 2) / (k_8 + LongNumber("6", precision + 2));
            LongNumber fraction4 = LongNumber("4", precision + 2) / (k_8 + LongNumber("1", precision + 2));

            LongNumber k_16;
            if (k == 0){
                k_16 = LongNumber("1", precision + 2); 
            } else {
                k_16 = LongNumber("16", precision + 2);
            }

            for (int i = 1; i < k; ++i){
                k_16 = k_16 * LongNumber("16", precision + 2);
            }

            LongNumber numerator = fraction1 + fraction2 + fraction3 + fraction4;
            
            result = result + numerator / k_16;
        }
        result.digits = result.digits.substr(0, result.digits.size() - 2);
        return result;
    } else {
        return "3"_ln;
    }
}