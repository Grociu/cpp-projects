#include <cmath>
#include <iostream>
#include "fraction.h"

/*
Implementation of Euclidean algorithm to find the greatest common divisor of
positive integers 'x' and 'y'.
https://en.wikipedia.org/wiki/Euclidean_algorithm
*/
int greatest_common_divisor(int x, int y)
{
    int temp;
    while(y != 0)
    {
        temp = y;
        y = x % y;
        x = temp;
    }
    return x;
}

/*
Outputs the Fraction to the console.
Placeholder function until the '>>' operator can be overloaded.
*/
void Fraction::output()
{
    std::cout << "[ " << this->numerator << " / " << this->denominator << " ]";
}

/*
Simplifies the numerator and denominator of a Fraction by dividing it by the
greatest common divisor.
*/
void Fraction::simplify()
{
    int hcd = greatest_common_divisor(
        abs(this->numerator), abs(this->denominator)
        );
    this->numerator = this->numerator / hcd;
    this->denominator = this->denominator / hcd;
}

/*
Figures out the correct sign (+ or -) of the fraction and moves it to the
numerator.
Ex. -1 / 2 => -1 / 2
Ex. 1 / -2 => -1 / 2
Ex. - 1 / -2 => 1 / 2
*/
void Fraction::sign()
{
    bool positive = true;
    if(this->numerator < 0)
    {
        positive = !positive;
    }
    if(this->denominator < 0)
    {
        positive = !positive;
    }
    this->numerator = positive ? abs(this->numerator) : -abs(this->numerator);  // ternary operator
    this->denominator = abs(this->denominator);
}

/*
Perform a series of checks to determine the correcto representation of the 
fraction.
*/
void Fraction::validate()
{
    this->simplify();
    this->sign();
}

/***********************************************************************
The main constructor of the Fraction class.
If both arguments are integers sets the first argument as the numerator,
and the second as the denominator.
If any are decimal numbers, performs a double division and the result is then
multiplied by 10 to power of Fraction class precision (6).
The numerator is then rounded, and both numerator and denominator are set to the
correct values.
Ex. 1.5 can be written as 1.5 * 10 / 10
Ex. 2.5 / 2.85 can be written as (2.5 * 10) * 100 / 10 * (2.85 * 100)
Then a simplification is performed. Ex. 4/8 == 1/2
Then a sign is extracted to the numerator.
Ex. 1 / -1 == -1 / 1 AND -2 / -3 == 2 / 3
***********************************************************************/
Fraction::Fraction(double x, double y)
{
    if(x == int(x) && y == int(y))
    {
        this->numerator = x;
        this->denominator = y;
    }
    else
    {
        double value = x / y;
        long int denominator = pow(10, this->precision);
        value = value * denominator;
        value = round(value);
        this->numerator = value;
        this->denominator = denominator;
    }
    this->validate();
}

Fraction::Fraction(double x) : Fraction::Fraction(x, 1) {} // This is called 'delegating constructors' it's a C++11 feature.
Fraction::Fraction() : Fraction::Fraction(0, 1) {}

// Comparison operators for Fraction class

/*
Equality operator for the Fraction class.
Two fractions are equal when their numerator and denominator are equal.
Fractions are simplified during construction, so Fraction(1, 2) == Fraction(2, 4).
*/
bool operator == (const Fraction& left, const Fraction& right)  // boolean for comparison
{
    return left.numerator == right.numerator &&
           left.denominator == right.denominator;
}

/*
Not Equal operator for the Fraction class.
Two fractions are not equal when either their numerator or denominator are different.
Fractions are simplified during construction, so Fraction(1, 2) == Fraction(2, 4).
*/
bool operator != (const Fraction& left, const Fraction& right)
{
    return ! operator == (left, right);
}

/*
Is Smaller Than operator for the Fraction class.
Raises both numerators to a common denominator and complares the values.
A fraction is smaller than another when it's numerator multiplied by (positive)
denominator of the other is smaller than the other fractions numerator multiplied 
by original denominator
Ex: 1 / 5  < 1 / 3 because 1 * 3 < 5 * 1
Ex: -6 / 7 < -2 / 5 because -6 * 5 (-30) < 7 * -2 (-14)
*/
bool operator < (const Fraction& left, const Fraction& right)
{
    return left.numerator * right.denominator < right.numerator * left.denominator;
}

// The following three operators are derived from the above basic operators:

/*
Is Greater Than operator for the Fraction class.
*/
bool operator > (const Fraction& left, const Fraction& right)
{
    return operator < (right, left);
}

/*
Is Smaller or Equal Than operator for the Fraction class.
*/
bool operator <= (const Fraction& left, const Fraction& right)
{
    return ! operator > (left, right);
}

/*
Is Greater or Equal Than operator for the Fraction class.
*/
bool operator >= (const Fraction& left, const Fraction& right)
{
    return  ! operator < (left, right);
}
