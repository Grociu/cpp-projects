#include <iostream>
#include "dividebyzero.h"

const char* DivideByZeroError::what() const throw()
{
    return "Divided by zero while creating a denominator.";
}
