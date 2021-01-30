#include <iostream>
#include "./classes/fraction.h"
#include "./classes/dividebyzero.h"

int main()
{
    Fraction half = Fraction(1, 2);
    Fraction five = Fraction(5);
    Fraction zero = Fraction();
    Fraction aberrant = Fraction(4.5, 3.33);

    half.output();
    five.output();
    zero.output();
    aberrant.output();
}
