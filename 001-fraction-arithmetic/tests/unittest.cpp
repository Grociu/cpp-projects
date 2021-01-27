#include "../classes/fraction.h"
#include "gtest/gtest.h"

/***********************************************************************
THESE TESTS CHECK IF THE COMPANION FUNCTIONS WORK CORRECTLY
***********************************************************************/

/***********************************************************************
Greatest Common Divisor
***********************************************************************/

TEST(GCDTests, GCDFunctionTestForOnes)
{
    EXPECT_EQ(greatest_common_divisor(1, 1), 1);
}

TEST(GCDTests, GCDFunctionTestForZero)
{
    EXPECT_EQ(greatest_common_divisor(0, 1), 1);
}

TEST(GCDTests, GCDFunctionTestForZero2)
{
    EXPECT_EQ(greatest_common_divisor(1, 0), 1);
}

TEST(GCDTests, GCDFunctionTestPrimes)
{
    EXPECT_EQ(greatest_common_divisor(3, 5), 1);
}

TEST(GCDTests, GCDFunctionTestOneDivisor)
{
    EXPECT_EQ(greatest_common_divisor(6, 9), 3);
}

TEST(GCDTests, GCDFunctionTestTwoSameDivisors)
{
    EXPECT_EQ(greatest_common_divisor(4, 8), 4);
}

TEST(GCDTests, GCDFunctionTestTwoDifferentDivisors)
{
    EXPECT_EQ(greatest_common_divisor(40, 70), 10);
}

TEST(GCDTests, GCDFunctionTestIrregularFraction)
{
    EXPECT_EQ(greatest_common_divisor(5000, 65), 5);
}

TEST(GCDTests, GCDFunctionTestLongAlgorithm)
{
    EXPECT_EQ(greatest_common_divisor(1701, 3768), 3);
}

/***********************************************************************
THESE TESTS CHECK IF THE FRACTIONS ARE CREATED CORRECTLY
***********************************************************************/

TEST(FractionCreationTests, FractionCreatedFromTwoArguments)
{
    Fraction test_fraction = Fraction(1, 2);
    EXPECT_EQ(test_fraction.numerator, 1);
    EXPECT_EQ(test_fraction.denominator, 2);
}

TEST(FractionCreationTests, FractionCreatedFromOneArgument)
{
    Fraction test_fraction = Fraction(1);
    EXPECT_EQ(test_fraction.numerator, 1);
    EXPECT_EQ(test_fraction.denominator, 1);
}

TEST(FractionCreationTests, FractionCreatedFromNoArguments)
{
    Fraction test_fraction = Fraction();
    EXPECT_EQ(test_fraction.numerator, 0);
    EXPECT_EQ(test_fraction.denominator, 1);
}

TEST(FractionCreationTests, FractionCreatedFromANegativeArgumentInFirst)
{
    Fraction test_fraction = Fraction(-5, 2);
    EXPECT_EQ(test_fraction.numerator, -5);
    EXPECT_EQ(test_fraction.denominator, 2);
}

TEST(FractionCreationTests, FractionCreatedFromANegativeArgumentInSecond)
{
    Fraction test_fraction = Fraction(5, -2);
    EXPECT_EQ(test_fraction.numerator, -5);
    EXPECT_EQ(test_fraction.denominator, 2);
}

TEST(FractionCreationTests, FractionCreatedFromTwoNegativeArguments)
{
    Fraction test_fraction = Fraction(-5, -2);
    EXPECT_EQ(test_fraction.numerator, 5);
    EXPECT_EQ(test_fraction.denominator, 2);
}

// Are the fractions simplified?
TEST(FractionCreationTests, FractionCreatedisSimplifiedByConstructor)
{
    Fraction test_fraction = Fraction(8, 10);
    EXPECT_EQ(test_fraction.numerator, 4);
    EXPECT_EQ(test_fraction.denominator, 5);
}

// This tests an input of a decimal double as sole argument
TEST(FractionCreationTests, FractionCreatedFromDecimalArguments)
{
    Fraction test_fraction = Fraction(1.37);
    EXPECT_EQ(test_fraction.numerator, 137);
    EXPECT_EQ(test_fraction.denominator, 100);
}

// This tests an input of two decimal doubles as arguments
// The resulting fraction should be shortened
TEST(FractionCreationTests, FractionCreatedFromDecimalArgumentsisSimplified)
{
    Fraction test_fraction = Fraction(1.2, 12.5);
    EXPECT_EQ(test_fraction.numerator, 12);
    EXPECT_EQ(test_fraction.denominator, 125);
}

// This test creates a set  of decimal fractions to test the precision of the 
// Fraction making algorithm for decimal numbers.
TEST(FractionCreationTests, PrecisionTestingForFractionCreation)
{
    const int test_cases_size = 26;
    double test_cases[][3] =
    {
        {0, 0, 1},  // double, numerator, denominator
        {-54342, -54342, 1},
        {1.1, 11, 10},
        {1.8, 9, 5},
        {-1.7, -17, 10},
        {-1.8, -9, 5},
        {2.79, 279, 100},
        {2.12, 53, 25},
        {-2.88, -72, 25},
        {-2.95, -59, 20},
        {3.123, 3123, 1000},
        {3.998, 1999, 500},
        {-3.124, -781, 250},
        {-3.003, -3003, 1000},
        {4.0001, 40001, 10000},
        {4.9983, 49983, 10000},
        {-4.1255, -8251, 2000},
        {-4.5555, -9111, 2000},
        {5.00342, 250171, 50000},
        {5.55559, 555559, 100000},
        {-5.00032, -15626, 3125},
        {-5.99925, -23997, 4000},
        {6.123453, 6123453, 1000000},
        {6.250252, 1562563, 250000},
        {-6.666666, -3333333, 500000},
        {-6.969696, -217803, 31250} //size 26
    };
    for(int i = 0; i < test_cases_size; i++)
    {
        Fraction test_fraction = Fraction(test_cases[i][0]);
        EXPECT_EQ(test_fraction.numerator, test_cases[i][1]) << "Unprecise conversion of " << test_cases[i][0] << std::endl;
        EXPECT_EQ(test_fraction.denominator, test_cases[i][2]) << "Unprecise conversion of " << test_cases[i][0] << std::endl;
    }
}

/***********************************************************************
***********************************************************************/

// main function for a Google Test CMake implementation
int main(int argc, char **argv) 
{
    printf("Running main() from %s\n", __FILE__);
    testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}