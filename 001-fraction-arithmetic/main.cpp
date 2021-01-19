#include <iostream>
#include "./classes/fraction.h"

int main()
{
    Fraction half = Fraction(1, 2);
    Fraction five = Fraction(5);
    Fraction zero = Fraction();
    Fraction aberrant = Fraction(4.5, 3.33);  //inputs should be non-decimal integers, ## TO DO

    half.output();
    five.output();
    zero.output();
    aberrant.output();
}
