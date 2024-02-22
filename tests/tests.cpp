#include "gtest/gtest.h"
#include "LongNumber.h"

TEST(BlockSum, Sum){
    LongNumber num1("4732478293294030.327748", 1);
    LongNumber num2("57390243.232434323", 9);

    std::cout << "Num1: " << num1.toString() << std::endl;
    std::cout << "Num2: " << num2.toString() << std::endl;
    
    std::cout << "Expect: 4732478350684273.560182323" << std::endl;
    LongNumber resSum = num1 + num2;

    EXPECT_TRUE(resSum.toString() == "4732478350684273.560182323");

    LongNumber num3("9999.9", 0);
    LongNumber num4("11.1", 0);

    std::cout << "Num3: " << num3.toString() << std::endl;
    std::cout << "Num4: " << num4.toString() << std::endl;

    std::cout << "Expect: 10011" << std::endl;
    LongNumber resSum1 = num3 + num4;

    EXPECT_TRUE(resSum1.toString() == "10011");
}

TEST(BlockSub, Sub){
    LongNumber num1("-3243.12", 5);
    LongNumber num2("123.3", 3);

    std::cout << "Num1: " << num1.toString() << std::endl;
    std::cout << "Num2: " << num2.toString() << std::endl;
    
    std::cout << "Expect: -3366.42000" << std::endl;
    LongNumber resSub = num1 - num2;

    EXPECT_TRUE(resSub.toString() == "-3366.42000");

    LongNumber num3("1.1", 0);
    LongNumber num4("0.3", 1);

    std::cout << "Num3: " << num3.toString() << std::endl;
    std::cout << "Num4: " << num4.toString() << std::endl;

    std::cout << "Expect: 0.8" << std::endl;
    LongNumber resSub1 = num3 - num4;

    EXPECT_TRUE(resSub1.toString() == "0.8");
}

TEST(BlockMul, Mul){
    LongNumber num1("-783438493.419", 10);
    LongNumber num2("4783.41030135", 0);

    std::cout << "Num1: " << num1.toString() << std::endl;
    std::cout << "Num2: " << num2.toString() << std::endl;

    std::cout << "Expect: -3747507759894.5687818155" << std::endl;
    LongNumber resMul = num1 * num2;

    EXPECT_TRUE(resMul.toString() == "-3747507759894.5687818155");

    LongNumber num3("-0", 3);
    LongNumber num4("0", 4);

    std::cout << "Num3: " << num3.toString() << std::endl;
    std::cout << "Num4: " << num4.toString() << std::endl;

    std::cout << "Expect: 0" << std::endl;
    LongNumber resMul1 = num3 * num4;

    EXPECT_TRUE(resMul1.toString() == "0");
}

TEST(BlockDiv, Div){
    LongNumber num1("22", 12);
    LongNumber num2("7", 0);

    std::cout << "Num1: " << num1.toString() << std::endl;
    std::cout << "Num2: " << num2.toString() << std::endl;

    std::cout << "Expect: 3.142857142857" << std::endl;
    LongNumber resDiv = num1 / num2;

    EXPECT_TRUE(resDiv.toString() == "3.142857142857");

    LongNumber num3("-100003204389348923.134", 3);
    LongNumber num4("12345", 4);

    std::cout << "Num3: " << num3.toString() << std::endl;
    std::cout << "Num4: " << num4.toString() << std::endl;

    std::cout << "Expect: -8100705094317.4502" << std::endl;
    LongNumber resDiv1 = num3 / num4;

    EXPECT_TRUE(resDiv1.toString() == "-8100705094317.4502");
}

TEST(BlockComp, Comp){
    LongNumber num1("0", 10);
    LongNumber num2("0.0000", 0);

    std::cout << "Num1: " << num1.toString() << std::endl;
    std::cout << "Num2: " << num2.toString() << std::endl;

    std::cout << "Expect: 0 == 0 => 1" << std::endl;
    bool eq = num1 == num2;

    EXPECT_TRUE(std::to_string(eq) == "1");

    LongNumber num3("1000000000000000000.2", 3);
    LongNumber num4("1000000000000000001.2", 4);

    std::cout << "Num3: " << num3.toString() << std::endl;
    std::cout << "Num4: " << num4.toString() << std::endl;

    std::cout << "Expect: 1000000000000000000.2 > 1000000000000000001.2 => 0" << std::endl;
    bool larger = num3 > num4;

    EXPECT_TRUE(std::to_string(larger) == "0");

    LongNumber num5("-1", 10);
    LongNumber num6("1", 0);

    std::cout << "Num5: " << num5.toString() << std::endl;
    std::cout << "Num6: " << num6.toString() << std::endl;

    std::cout << "Expect: -1 != 1 => 1" << std::endl;
    bool eq1 = num5 != num6;

    EXPECT_TRUE(std::to_string(eq1) == "1");

    LongNumber num7("-0", 10);
    LongNumber num8("-0", 0);

    std::cout << "Num7: " << num7.toString() << std::endl;
    std::cout << "Num8: " << num8.toString() << std::endl;

    std::cout << "Expect: -0 < -0 => 0" << std::endl;
    bool larger1 = num7 < num8;

    EXPECT_TRUE(std::to_string(larger1) == "0");
}

TEST(BlockPi, Pi){
    LongNumber Pi = LongNumber::pi(10);

    std::cout << "Pi: 3.1415926535";
    EXPECT_TRUE(Pi.toString() == "3.1415926535");
}