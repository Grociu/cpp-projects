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
THESE TESTS CHECK THE RESULTS OF THE FRACTION OPERATORS
***********************************************************************/
/***********************************************************************
EQUAL/NOT EQUAL OPERATORS
***********************************************************************/

// test for equality true
TEST(FractionEqualityOperatorTests, EqualIsTrue)
{
    const int test_cases_size = 6;
    double test_cases[][4] =
    {
        {1, 2, 1, 2},  // numerator1, denominator1, denominator2, denominator2
        {-5, -5, 1, 1},
        {4, 8, 1, 2},  // simplified before comparison?
        {1.5, 1, 12, 8},
        {3, -7, -9, 21},
        {0.25, 1, 1, 4} //size 6
    };
    for(int i = 0; i < test_cases_size; i++)
    {
        Fraction test_fraction_1 = Fraction(test_cases[i][0], test_cases[i][1]);
        Fraction test_fraction_2 = Fraction(test_cases[i][2], test_cases[i][3]);
        EXPECT_TRUE(test_fraction_1 == test_fraction_2) << "Equality test of index "
        << i << " should be TRUE\nRaw data: " << test_cases[i][0] << " "
        << test_cases[i][1] << " " << test_cases[i][2] << " " << test_cases[i][3]
        << std::endl;
    }
}

// tests for equality false
TEST(FractionEqualityOperatorTests, EqualIsFalse)
{
    const int test_cases_size = 5;
    double test_cases[][4] =
    {
        {1, 2, 1, 7},  // numerator1, denominator1, denominator2, denominator2
        {-5, -5, -1, 1},
        {1.5, 1, 1, 8},
        {3, -7, 9, 21},
        {0.25, 1, 1, 40} //size 5
    };
    for(int i = 0; i < test_cases_size; i++)
    {
        Fraction test_fraction_1 = Fraction(test_cases[i][0], test_cases[i][1]);
        Fraction test_fraction_2 = Fraction(test_cases[i][2], test_cases[i][3]);
        EXPECT_FALSE(test_fraction_1 == test_fraction_2) << "Equality test of index "
        << i << " should be FALSE\nRaw data: " << test_cases[i][0] << " "
        << test_cases[i][1] << " " << test_cases[i][2] << " " << test_cases[i][3]
        << std::endl;
    }
}

// tests for not-equal true
TEST(FractionEqualityOperatorTests, NotEqualIsTrue)
{
    const int test_cases_size = 5;
    double test_cases[][4] =
    {
        {1, 2, 1, 7},  // numerator1, denominator1, denominator2, denominator2
        {-5, -5, -1, 1},
        {1.5, 1, 1, 8},
        {3, -7, 9, 21},
        {0.25, 1, 1, 40} //size 5
    };
    for(int i = 0; i < test_cases_size; i++)
    {
        Fraction test_fraction_1 = Fraction(test_cases[i][0], test_cases[i][1]);
        Fraction test_fraction_2 = Fraction(test_cases[i][2], test_cases[i][3]);
        EXPECT_TRUE(test_fraction_1 != test_fraction_2) << "Noe-equal test of index "
        << i << " should be TRUE\nRaw data: " << test_cases[i][0] << " "
        << test_cases[i][1] << " " << test_cases[i][2] << " " << test_cases[i][3]
        << std::endl;
    }
}

// tests for not-equal false
TEST(FractionEqualityOperatorTests, NotEqualIsFalse)
{
    const int test_cases_size = 6;
    double test_cases[][4] =
    {
        {1, 2, 1, 2},  // numerator1, denominator1, denominator2, denominator2
        {4, 8, 1, 2},  // simplified before comparison?
        {-5, -5, 1, 1},
        {1.5, 1, 12, 8},
        {3, -7, -9, 21},
        {0.25, 1, 1, 4} //size 5
    };
    for(int i = 0; i < test_cases_size; i++)
    {
        Fraction test_fraction_1 = Fraction(test_cases[i][0], test_cases[i][1]);
        Fraction test_fraction_2 = Fraction(test_cases[i][2], test_cases[i][3]);
        EXPECT_FALSE(test_fraction_1 != test_fraction_2) << "Not-equal test of index "
        << i << " should be FALSE\nRaw data: " << test_cases[i][0] << " "
        << test_cases[i][1] << " " << test_cases[i][2] << " " << test_cases[i][3]
        << std::endl;
    }
}

