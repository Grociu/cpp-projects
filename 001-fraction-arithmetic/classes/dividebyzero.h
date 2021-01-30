#include <exception>

#ifndef DIVIDEBYZERO_H
#define DIVIDEBYZERO_H

// Division by zero Exception class

class DivideByZeroError : public std::exception
{
    const char* what() const throw();
};

#endif