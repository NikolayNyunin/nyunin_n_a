#include <complex/complex.h>

#include <iostream>
#include <limits>
#include <stdexcept>


Complex::Complex(const double real) : Complex(real, 0.0) {}

Complex::Complex(const double real, const double imaginary)
    : re(real), im(imaginary) {}

bool Complex::operator==(const Complex& rhs) const noexcept {
    return std::abs(re - rhs.re) < 2 * std::numeric_limits<double>::epsilon() &&
           std::abs(im - rhs.im) < 2 * std::numeric_limits<double>::epsilon();
}

Complex& Complex::operator+=(const Complex& rhs) noexcept {
    re += rhs.re;
    im += rhs.im;
    return *this;
}

Complex& Complex::operator*=(const Complex& rhs) noexcept {
    double old_re = re;
    re = re * rhs.re - im * rhs.im;
    im = old_re * rhs.im + rhs.re * im;
    return *this;
}

Complex& Complex::operator*=(const double rhs) noexcept {
    re *= rhs;
    im *= rhs;
    return *this;
}

Complex& Complex::operator/=(const double rhs) {
    if (std::abs(rhs) < 2 * std::numeric_limits<double>::epsilon())
        throw std::invalid_argument("Division by zero in Complex::operator/=(const double)");
    re /= rhs;
    im /= rhs;
    return *this;
}

Complex& Complex::operator/=(const Complex& rhs) {
    const double denom = rhs.re * rhs.re + rhs.im * rhs.im;
    if (denom < 2 * std::numeric_limits<double>::epsilon())
        throw std::invalid_argument("Division by zero in Complex::operator/=(const Complex&)");
    operator*=(Complex(rhs.re, -rhs.im));
    operator/=(denom);
    return *this;
}

std::ostream& Complex::write_to(std::ostream& ostrm) const {
    ostrm << left_brace << re << separator << im << right_brace;
    return ostrm;
}

std::istream& Complex::read_from(std::istream& istrm) {
    char left_brace(0);
    double real(0.0);
    char comma(0);
    double imaginary(0.0);
    char right_brace(0);
    istrm >> left_brace >> real >> comma >> imaginary >> right_brace;

    if (istrm.good()) {
        if ((Complex::left_brace == left_brace) && (Complex::separator == comma) &&
            (Complex::right_brace == right_brace)) {
            re = real;
            im = imaginary;
        } else
            istrm.setstate(std::ios_base::failbit);
    }

    return istrm;
}

std::ostream& operator<<(std::ostream& ostrm, const Complex& rhs) {
    return rhs.write_to(ostrm);
}

std::istream& operator>>(std::istream& istrm, Complex& rhs) {
    return rhs.read_from(istrm);
}
