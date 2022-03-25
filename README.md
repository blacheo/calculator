# calculator
A calculator that supports parentheses, variables and functions

## Motivation
I started this project during my class on assemblers and compilers. We learned about the process of compiling a programming language; scanning, parsing, syntax checking and generating. I found this to be really cool and I wanted to play with the process. So I'm applying what I'm learning from this class to make a calculator. This calculator should be able to do more than just arithmetic on two numbers, it should be able to process more complex expressions, including ones with parentheses.

## Parts

### Scanner
The scanner is the first part of the calculator. It takes in input and converts it into tokens.

Example:

1 + 2 -> NUM 1, PLUS +, NUM 2

or

sqrt(2) -> ID sqrt, LPAREN (, NUM 2, RPAREN )
