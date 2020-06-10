#ifndef H_KAZACHTKOM_NUMBER
#define H_KAZACHTKOM_NUMBER
namespace kazachTKOM{

class Number {
public:
    Number();
    Number(const long numer, const unsigned int denom = 1);

    const long get_numerator() const;
    const unsigned int get_denominator() const;

    void operator=(const Number&);
    friend Number operator+(const Number&, const Number&);
    friend Number operator-(const Number&, const Number&);
    friend Number operator*(const Number&, const Number&);
    friend Number operator/(const Number&, const Number&);
    friend bool operator==(const Number&, const Number&);
    friend bool operator!=(const Number&, const Number&);
    friend bool operator<(const Number&, const Number&);
    friend bool operator<=(const Number&, const Number&);
    friend bool operator>(const Number&, const Number&);
    friend bool operator>=(const Number&, const Number&);
private:
    long numerator;
    unsigned int denominator;

    void simplify(); // Reduce the fraction to its lowest form.
};

// Helper functions
const unsigned int lcm(const unsigned int, const unsigned int); // Least common multiple.
const unsigned int gcd(const unsigned int, const unsigned int); // Greatest common divisor.

}
#endif // H_KAZACHTKOM_NUMBER
