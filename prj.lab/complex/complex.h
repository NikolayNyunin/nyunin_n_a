#ifndef COMPLEX_COMPLEX_H_20201007
#define COMPLEX_COMPLEX_H_20201007

#include <iosfwd>


struct Complex {
    Complex() = default;
    Complex(const Complex&) = default;
    Complex& operator=(const Complex&) = default;
    ~Complex() = default;

    explicit Complex(const double real);
    Complex(const double real, const double imaginary);

    bool operator==(const Complex& rhs) const noexcept;
    bool operator==(const double rhs) const noexcept { return operator==(Complex(rhs)); }
    bool operator!=(const Complex& rhs) const noexcept { return !operator==(rhs); }
    bool operator!=(const double rhs) const noexcept { return operator!=(Complex(rhs)); }
    Complex operator-() const noexcept { return Complex(-re, -im); }
    Complex& operator+=(const Complex& rhs) noexcept;
    Complex& operator+=(const double rhs) noexcept { return operator+=(Complex(rhs)); }
    Complex& operator-=(const Complex& rhs) noexcept { return operator+=(-rhs); }
    Complex& operator-=(const double rhs) noexcept { return operator+=(Complex(-rhs)); }
    Complex& operator*=(const Complex& rhs) noexcept;
    Complex& operator*=(const double rhs) noexcept;
    // can throw std::invalid_argument
    Complex& operator/=(const Complex& rhs);
    Complex& operator/=(const double rhs);
    std::ostream& write_to(std::ostream& ostrm) const;
    std::istream& read_from(std::istream& istrm);

    double re{0.0};
    double im{0.0};

    static const char left_brace{'{'};
    static const char separator{','};
    static const char right_brace{'}'};
};

inline bool operator==(const double lhs, const Complex& rhs) { return Complex(lhs) == rhs; }
inline bool operator!=(const double lhs, const Complex& rhs) { return !operator==(lhs, rhs); }

inline Complex operator+(const Complex& lhs, const Complex& rhs) noexcept { return Complex(lhs) += rhs; }
inline Complex operator-(const Complex& lhs, const Complex& rhs) noexcept { return Complex(lhs) -= rhs; }
inline Complex operator*(const Complex& lhs, const Complex& rhs) noexcept { return Complex(lhs) *= rhs; }
inline Complex operator/(const Complex& lhs, const Complex& rhs) { return Complex(lhs) /= rhs; }

inline Complex operator+(const Complex& lhs, const double rhs) noexcept { return Complex(lhs) += rhs; }
inline Complex operator-(const Complex& lhs, const double rhs) noexcept { return Complex(lhs) -= rhs; }
inline Complex operator*(const Complex& lhs, const double rhs) noexcept { return Complex(lhs) *= rhs; }
inline Complex operator/(const Complex& lhs, const double rhs) { return Complex(lhs) /= rhs; }

inline Complex operator+(const double lhs, const Complex& rhs) noexcept { return Complex(lhs) += rhs; }
inline Complex operator-(const double lhs, const Complex& rhs) noexcept { return Complex(lhs) -= rhs; }
inline Complex operator*(const double lhs, const Complex& rhs) noexcept { return Complex(lhs) *= rhs; }
inline Complex operator/(const double lhs, const Complex& rhs) { return Complex(lhs) /= rhs; }

std::ostream& operator<<(std::ostream& ostrm, const Complex& rhs);
std::istream& operator>>(std::istream& istrm, Complex& rhs);

#endif // COMPLEX_COMPLEX_H_20201007
