#include "../../include/program-tree/Number.h"
#include "../../include/exceptions/RuntimeException.h"
#include <cassert>
#include <iostream>
namespace kazachTKOM{

Number::Number()
{}

Number::Number(const long numer, const unsigned int denom)
    : numerator(numer), denominator(denom)
{
    assert(denom != 0);
    simplify();
}

const long Number::get_numerator() const {
    return numerator;
}
const unsigned int Number::get_denominator() const {
    return denominator;
}

void Number::operator=(const Number& other){
    this->numerator = other.numerator;
    this->denominator = other.denominator;
}

Number operator+(const Number& left, const Number& right){
    // Expand fractions so they have the same denominator.
    unsigned int new_denom = lcm(left.denominator, right.denominator);

    Number result;
    result.numerator = ((left.numerator * (new_denom/left.denominator))
                        + (right.numerator * (new_denom/right.denominator)));
                                         // ^ Forcing the division to be done before multiplication with parentheses
                                         // prevents from the result being incorrect when the 'numerator' is negative.
    result.denominator = new_denom;
    result.simplify();

    return result;
}
Number operator-(const Number& left, const Number& right){
    return left + Number(-right.numerator, right.denominator);
}
Number operator*(const Number& left, const Number& right){
    Number result (left.numerator*right.numerator, left.denominator*right.denominator);
    result.simplify();

    return result;
}
Number operator/(const Number& left, const Number& right){
    Number temp = right.numerator > 0 ? Number(right.denominator, right.numerator)
                                        : Number(-static_cast<long>(right.denominator), -right.numerator);
    return left*temp;
}
bool operator==(const Number& left, const Number& right){
    return static_cast<double>(left.numerator) / left.denominator
            == static_cast<double>(right.numerator) / right.denominator;
}
bool operator!=(const Number& left, const Number& right){
    return !(left == right);
}
bool operator<(const Number& left, const Number& right){
    return static_cast<double>(left.numerator) / left.denominator
            < static_cast<double>(right.numerator) / right.denominator;
}
bool operator<=(const Number& left, const Number& right) {
    return static_cast<double>(left.numerator) / left.denominator
            <= static_cast<double>(right.numerator) / right.denominator;
}
bool operator>(const Number& left, const Number& right) {
    return static_cast<double>(left.numerator) / left.denominator
            > static_cast<double>(right.numerator) / right.denominator;
}
bool operator>=(const Number& left, const Number& right){
    return static_cast<double>(left.numerator) / left.denominator
            >= static_cast<double>(right.numerator) / right.denominator;
}

void Number::simplify() {
    unsigned int d = gcd(std::abs(numerator), denominator);
    if (d > 1){
        numerator /= static_cast<long>(d);
        denominator /= d;
    }
}

const unsigned int lcm(const unsigned int a, const unsigned int b){ // Least common multiple.
    return (a * b) / gcd(a, b);
}
const unsigned int gcd(const unsigned int a, const unsigned int b){ // Greatest common divisor.
    if (a == 0)
        return b;
    return gcd(b % a, a);
}

}
