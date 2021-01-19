#include <iostream>
#include "fraction.h"

/*
Outputs the Fraction to the console.
Placeholder function until the '>>' operator can be overloaded.
*/
void Fraction::output()
{
    std::cout << "[ " << this->numerator << " / " << this->denominator << " ]";
}

/*
The main constructor of the Fraction class.
Sets the first argument as the numerator, the second as the denominator.
*/
Fraction::Fraction(double x, double y)
{
    this->numerator = x;
    this->denominator = y;
}
Fraction::Fraction(double x) : Fraction::Fraction(x, 1) {} // This is called 'delegating constructors' it's a C++11 feature.
Fraction::Fraction() : Fraction::Fraction(0, 1) {}
