#include <cmath>
#include <iostream>
#include "fraction.h"

// For a double x returns the number of places after a decimal spot.
// For an integer it should be zero, for a decimal like 1.345 it should be 3
// Precision up to 12 numbers, returns 12 if higher
int number_of_decimals(double x)
{
    double tracker = x;
    int decimals = 0;
    while(tracker != (int(tracker)) && decimals < 12)
    {
        decimals++;
        tracker = tracker*10;
    }
    return decimals;
}

/*
Outputs the Fraction to the console.
Placeholder function until the '>>' operator can be overloaded.
*/
void Fraction::output()
{
    std::cout << "[ " << this->numerator << " / " << this->denominator << " ]";
}

/***********************************************************************
The main constructor of the Fraction class.
If both arguments are integers sets the first argument as the numerator,
and the second as the denominator.
If any are decimal numbers, performs a multiplications by powers of 10
to each non integer argument and sets numerator and denominator to the
correct values.
Ex. 1.5 can be written as 1.5 * 10 / 10
Ex. 2.5 / 2.85 can be written as (2.5 * 10) * 100 / 10 * (2.85 * 100)
Not Yet Implemented: Then a simplification is performed. Ex. 4/8 == 1/2
Not Yet Implemented: Then a sign is extracted to the numerator.
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
        int x_decimals = 0;
        int y_decimals = 0;

        if(x != int(x))
        {
            x_decimals = number_of_decimals(x);
        }
        if(y != int(y))
        {
            y_decimals = number_of_decimals(y);
        }

        this->numerator = (x * pow(10, x_decimals + y_decimals));
        this->denominator = (y * pow(10, x_decimals + y_decimals));
    }
}

Fraction::Fraction(double x) : Fraction::Fraction(x, 1) {} // This is called 'delegating constructors' it's a C++11 feature.
Fraction::Fraction() : Fraction::Fraction(0, 1) {}
