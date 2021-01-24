#ifndef FRACTION_H
#define FRACTION_H

class Fraction
{
    public:
        long int numerator;
        long int denominator;
        // Constructors
        Fraction(double x, double y);
        Fraction(double x);
        Fraction();

        void output();
        friend int number_of_decimals(double x);
};

#endif
