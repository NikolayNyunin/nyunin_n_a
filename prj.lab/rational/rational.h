#ifndef RATIONAL_RATIONAL_H_2281337
#define RATIONAL_RATIONAL_H_2281337

#include <iosfwd>


class Rational {
public:
    Rational() = default;
    Rational(const Rational&) = default;
    Rational& operator=(const Rational&) = default;
    ~Rational() = default;

    Rational(const int num, const int denom = 1);

    int num() const { return num_; }
    int denum() const { return denom_; }

    Rational operator-() const noexcept { return Rational(-num_, denom_); };
    Rational& operator+=(const Rational& rhs) noexcept;
    Rational& operator-=(const Rational& rhs) noexcept { return operator+=(-rhs); }
    Rational& operator*=(const Rational& rhs) noexcept;
    // can throw std::invalid_argument
    Rational& operator/=(const Rational& rhs);

    bool operator==(const Rational& rhs) const noexcept;
    bool operator!=(const Rational& rhs) const noexcept { return !operator==(rhs); }
    bool operator<(const Rational& rhs) const noexcept;
    bool operator<=(const Rational& rhs) const noexcept { return !operator>(rhs); }
    bool operator>(const Rational& rhs) const noexcept;
    bool operator>=(const Rational& rhs) const noexcept { return !operator<(rhs); }

    std::ostream& write_to(std::ostream& ostrm) const noexcept;
    std::istream& read_from(std::istream& istrm) noexcept;

private:
    int num_ = 0;
    int denom_ = 1;

    void normalize();

    int gcd(int a, int b);

    static const char division_sign = '/';
};

inline Rational operator+(const Rational& lhs, const Rational& rhs) noexcept { return Rational(lhs) += rhs; }
inline Rational operator-(const Rational& lhs, const Rational& rhs) noexcept { return Rational(lhs) -= rhs; }
inline Rational operator*(const Rational& lhs, const Rational& rhs) noexcept { return Rational(lhs) *= rhs; }
inline Rational operator/(const Rational& lhs, const Rational& rhs) { return Rational(lhs) /= rhs; }

inline std::ostream& operator<<(std::ostream& ostrm, const Rational& rhs) noexcept { return rhs.write_to(ostrm); }
inline std::istream& operator>>(std::istream& istrm, Rational& rhs) noexcept { return rhs.read_from(istrm); }

#endif // RATIONAL_RATIONAL_H_2281337
