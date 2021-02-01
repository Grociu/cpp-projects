#include "../classes/fraction.h"
#include "../classes/dividebyzero.h"
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
TEST(FractionCreationTests, DenominatorCannotBeZero) // Zero cannot be a denominator
{
    Fraction test_fraction;
    EXPECT_THROW(test_fraction = Fraction(7, 0), DivideByZeroError);
}

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
    const int test_cases_size = 27;
    double test_cases[][3] =
    {
        {0, 0, 1},  // double, numerator, denominator
        {-54342, -54342, 1},
        {1.1, 11, 10},
        {1.5, 3, 2},
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
        {-6.969696, -217803, 31250} //size 27
    };
    for(int i = 0; i < test_cases_size; i++)
    {
        Fraction test_fraction = Fraction(test_cases[i][0]);
        EXPECT_EQ(test_fraction.numerator, test_cases[i][1]) << "Unprecise conversion of " << test_cases[i][0] << std::endl;
        EXPECT_EQ(test_fraction.denominator, test_cases[i][2]) << "Unprecise conversion of " << test_cases[i][0] << std::endl;
    }
}

/***********************************************************************
SIMPLIFY() METHOD TESTS
***********************************************************************/

TEST(SimplifyFunctionTests, SimpleFractionSimplifiesToSelf)
{
    Fraction test_fraction;
    test_fraction.numerator = 7;
    test_fraction.denominator = 12;
    test_fraction.simplify();
    EXPECT_EQ(test_fraction.numerator, 7);
    EXPECT_EQ(test_fraction.denominator, 12);
}

TEST(SimplifyFunctionTests, SimplifyIrregularFraction)
{
    Fraction test_fraction;
    test_fraction.numerator = 120;
    test_fraction.denominator = 360;
    test_fraction.simplify();
    EXPECT_EQ(test_fraction.numerator, 1);
    EXPECT_EQ(test_fraction.denominator, 3);
}

TEST(SimplifyFunctionTests, SimplifyIrregularNegativeFraction)
{
    Fraction test_fraction;
    test_fraction.numerator = -150;
    test_fraction.denominator = 360;
    test_fraction.simplify();
    EXPECT_EQ(test_fraction.numerator, -5);
    EXPECT_EQ(test_fraction.denominator, 12);
}

/***********************************************************************
INVERT() METHOD TESTS
***********************************************************************/

TEST(InvertFunctionTests, AFractionIsInverted)
{
    Fraction test_fraction = Fraction(7, 12);
    test_fraction.invert();
    EXPECT_EQ(test_fraction, Fraction(12, 7));
}

TEST(InvertFunctionTests, AFractionThatIsAWholeNumberIsInverted)
{
    Fraction test_fraction = Fraction(9);
    test_fraction.invert();
    EXPECT_EQ(test_fraction, Fraction(1, 9));
}