/***********************************************************************
INEQUALITY OPERATORS
***********************************************************************/

TEST(FractionCompareTests, HalfIsLargerThanQuarter)
{
    Fraction test_fraction_1 = Fraction(1, 2);
    Fraction test_fraction_2 = Fraction(1, 4);
    EXPECT_TRUE(test_fraction_1 > test_fraction_2);
}

TEST(FractionCompareTests, HalfIsLargerThanMinusQuarter)
{
    Fraction test_fraction_1 = Fraction(1, 2);
    Fraction test_fraction_2 = Fraction(-1, 4);
    EXPECT_TRUE(test_fraction_1 > test_fraction_2);
}

TEST(FractionCompareTests, NegativeFractionisLargerThanAnother)
{
    Fraction test_fraction_1 = Fraction(-1, 4);
    Fraction test_fraction_2 = Fraction(-1, 2);
    EXPECT_TRUE(test_fraction_1 > test_fraction_2);
}

TEST(FractionCompareTests, EighthIsLargerThanZero)
{
    Fraction test_fraction_1 = Fraction(1, 8);
    Fraction test_fraction_2 = Fraction(0);
    EXPECT_TRUE(test_fraction_1 > test_fraction_2);
}

TEST(FractionCompareTests, ZeroIsLargerThanMinusQuarter)
{
    Fraction test_fraction_1 = Fraction(0);
    Fraction test_fraction_2 = Fraction(-1, 8);
    EXPECT_TRUE(test_fraction_1 > test_fraction_2);
}

TEST(FractionCompareTests, DecimalFractionIsLargerThanAnother)
{
    Fraction test_fraction_1 = Fraction(0.57);
    Fraction test_fraction_2 = Fraction(0.372);
    EXPECT_TRUE(test_fraction_1 > test_fraction_2);
}

TEST(FractionCompareTests, NegativeDecimalFractionIsLargerThanAnother)
{
    Fraction test_fraction_1 = Fraction(-0.372);
    Fraction test_fraction_2 = Fraction(-0.57);
    EXPECT_TRUE(test_fraction_1 > test_fraction_2);
}

/***********************************************************************
DERIVED INEQUALITY OPERATORS
***********************************************************************/

TEST(FractionCompareTests, HalfIsLargerOrEqualThanQuarter)
{
    Fraction test_fraction_1 = Fraction(1, 2);
    Fraction test_fraction_2 = Fraction(1, 4);
    EXPECT_TRUE(test_fraction_1 >= test_fraction_2);
}

TEST(FractionCompareTests, QuarterIsSmallerThanHalf)
{
    Fraction test_fraction_1 = Fraction(1, 4);
    Fraction test_fraction_2 = Fraction(1, 2);
    EXPECT_TRUE(test_fraction_1 < test_fraction_2);
}

TEST(FractionCompareTests, QuarterIsSmallerOrEqualThanHalf)
{
    Fraction test_fraction_1 = Fraction(1, 4);
    Fraction test_fraction_2 = Fraction(1, 2);
    EXPECT_TRUE(test_fraction_1 <= test_fraction_2);
}

TEST(FractionCompareTests, EqualsAreLargerOrEqual)
{
    Fraction test_fraction_1 = Fraction(1, 4);
    Fraction test_fraction_2 = Fraction(1, 4);
    EXPECT_TRUE(test_fraction_1 >= test_fraction_2);
}

TEST(FractionCompareTests, EqualsAreSmallerOrEqual)
{
    Fraction test_fraction_1 = Fraction(1, 4);
    Fraction test_fraction_2 = Fraction(1, 4);
    EXPECT_TRUE(test_fraction_1 <= test_fraction_2);
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