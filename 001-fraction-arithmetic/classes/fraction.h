#ifndef FRACTION_H
#define FRACTION_H

class Fraction
{
    public:
        double numerator;
        double denominator;
        // Constructors
        Fraction(double x, double y);
        Fraction(double x);
        Fraction();
        void output();

};

#endif