#include "gtest/gtest.h"
#include "LongNumber.h"

TEST(BlockSum, Sum1){
    LongNumber num1("321", 5);
    LongNumber num2("123", 3);

    std::cout << "Num1: " << num1.toString() << std::endl;
    std::cout << "Num2: " << num2.toString() << std::endl;
    
    LongNumber resSum = num1 + num2;

    EXPECT_TRUE(resSum.toString() == "444.00000");
}