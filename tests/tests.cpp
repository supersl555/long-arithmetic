#include "gtest/gtest.h"
#include "LongNumber.h"

TEST(BlockSum, Sum1){
    LongNumber num1("321.32", 5);
    LongNumber num2("123.91", 3);

    std::cout << "Num1: " << num1.toString() << std::endl;
    std::cout << "Num2: " << num2.toString() << std::endl;
    
    std::cout << "Expect: 445.23000" << std::endl;
    LongNumber resSum = num1 + num2;

    EXPECT_TRUE(resSum.toString() == "445.23000");
}

TEST(BlockMul, Mul1){
    LongNumber num1("-3243.12", 5);
    LongNumber num2("123.3", 3);

    std::cout << "Num1: " << num1.toString() << std::endl;
    std::cout << "Num2: " << num2.toString() << std::endl;
    
    std::cout << "Expect: -399876.69600" << std::endl;
    LongNumber resMul = num1 * num2;

    EXPECT_TRUE(resMul.toString() == "-399876.69600");
}