TEST(InvertFunctionTests, ZeroCannotBeInverted) // Zero does not have a number that multiplies it to 1
{
    Fraction test_fraction = Fraction();
    EXPECT_THROW(test_fraction.invert(), DivideByZeroError);
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
FRACTION ADDITION
***********************************************************************/

TEST(FractionAdditionTests, BinaryAdditionBasicTest)
{
    Fraction test_fraction_1 = Fraction(1, 4);
    Fraction test_fraction_2 = Fraction(1, 4);
    test_fraction_1 += test_fraction_2;
    EXPECT_EQ(test_fraction_1, Fraction(1, 2));
}

TEST(FractionAdditionTests, BinaryAdditionAddADouble)
{
    Fraction test_fraction_1 = Fraction(1, 4);
    double number = 4;
    test_fraction_1 += number;
    EXPECT_EQ(test_fraction_1, Fraction(17, 4));
}

TEST(FractionAdditionTests, BinaryAdditionAddANeutralizer)
{
    Fraction test_fraction_1 = Fraction(1, 4);
    Fraction test_fraction_2 = Fraction(-1, 4);
    test_fraction_1 += test_fraction_2;
    EXPECT_EQ(test_fraction_1, Fraction(0));
}

TEST(FractionAdditionTests, BinaryAdditionAddAZero)
{
    Fraction test_fraction_1 = Fraction(1, 4);
    double number = 0;
    test_fraction_1 += number;
    EXPECT_EQ(test_fraction_1, Fraction(1, 4));
}

TEST(FractionAdditionTests, AddTwoFractions)
{
    Fraction test_fraction_1 = Fraction(2, 7);
    Fraction test_fraction_2 = Fraction(1, 4);
    Fraction result = Fraction(15, 28);
    EXPECT_TRUE(test_fraction_1 + test_fraction_2 == result);
}

TEST(FractionAdditionTests, CorrectlyAddToZero)
{
    Fraction test_fraction_1 = Fraction(0);
    Fraction test_fraction_2 = Fraction(1, 4);
    Fraction result = Fraction(1, 4);
    EXPECT_TRUE(test_fraction_1 + test_fraction_2 == result);
}

TEST(FractionAdditionTests, CorrectlyAddAZero)
{
    Fraction test_fraction_1 = Fraction(1, 4);
    Fraction test_fraction_2 = Fraction(0);
    Fraction result = Fraction(1, 4);
    EXPECT_TRUE(test_fraction_1 + test_fraction_2 == result);
}

TEST(FractionAdditionTests, CorrectlyAddOpposites)
{
    Fraction test_fraction_1 = Fraction(3, 4);
    Fraction test_fraction_2 = Fraction(-6, 8);
    Fraction result = Fraction(0);
    EXPECT_TRUE(test_fraction_1 + test_fraction_2 == result);
}

TEST(FractionAdditionTests, CorrectlyAddDecimalFractions)
{
    Fraction test_fraction_1 = Fraction(34.765);
    Fraction test_fraction_2 = Fraction(27.212);
    Fraction result = Fraction(61.977);
    EXPECT_TRUE(test_fraction_1 + test_fraction_2 == result);
}

TEST(FractionAdditionTests, CorrectlyAddAConstantRightSide)
{
    Fraction test_fraction_1 = Fraction(3, 10);
    double number = 12;
    Fraction result = Fraction(123, 10);
    EXPECT_TRUE(test_fraction_1 + number == result);
}

TEST(FractionAdditionTests, CorrectlyAddAConstantLeftSide)
{
    Fraction test_fraction_1 = Fraction(3, 10);
    double number = 12;
    Fraction result = Fraction(123, 10);
    EXPECT_TRUE(number + test_fraction_1 == result);
}

TEST(FractionAdditionTests, MultipleAdditionTest)
{
    EXPECT_EQ(0 + Fraction(1, 2) + 8 + Fraction(-1, 2) + 2, Fraction(10));
}

/***********************************************************************
FRACTION SUBTRACTION
***********************************************************************/

TEST(FractionSubtractionTests, BinarySubtractionBasicTest)
{
    Fraction test_fraction_1 = Fraction(1, 2);
    Fraction test_fraction_2 = Fraction(1, 4);
    test_fraction_1 -= test_fraction_2;
    EXPECT_EQ(test_fraction_1, Fraction(1, 4));
}

TEST(FractionSubtractionTests, BinarySubtractionSubtraAdditionAddADouble)
{
    Fraction test_fraction_1 = Fraction(7, 4);
    double number = 1;
    test_fraction_1 -= number;
    EXPECT_EQ(test_fraction_1, Fraction(3, 4));
}

TEST(FractionSubtractionTests, BinarySubtractANeutralizer)
{
    Fraction test_fraction_1 = Fraction(1, 4);
    Fraction test_fraction_2 = Fraction(1, 4);
    test_fraction_1 -= test_fraction_2;
    EXPECT_EQ(test_fraction_1, Fraction(0));
}

TEST(FractionSubtractionTests, BinarySubtractionSubtractZero)
{
    Fraction test_fraction_1 = Fraction(1, 4);
    double number = 0;
    test_fraction_1 -= number;
    EXPECT_EQ(test_fraction_1, Fraction(1, 4));
}

TEST(FractionSubtractionTests, SubtractTwoFractions)
{
    Fraction test_fraction_1 = Fraction(2, 7);
    Fraction test_fraction_2 = Fraction(1, 4);
    Fraction result = Fraction(1, 28);
    EXPECT_TRUE(test_fraction_1 - test_fraction_2 == result);
}

TEST(FractionSubtractionTests, CorrectlySubtractFromZero)
{
    Fraction test_fraction_1 = Fraction(0);
    Fraction test_fraction_2 = Fraction(1, 4);
    Fraction result = Fraction(-1, 4);
    EXPECT_TRUE(test_fraction_1 - test_fraction_2 == result);
}

TEST(FractionSubtractionTests, CorrectlySubtractAZero)
{
    Fraction test_fraction_1 = Fraction(1, 4);
    Fraction test_fraction_2 = Fraction(0);
    Fraction result = Fraction(1, 4);
    EXPECT_TRUE(test_fraction_1 - test_fraction_2 == result);
}

TEST(FractionSubtractionTests, CorrectlySubtractOpposites)
{
    Fraction test_fraction_1 = Fraction(3, 4);
    Fraction test_fraction_2 = Fraction(-6, 8); // these add to 0
    Fraction result = Fraction(3, 2);
    EXPECT_TRUE(test_fraction_1 - test_fraction_2 == result);
}

TEST(FractionSubtractionTests, CorrectlySubtractDecimalFractions)
{
    Fraction test_fraction_1 = Fraction(17.652);
    Fraction test_fraction_2 = Fraction(9.763);
    Fraction result = Fraction(7.889);
    EXPECT_TRUE(test_fraction_1 - test_fraction_2 == result);
}

TEST(FractionSubtractionTests, CorrectlySubtractAConstantRightSide)
{
    Fraction test_fraction_1 = Fraction(3, 10);
    double number = 12;
    Fraction result = Fraction(-117, 10);
    EXPECT_TRUE(test_fraction_1 - number == result);
}

TEST(FractionSubtractionTests, CorrectlySubtractFromAConstantLeftSide)
{
    Fraction test_fraction_1 = Fraction(3, 10);
    double number = 12;
    Fraction result = Fraction(117, 10);
    EXPECT_TRUE(number - test_fraction_1 == result);
}

TEST(FractionSubtractionTests, MultipleSubtractionTest)
{
    EXPECT_EQ(100 - Fraction(1, 2) - 8 - Fraction(-1, 2) - 2, Fraction(90));
}

/***********************************************************************
FRACTION MULTIPLICATION
***********************************************************************/

TEST(FractionMultiplicationTests, BinaryMultiplicationBasicTest)
{
    Fraction test_fraction_1 = Fraction(4, 7);
    Fraction test_fraction_2 = Fraction(2, 5);
    test_fraction_1 *= test_fraction_2;
    EXPECT_EQ(test_fraction_1, Fraction(8, 35));
}

TEST(FractionMultiplicationTests, BinaryMultiplicationByANumber)
{
    Fraction test_fraction_1 = Fraction(5, 4);
    double number = 5;
    test_fraction_1 *= number;
    EXPECT_EQ(test_fraction_1, Fraction(25, 4));
}

TEST(FractionMultiplicationTests, BinaryMultiplicationByAUnit)
{
    Fraction test_fraction_1 = Fraction(5, 4);
    double number = 1;
    test_fraction_1 *= number;
    EXPECT_EQ(test_fraction_1, Fraction(5, 4));
}

TEST(FractionMultiplicationTests, BinaryMultiplicationMultiplyByInverse)
{
    Fraction test_fraction_1 = Fraction(1, 4);
    Fraction test_fraction_2 = Fraction(4);
    test_fraction_1 *= test_fraction_2;
    EXPECT_EQ(test_fraction_1, Fraction(1));
}

TEST(FractionMultiplicationTests, BinaryMultiplicationMultiplyByZero)
{
    Fraction test_fraction_1 = Fraction(1, 4);
    double number = 0;
    test_fraction_1 *= number;
    EXPECT_EQ(test_fraction_1, Fraction());
}

TEST(FractionMultiplicationTests, MultiplyTwoFractions)
{
    Fraction test_fraction_1 = Fraction(-2, 7);
    Fraction test_fraction_2 = Fraction(1, 4);
    Fraction result = Fraction(-2, 28);
    EXPECT_TRUE(test_fraction_1 * test_fraction_2 == result);
}

TEST(FractionMultiplicationTests, CorrectlyMultiplyByFractionZero)
{
    Fraction test_fraction_1 = Fraction(0);
    Fraction test_fraction_2 = Fraction(1, 4);
    Fraction result = Fraction(0);
    EXPECT_TRUE(test_fraction_1 * test_fraction_2 == result);
}

TEST(FractionMultiplicationTests, CorrectlyMultiplyAFractionandAUnit)
{
    Fraction test_fraction_1 = Fraction(1, 4);
    Fraction test_fraction_2 = Fraction(1);
    Fraction result = Fraction(1, 4);
    EXPECT_TRUE(test_fraction_1 * test_fraction_2 == result);
}

TEST(FractionMultiplicationTests, CorrectlyMultiplyByInverse)
{
    Fraction test_fraction_1 = Fraction(3, 4);
    Fraction test_fraction_2 = Fraction(8, 6);
    Fraction result = Fraction(1);
    EXPECT_TRUE(test_fraction_1 * test_fraction_2 == result);
}

TEST(FractionMultiplicationTests, CorrectlyMultiplyDecimalFractions)
{
    Fraction test_fraction_1 = Fraction(1.4);
    Fraction test_fraction_2 = Fraction(1.5);
    Fraction result = Fraction(2.1);
    EXPECT_TRUE(test_fraction_1 * test_fraction_2 == result);
}

TEST(FractionMultiplicationTests, CorrectlyMultiplyByConstantRightSide)
{
    Fraction test_fraction_1 = Fraction(3, 10);
    double number = 12;
    Fraction result = Fraction(36, 10);
    EXPECT_TRUE(test_fraction_1 * number == result);
}

TEST(FractionDivisionTests, CorrectlyMultiplyByADouble)
{
    Fraction test_fraction_1 = Fraction(1, 4);
    double number = 1.25;
    Fraction result = Fraction(3125, 10000);
    EXPECT_TRUE(test_fraction_1 * number == result);
}

TEST(FractionMultiplicationTests, CorrectlyMultiplyByConstantLeftSide)
{
    Fraction test_fraction_1 = Fraction(3, 10);
    double number = 12;
    Fraction result = Fraction(36, 10);
    EXPECT_TRUE(number * test_fraction_1 == result);
}

TEST(FractionMultiplicationTests, CorrectlyMultiplyTwoNegativeFractions)
{
    Fraction test_fraction_1 = Fraction(-1, 10);
    Fraction test_fraction_2 = Fraction(-1, 10);
    Fraction result = Fraction(1, 100);
    EXPECT_TRUE(test_fraction_1 * test_fraction_2 == result);
}

TEST(FractionMultiplicationTests, MultipleMultiplicationsInOneExpression)
{
    EXPECT_EQ(2 * Fraction(1, 2) * Fraction(3, 4) * 3 * Fraction(-1, 2) * 1.5, Fraction(-1.6875));
}

/***********************************************************************
FRACTION DIVISION
***********************************************************************/

TEST(FractionDivisionTests, BinaryDivisionBasicTest)
{
    Fraction test_fraction_1 = Fraction(4, 7);
    Fraction test_fraction_2 = Fraction(2, 5);
    test_fraction_1 /= test_fraction_2;
    EXPECT_EQ(test_fraction_1, Fraction(20, 14));
}

TEST(FractionDivisionTests, BinaryDivisionByANumber)
{
    Fraction test_fraction_1 = Fraction(5, 4);
    double number = 5;
    test_fraction_1 /= number;
    EXPECT_EQ(test_fraction_1, Fraction(1, 4));
}

TEST(FractionDivisionTests, BinaryDivisionByAUnit)
{
    Fraction test_fraction_1 = Fraction(5, 4);
    double number = 1;
    test_fraction_1 /= number;
    EXPECT_EQ(test_fraction_1, Fraction(5, 4));
}

TEST(FractionDivisionTests, BinaryDivisionBySelf)
{
    Fraction test_fraction_1 = Fraction(1, 4);
    Fraction test_fraction_2 = Fraction(1, 4);
    test_fraction_1 /= test_fraction_2;
    EXPECT_EQ(test_fraction_1, Fraction(1));
}

TEST(FractionDivisionTests, BinaryDivisionByZeroIsError)
{
    Fraction test_fraction_1 = Fraction(1, 4);
    double number = 0;
    EXPECT_THROW(test_fraction_1 /= number, DivideByZeroError);
}

TEST(FractionDivisionTests, BinaryDivisionOfFractionZeroIsAllowed)
{
    Fraction test_fraction_1 = Fraction(0);
    Fraction test_fraction_2 = Fraction(1, 4);
    test_fraction_1 /= test_fraction_2;
    EXPECT_EQ(test_fraction_1, Fraction(0));
}

TEST(FractionDivisionTests, DivideTwoFractions)
{
    Fraction test_fraction_1 = Fraction(-2, 7);
    Fraction test_fraction_2 = Fraction(1, 4);
    Fraction result = Fraction(-8, 7);
    EXPECT_TRUE(test_fraction_1 / test_fraction_2 == result);
}

TEST(FractionDivisionTests, ZeroCanBeDividedByAFracion)
{
    Fraction test_fraction_1 = Fraction(0);
    Fraction test_fraction_2 = Fraction(1, 4);
    Fraction result = Fraction(0);
    EXPECT_TRUE(test_fraction_1 / test_fraction_2 == result);
}

TEST(FractionDivisionTests, CorrectlyDivideAFractionAndAUnit)
{
    Fraction test_fraction_1 = Fraction(1, 4);
    Fraction test_fraction_2 = Fraction(1);
    Fraction result = Fraction(1, 4);
    EXPECT_TRUE(test_fraction_1 / test_fraction_2 == result);
}

TEST(FractionDivisionTests, CorrectlyDivideBySelf)
{
    Fraction test_fraction_1 = Fraction(3, 4);
    Fraction test_fraction_2 = Fraction(3, 4);
    Fraction result = Fraction(1);
    EXPECT_TRUE(test_fraction_1 / test_fraction_2 == result);
}

TEST(FractionDivisionTests, CorrectlyDivideDecimalFractions)
{
    Fraction test_fraction_1 = Fraction(1.4);
    Fraction test_fraction_2 = Fraction(1.5);
    Fraction result = Fraction(14, 15);
    EXPECT_TRUE(test_fraction_1 / test_fraction_2 == result);
}

TEST(FractionDivisionTests, CorrectlyDivideAFractionByADouble)
{
    Fraction test_fraction_1 = Fraction(1, 4);
    double number = 1.25;
    Fraction result = Fraction(2, 10);
    EXPECT_TRUE(test_fraction_1 / number == result);
}

TEST(FractionDivisionTests, CorrectlyDivideByConstantRightSide)
{
    Fraction test_fraction_1 = Fraction(3, 10);
    double number = 12;
    Fraction result = Fraction(3, 120);
    EXPECT_TRUE(test_fraction_1 / number == result);
}

TEST(FractionDivisionTests, CorrectlyMultiplyByConstantLeftSide)
{
    Fraction test_fraction_1 = Fraction(3, 10);
    double number = 12;
    Fraction result = Fraction(120, 3);
    EXPECT_TRUE(number / test_fraction_1 == result);
}

TEST(FractionDivisionTests, CorrectlyDivideTwoNegativeFractions)
{
    Fraction test_fraction_1 = Fraction(-1, 10);
    Fraction test_fraction_2 = Fraction(-1, 100);
    Fraction result = Fraction(10);
    EXPECT_TRUE(test_fraction_1 / test_fraction_2 == result);
}

TEST(FractionDivisionTests, MultipleDivisionsInOneExpression)
{
    EXPECT_EQ(2 / Fraction(1, 2) / Fraction(3, 4) / 3 / Fraction(-1, 2) / 1.5, Fraction(-320, 135));
}

TEST(FractionDivisionTests, DivisionByIntegerZeroThrowsError)
{
    Fraction test_fraction_1 = Fraction(1, 8);
    double number = 0;
    EXPECT_THROW(test_fraction_1 / number, DivideByZeroError);
}

TEST(FractionDivisionTests, DivisionOfZeroByFractionIsAllowed)
{
    double number = 0;
    Fraction test_fraction_1 = Fraction(1, 4);
    EXPECT_EQ(number / test_fraction_1, Fraction(0));
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