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
        // Binary arithmetic operators
        Fraction& operator += (const Fraction& right);
        Fraction& operator += (const double number);
        Fraction& operator -= (const Fraction& right);
        Fraction& operator -= (const double number);
        Fraction& operator *= (const Fraction& right);
        Fraction& operator *= (const double number);
        Fraction& operator /= (const Fraction& right);
        Fraction& operator /= (const double number);
        // Methods
        void output();
        void simplify();
        void sign();
        void validate();
        void invert();
};

// Various Mathematical Functions
bool is_whole_number(double x, short precision);
long int greatest_common_divisor(long int x, long int y);
Fraction power(Fraction base, int exponent);


// Logic Operators
bool operator == (const Fraction& left, const Fraction& right);
bool operator != (const Fraction& left, const Fraction& right);
bool operator < (const Fraction& left, const Fraction& right);
bool operator > (const Fraction& left, const Fraction& right);
bool operator <= (const Fraction& left, const Fraction& right);
bool operator >= (const Fraction& left, const Fraction& right);

// Arithmetic functions
Fraction operator + (Fraction left, const Fraction& right);
Fraction operator + (Fraction left, const double number);
Fraction operator - (Fraction left, const Fraction& right);
Fraction operator - (Fraction left, const double number);
Fraction operator * (Fraction left, const Fraction& right);
Fraction operator * (Fraction left, const double number);
Fraction operator / (Fraction left, const Fraction& right);
Fraction operator / (Fraction left, const double number);

#endif
