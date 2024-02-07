#define DOCTEST_CONFIG_IMPLEMENT_WITH_MAIN
#include <doctest/doctest.h>

#include <complex/complex.h>

#include <sstream>


TEST_CASE("Complex - constructor") {
    SUBCASE("Default constructor") {
        Complex c1;
        CHECK(doctest::Approx(c1.re) == 0.0);
        CHECK(doctest::Approx(c1.im) == 0.0);
    }

    SUBCASE("Constructor (const double real)") {
        Complex c2(5.0);
        CHECK(doctest::Approx(c2.re) == 5.0);
        CHECK(doctest::Approx(c2.im) == 0.0);
    }

    SUBCASE("Constructor (const double real, const double imaginary)") {
        Complex c3(1.5, 3.5);
        CHECK(doctest::Approx(c3.re) == 1.5);
        CHECK(doctest::Approx(c3.im) == 3.5);
    }

    SUBCASE("Constructor (const Complex&)") {
        Complex c4(5.0, 4.0);
        Complex c5(c4);
        CHECK(doctest::Approx(c5.re) == 5.0);
        CHECK(doctest::Approx(c5.im) == 4.0);
    }
}

TEST_CASE("Complex - operator=") {
    Complex c1(5.0, 4.0);
    Complex c2;
    c2 = c1;
    CHECK(doctest::Approx(c2.re) == 5.0);
    CHECK(doctest::Approx(c2.im) == 4.0);

    c2 = c2;
    CHECK(doctest::Approx(c2.re) == 5.0);
    CHECK(doctest::Approx(c2.im) == 4.0);
}

TEST_CASE("Complex - comparison operators") {
    SUBCASE("operator==") {
        CHECK(Complex(5.0) == Complex(5.0));
        CHECK(Complex(9.0, 12.0) == Complex(9.0, 12.0));
        CHECK(Complex(5.0) == 5.0);
        CHECK(!(5.0 == Complex(0, 5.0)));
    }

    SUBCASE("operator!=") {
        CHECK(!(Complex(5.0) != Complex(5.0)));
        CHECK(!(Complex(9.0, 12.0) != Complex(9.0, 12.0)));
        CHECK(!(Complex(5.0) != 5.0));
        CHECK(5.0 != Complex(0, 5.0));
    }
}

TEST_CASE("Complex - arithmetic operators") {
    SUBCASE("operator- (unary)") {
        CHECK(-Complex() == Complex());
        CHECK(-Complex(5.0) == Complex(-5.0));
        CHECK(-Complex(8.0, 10.0) == Complex(-8.0, -10.0));
    }

    SUBCASE("operator+=") {
        Complex c1;
        c1 += Complex(8.0, 10.0);
        CHECK(c1 == Complex(8.0, 10.0));

        Complex c2(5.0);
        c2 += 11.0;
        CHECK(c2 == Complex(16.0));
    }

    SUBCASE("operator-=") {
        Complex c3(8.0, 10.0);
        c3 -= Complex(16.0);
        CHECK(c3 == Complex(-8.0, 10.0));

        c3 -= 2.0;
        CHECK(c3 == Complex(-10.0, 10.0));
    }

    SUBCASE("operator*=") {
        Complex c4(16.0);
        c4 *= Complex(-10.0, 10.0);
        CHECK(c4 == Complex(-160.0, 160.0));

        Complex c5(8.0, 10.0);
        c5 *= 10.0;
        CHECK(c5 == Complex(80.0, 100.0));
    }

    SUBCASE("operator/=") {
        Complex c6(80.0, 100.0);

        CHECK_THROWS(c6 /= Complex());

        c6 /= Complex(-10.0, 10.0);
        CHECK(c6 == Complex(1.0, -9.0));

        c6 /= 10.0;
        CHECK(c6 == Complex(0.1, -0.9));
    }

    SUBCASE("operator+") {
        CHECK(Complex() + Complex(5.0) == Complex(5.0));
        CHECK(Complex(0.0, 6.5) + 6.0 == Complex(6.0, 6.5));
        CHECK(8.0 + Complex(5.0) == Complex(13.0));
    }

    SUBCASE("operator-") {
        CHECK(Complex(5.0) - Complex(8.0, 10.0) == Complex(-3.0, -10.0));
        CHECK(Complex(8.0, 10.0) - 3.0 == Complex(5.0, 10.0));
        CHECK(-4.5 - Complex() == Complex(-4.5));
    }

    SUBCASE("operator*") {
        CHECK(Complex(8.0, 10.0) * Complex(5.0) == Complex(40.0, 50.0));
        CHECK(Complex(5.0) * 0.5 == Complex(2.5));
        CHECK(15.0 * Complex(5.0) == Complex(75.0));
    }

    SUBCASE("operator/") {
        CHECK_THROWS(Complex(10.0, 150.0) / Complex());

        CHECK(Complex(8.0) / Complex(8.0, 16.0) == Complex(0.2, -0.4));
        CHECK(Complex(5.0) / 0.33 == Complex(5.0 / 0.33));
        CHECK(-7.0 / Complex(7.0, 7.0) == Complex(-0.5, 0.5));
    }
}

TEST_CASE("Complex - operator<<") {
    Complex c1(10, 2);
    std::stringstream strm1;
    strm1 << c1;
    std::string str1;
    strm1 >> str1;
    CHECK(str1 == "{10,2}");

    Complex c2(15, -4);
    std::stringstream strm2;
    strm2 << c2;
    std::string str2;
    strm2 >> str2;
    CHECK(str2 == "{15,-4}");
}

TEST_CASE("Complex - operator>>") {
    Complex c1;
    std::istringstream istrm1("{8.9,9}");
    istrm1 >> c1;
    CHECK(c1 == Complex(8.9, 9.0));

    Complex c2;
    std::istringstream istrm2("{10, 9}");
    istrm2 >> c2;
    CHECK(c2 == Complex(10.0, 9.0));

    Complex c3;
    std::istringstream istrm3("{7.5,9");
    istrm3 >> c3;
    CHECK(c3 == Complex());
}
