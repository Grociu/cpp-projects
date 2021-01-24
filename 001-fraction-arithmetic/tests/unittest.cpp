#include "../classes/fraction.h"
#include "gtest/gtest.h"

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

/***********************************************************************
***********************************************************************/

// main function for a Google Test CMake implementation
int main(int argc, char **argv) 
{
    printf("Running main() from %s\n", __FILE__);
    testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}