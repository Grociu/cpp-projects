#include <iostream>
#include "dividebyzero.h"

// Error message for trying to put a 0 in a Fraction denominator
const char* DivideByZeroError::what() const throw()
{
    return "Divided by zero while creating a denominator.";
}
