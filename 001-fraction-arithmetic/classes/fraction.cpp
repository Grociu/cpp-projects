#include <cmath>
#include <iostream>
#include "dividebyzero.h"
#include "fraction.h"

/*
Checks whether a double number is an integer with a given precision degree.
As decimal numbers declared as double values are not represented precisely, 
a method of checking if in fact it is an integer has to be devised.
Ex. 1.23 is actually  1.229999999999999982
Current implementation takes the number 'x' and a degree of 'precision'.
A number is deemed a whole number when abs of its' decimal part is smaller than 10^-(precision)
Ex. 123.199.. - 123 = .199 > 0.1 - not a whole number
Ex. 1231.99.. - 1232 = .000. < 0.1 - whole number
*/
bool is_whole_number(double x, short precision)
{
    double x_remainder = fabs(x - round(x));  // fabs is float abs
    double margin = pow(10, -(precision));
    return x_remainder < margin;
}

/*
Implementation of Euclidean algorithm to find the greatest common divisor of
positive integers 'x' and 'y'.
https://en.wikipedia.org/wiki/Euclidean_algorithm
*/
long int greatest_common_divisor(long int x, long int y)
{
    long int temp;
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
    long int hcd = greatest_common_divisor(
        labs(this->numerator), labs(this->denominator)
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
    this->numerator = positive ? labs(this->numerator) : -labs(this->numerator);  // ternary operator
    this->denominator = labs(this->denominator);  // labs is long abs
}

/*
Inverts a Fraction object.
Switches the values of the numerator and denominator, keeps the sign in the numerator.
Contains a validation step - catches zero division.
*/
void Fraction::invert()
{
    long int temp;
    temp = numerator;
    this->numerator = denominator;
    this->denominator = temp;
    this->validate();
}

/*
Perform a series of checks to determine the correct representation of the 
Fraction.
Contains a validation of zero division.
*/
void Fraction::validate()
{
    if(denominator == 0)
    {
        throw DivideByZeroError();
    }
    this->simplify();
    this->sign();
}

/***********************************************************************
The main constructor of the Fraction class.
Covers multiple steps depending on the type of the arguments.
Variant 1: 
If both arguments are integers sets the first argument as the numerator,
and the second as the denominator.
Variant 2:
If both arguments convert to integers within the margin of precision,
they are gradually multiplied by 10 to a point where they are whole numbers.
Then the new alues are assigned to numerator and denominator.
Variant 3:
If any of the values are not within precision, they are divided and then multiplied by 10^precision,
the result is rounded and assigned to numerator while 10^precision is assigned to numerator.
to numerator and denominator.
Ex. 1.5 can be written as 1.5 * 10 / 10 (Variant 2)
Ex. 2.5 / 2.85 can be written as (2.5 * 10) * 100 / 10 * (2.85 * 100)
Then a simplification is performed. Ex. 4/8 == 1/2
Then a sign is extracted to the numerator.
Ex. 1 / -1 == -1 / 1 AND -2 / -3 == 2 / 3
***********************************************************************/
Fraction::Fraction(double x, double y)
{
    // Phase 1 - are they both integers? Put them into numerator, denominator.
    if(x == int(x) && y == int(y))
    {
        this->numerator = x;
        this->denominator = y;
        this->validate();
        return;
    }
    // Phase 2 - multiply both by 10 towards precision to get a representation via whole numbers
    // This will convert simple fractions like 1.5 (2/3) without making the actual division
    if (true)
    {
        short decimals = 0;
        const short p = this->precision;
        while(decimals < p)
        {
            decimals++;
            x *= 10;
            y *= 10;
            if(is_whole_number(x, p) && is_whole_number(y, p))
            {
                this->numerator = round(x);
                this->denominator = round(y);
                this->validate();
                return;
            }
        }
    }
    // Phase 3 - divide the two numbers and return a rounded approximate solution
    if (true)
    {
        long pow_of_precision = pow(10, this->precision);
        double value = x / y;
        value = value * pow_of_precision;
        value = round(value);
        this->numerator = value;
        this->denominator = pow_of_precision;
        this->validate();
        return;
    }
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
    return ! operator < (left, right);
}

// Binary arithmetic operators
/*
Binary operator for adding a Fraction object to another. A common denominator is reached,
and the numerators are added. Original Fraction object is modified.
*/
Fraction& Fraction::operator += (const Fraction& right)
{
    this->numerator = numerator * right.denominator + right.numerator * denominator;
    this->denominator = denominator * right.denominator;
    this->validate();
    return *this;
}

/*
Binary addition for adding any number, be it integer or double.
Number is converted to a fraction then added. Original Fraction object is modified.
*/
Fraction& Fraction::operator += (const double number)
{
    *this += Fraction(number);
    return *this;
}

/*
Binary subtraction for adding a Fraction object to another. Performs addition of Fraction
that had its numerator multiplied by -1. Original Fraction object is modified.
*/
Fraction& Fraction::operator -= (const Fraction& right)
{
    *this += Fraction(-1 * right.numerator, right.denominator);
    return *this;
}

/*
Binary subtraction for adding an integer or double value to a Fraction object. 
Converts the number to a Fraction object then subtract.
Original Fraction object is modified.
*/
Fraction& Fraction::operator -= (const double number)
{
    *this -= Fraction(number);
    return *this;
}

/*
Binary multiplicaton for multiplying a Fraction by another.
Multiplies the numerators and denominators and then validates (simplifies) the Fraction object.
Original Fraction object is modified.
*/
Fraction& Fraction::operator *= (const Fraction& right)
{
    this->numerator = numerator * right.numerator;
    this->denominator = denominator * right.denominator;
    this->validate();
    return *this;
}

/*
Binary multiplicaton for multiplying a Fraction by a double value. 
Converts the number to a Fraction object then multiplies.
Original Fraction object is modified.
*/
Fraction& Fraction::operator *= (const double number)
{
    *this *= Fraction(number);
    return *this;
}

/*
Binary division for dividing a Fraction object by another.
Inverts the fraction on the right and then performs the multiplication operation.
Original Fraction object is modified.
*/
Fraction& Fraction::operator /= (const Fraction& right)
{
    Fraction temp = right;
    temp.invert();
    *this *= temp;
    return *this;
}

/*
Binary division for dividing a Fraction by a double value. 
Converts the number to an inverted Fraction object then multiplies.
Original Fraction object is modified.
*/
Fraction& Fraction::operator /= (const double number)
{
    *this *= Fraction(1, number);
    return *this;
}

/***********************************************************************
Arithmetic functions
***********************************************************************/

/*
Addition of Fraction objects. Returns a new Fraction object.
*/
Fraction operator + (Fraction left, const Fraction& right)
{
    left += right;
    return left;
}

/*
Addition of a number to a Fraction object. Returns a new Fraction object.
*/
Fraction operator + (Fraction left, const double number)
{
    left += number;
    return left;
}

/*
Subtraction operator for Fraction objects. Returns a new Fraction object.
*/
Fraction operator - (Fraction left, const Fraction& right)
{
    left -= right;
    return left;
}

/*
Subtractions of a number from a Fraction object. Returns a new Fraction object.
*/
Fraction operator - (Fraction left, const double number)
{
    left -= number;
    return left;
}

/*
Multiplication operator for Fraction objects. Returns a new Fraction object.
*/
Fraction operator * (Fraction left, const Fraction& right)
{
    left *= right;
    return left;
}

/*
Multiplication operator for Fraction objects and doubles.
Returns a new Fraction object.
*/
Fraction operator * (Fraction left, const double number)
{
    left *= number;
    return left;
}

/*
Division operator for Fraction objects. Returns a new Fraction object.
*/
Fraction operator / (Fraction left, const Fraction& right)
{
    left /= right;
    return left;
}

/*
Division operator for Fraction objects and doubles.
Returns a new Fraction object.
*/
Fraction operator / (Fraction left, const double number)
{
    left /= number;
    return left;
}

/*
pow() function overload for a Fraction object.
Raises the Fraction 'base' to the power of 'exponent'. Currently only valid for integer exponents.
*/
Fraction power(Fraction base, int exponent)
{
    if(exponent < 0)
    {
        if(base.numerator == 0) {throw DivideByZeroError();}
        base.invert();
        return power(base, -exponent);
    }
    Fraction result;
    result.numerator = powl(base.numerator, exponent);
    result.denominator = powl(base.denominator, exponent);
    result.validate();
    return result;
}
