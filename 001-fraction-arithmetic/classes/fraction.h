#ifndef FRACTION_H
#define FRACTION_H

// Main Fraction Class
class Fraction
{
    private:
        static const int precision = 6;  // Governs the precision of conversion from double to integer
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
