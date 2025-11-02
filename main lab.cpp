#include <iostream>
#include <stdexcept>
#include <cstdlib>   // for llabs

// Simple gcd implementation for old compilers
long long my_gcd(long long a, long long b) {
    a = llabs(a);
    b = llabs(b);
    while (b != 0) {
        long long t = b;
        b = a % b;
        a = t;
    }
    return (a == 0 ? 1 : a);
}

class Fraction {
private:
    long long num; // numerator
    long long den; // denominator

    void normalize() {
        if (den == 0) throw std::invalid_argument("Denominator cannot be zero");
        if (den < 0) { num = -num; den = -den; }
        long long g = my_gcd(num, den);
        num /= g;
        den /= g;
    }

public:
    // Default constructor
    Fraction() : num(0), den(1) {}

    // Parameterized constructor
    Fraction(long long n, long long d) : num(n), den(d) { normalize(); }

    // Destructor (optional)
    ~Fraction() {}

    // Read from keyboard
    void read() {
        std::cout << "Enter numerator and denominator (separated by space): ";
        std::cin >> num >> den;
        normalize();
    }

    // Print to console
    void print() const {
        std::cout << num << "/" << den;
    }

    // Convert to double
    double value() const {
        return static_cast<double>(num) / static_cast<double>(den);
    }

    // Overloaded operators
    Fraction operator+(const Fraction& other) const {
        return Fraction(num * other.den + other.num * den, den * other.den);
    }

    Fraction operator-(const Fraction& other) const {
        return Fraction(num * other.den - other.num * den, den * other.den);
    }

    Fraction operator*(const Fraction& other) const {
        return Fraction(num * other.num, den * other.den);
    }

    Fraction operator/(const Fraction& other) const {
        if (other.num == 0) throw std::domain_error("Division by zero fraction");
        return Fraction(num * other.den, den * other.num);
    }
};

int main() {
    Fraction a, b(3, 4);
    a.read();

    std::cout << "a = "; a.print();
    std::cout << "  ~ " << a.value() << "\n";

    std::cout << "b = "; b.print();
    std::cout << "  ~ " << b.value() << "\n";

    Fraction sum  = a + b;
    Fraction diff = a - b;
    Fraction prod = a * b;
    Fraction quot = a / b;

    std::cout << "\na + b = "; sum.print();  std::cout << "  ~ " << sum.value()  << "\n";
    std::cout << "a - b = "; diff.print(); std::cout << "  ~ " << diff.value() << "\n";
    std::cout << "a * b = "; prod.print(); std::cout << "  ~ " << prod.value() << "\n";
    std::cout << "a / b = "; quot.print(); std::cout << "  ~ " << quot.value() << "\n";

    return 0;
}
