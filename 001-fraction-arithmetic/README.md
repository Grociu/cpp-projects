This is a C++ Fraction Arithmetic project by Jan Grottel. Started on 19.01.2020

Parameters:
Write a module that allows to define, interact and operate on numbers in fraction form.

https://en.wikipedia.org/wiki/Fraction

Elements that will be needed at project definition:

1. A class Fraction to represent a fraction number.
    a) A simple Fraction has a numerator and a denominator. 
        Ex. "1 / 2", "4 / 3", "-2 / 4"
    b) A fraction can be a mixed number ie. a whole part and a fraction part
        Ex.  "3 1/4", "5 2/4"
    c) A fraction can be a decimal fraction
        Ex. "3.5", "6.43", "3.554"
    d) A fraction can be an improper fraction
        Ex. "5/2", "7/5"

2. A fraction can be reduced (simplified to a proper irreducible form)
    Ex. 4/8 == 1/2

Here's where these methods might be needed:
    - least common denominator
    - greatest common factor
    - Euclidian algorithm 

3. Following logic operations have to be defined:

    == != < > <= >=

4. Following operations can be performed on fractions:

    + - * / pow, inverse

5. A fraction can be represented in multiple ways depending on the type.
    This will be the type of output to the console
    Ex.
    3/2 can be represented as 
    "3 / 2" "1 1/2" "1.5"
    (probably subclasses polymorphism with virtual output functions)

6. C++ unit testing for these functionalities where possible;
