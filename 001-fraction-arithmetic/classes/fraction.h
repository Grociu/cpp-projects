#ifndef FRACTION_H
#define FRACTION_H

// Main Fraction Class
class Fraction
{
    public:
        long int numerator;
        long int denominator;
        // Constructors
        Fraction(double x, double y);
        Fraction(double x);
        Fraction();
        // Methods
        void output();
        void simplify();
        void sign();
        void validate();
};

// Various Mathematical Functions
int number_of_decimals(double x);
int greatest_common_divisor(int x, int y);

#endif
