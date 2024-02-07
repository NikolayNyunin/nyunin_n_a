#include <rational/rational.h>

#include <iostream>
#include <stdexcept>


Rational::Rational(const int num, const int denom) : num_(num), denom_(denom) {
    if (denom == 0)
        throw std::invalid_argument("Denominator cannot be equal to 0");
    normalize();
}

void Rational::normalize() {
    if (denom_ < 0) {
        num_ *= -1;
        denom_ *= -1;
    }

    int common = gcd(std::abs(num_), denom_);
    num_ /= common;
    denom_ /= common;
}

int Rational::gcd(int a, int b) {
    if (a % b == 0)
        return b;
    if (b % a == 0)
        return a;
    if (a > b)
        return gcd(a % b, b);
    return gcd(a, b % a);
}

Rational& Rational::operator+=(const Rational& rhs) noexcept {
    num_ = num_ * rhs.denom_ + rhs.num_ * denom_;
    denom_ *= rhs.denom_;
    normalize();
    return *this;
}

Rational& Rational::operator*=(const Rational& rhs) noexcept {
    num_ *= rhs.num_;
    denom_ *= rhs.denom_;
    normalize();
    return *this;
}

Rational& Rational::operator/=(const Rational& rhs) {
    if (rhs.num_ == 0)
        throw std::invalid_argument("Division by 0");
    num_ *= rhs.denom_;
    denom_ *= rhs.num_;
    normalize();
    return *this;
}

bool Rational::operator==(const Rational& rhs) const noexcept {
    return (num_ == rhs.num_ && denom_ == rhs.denom_);
}

bool Rational::operator<(const Rational& rhs) const noexcept {
    return (num_ * rhs.denom_ < rhs.num_ * denom_);
}

bool Rational::operator>(const Rational& rhs) const noexcept {
    return (num_ * rhs.denom_ > rhs.num_ * denom_);
}

std::ostream& Rational::write_to(std::ostream& ostrm) const noexcept {
    ostrm << num_ << division_sign << denom_;
    return ostrm;
}

std::istream& Rational::read_from(std::istream& istrm) noexcept {
    int num = 0;
    char division_sign = 0;
    int denom = 1;

    bool extra_space = false;

    istrm >> num;
    if (isspace(istrm.peek()))
        extra_space = true;
    istrm >> division_sign;
    if (isspace(istrm.peek()))
        extra_space = true;
    istrm >> denom;

    if (!istrm.fail() && !istrm.bad()) {
        if (division_sign == Rational::division_sign && denom > 0 && !extra_space) {
            num_ = num;
            denom_ = denom;
            normalize();
        } else
            istrm.setstate(std::ios_base::failbit);
    }

    return istrm;
}
