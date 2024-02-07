#define DOCTEST_CONFIG_IMPLEMENT_WITH_MAIN
#include <doctest/doctest.h>

#include <rational/rational.h>

#include <sstream>


TEST_CASE("Rational - constructor") {
    SUBCASE("Default constructor") {
        Rational r1;
        CHECK(r1.num() == 0);
        CHECK(r1.denum() == 1);
    }

    SUBCASE("Constructor (const int num, const int denom = 1)") {
        CHECK_THROWS(Rational(1, 0));

        Rational r2(5);
        CHECK(r2.num() == 5);
        CHECK(r2.denum() == 1);

        Rational r3(6, 9);
        CHECK(r3.num() == 2);
        CHECK(r3.denum() == 3);

        Rational r4(6, -9);
        CHECK(r4.num() == -2);
        CHECK(r4.denum() == 3);

        Rational r5(-9, 6);
        CHECK(r5.num() == -3);
        CHECK(r5.denum() == 2);

        Rational r6(-9, -6);
        CHECK(r6.num() == 3);
        CHECK(r6.denum() == 2);
    }

    SUBCASE("Constructor (const Rational&)") {
        Rational r7(5, 4);
        Rational r8(r7);
        CHECK(r8.num() == 5);
        CHECK(r8.denum() == 4);
    }
}

TEST_CASE("Rational - operator=") {
    Rational r1(5, 4);
    Rational r2;
    r2 = r1;
    CHECK(r2.num() == 5);
    CHECK(r2.denum() == 4);

    r2 = r2;
    CHECK(r2.num() == 5);
    CHECK(r2.denum() == 4);
}

TEST_CASE("Rational - arithmetic operators") {
    SUBCASE("operator- (unary)") {
        Rational r1(5, 4);
        r1 = -r1;
        CHECK(r1.num() == -5);
        CHECK(r1.denum() == 4);

        Rational r2;
        r2 = -r2;
        CHECK(r2.num() == 0);
        CHECK(r2.denum() == 1);
    }

    SUBCASE("operator+=") {
        Rational r3(2, 3);
        r3 += Rational(-2, 3);
        CHECK(r3.num() == 0);
        CHECK(r3.denum() == 1);
    }

    SUBCASE("operator-=") {
        Rational r4;
        r4 -= Rational(-2, 3);
        CHECK(r4.num() == 2);
        CHECK(r4.denum() == 3);
    }

    SUBCASE("operator*=") {
        Rational r5(3, 2);
        r5 *= Rational(-3, 2);
        CHECK(r5.num() == -9);
        CHECK(r5.denum() == 4);
    }

    SUBCASE("operator/=") {
        Rational r6(-9, 4);

        CHECK_THROWS(r6 /= Rational());

        r6 /= Rational(-2, 3);
        CHECK(r6.num() == 27);
        CHECK(r6.denum() == 8);
    }

    SUBCASE("operator+") {
        Rational r7(2, 3);
        Rational r8(-2, 3);
        r7 = r7 + r8;
        CHECK(r7.num() == 0);
        CHECK(r7.denum() == 1);
    }

    SUBCASE("operator-") {
        Rational r9(3, 2);
        Rational r10(2, 3);
        r9 = r9 - r10;
        CHECK(r9.num() == 5);
        CHECK(r9.denum() == 6);
    }

    SUBCASE("operator*") {
        Rational r11(-2, 3);
        Rational r12(-3, 2);
        r11 = r11 * r12;
        CHECK(r11.num() == 1);
        CHECK(r11.denum() == 1);
    }

    SUBCASE("operator/") {
        Rational r13(-3, 2);

        CHECK_THROWS(r13 / Rational());

        Rational r14(3, 2);
        r13 = r13 / r14;
        CHECK(r13.num() == -1);
        CHECK(r13.denum() == 1);
    }
}

TEST_CASE("Rational - comparison operators") {
    SUBCASE("operator==") {
        CHECK(Rational(2, 3) == Rational(4, 6));
    }

    SUBCASE("operator!=") {
        CHECK(!(Rational(2, 3) != Rational(2, 3)));
    }

    SUBCASE("operator<") {
        CHECK(Rational(-3, 2) < Rational(-2, 3));
    }

    SUBCASE("operator<=") {
        CHECK(!(Rational(-2, 3) <= Rational(-3, 2)));
    }

    SUBCASE("operator>") {
        CHECK(!(Rational(-2, 3) > Rational(-2, 3)));
    }

    SUBCASE("operator>=") {
        CHECK(Rational(27, 8) >= Rational(2, 3));
    }
}

TEST_CASE("Rational - operator<<") {
    Rational r1(10, 2);
    std::stringstream strm1;
    strm1 << r1;
    std::string str1;
    strm1 >> str1;
    CHECK(str1 == "5/1");

    Rational r2(15, -4);
    std::stringstream strm2;
    strm2 << r2;
    std::string str2;
    strm2 >> str2;
    CHECK(str2 == "-15/4");
}

TEST_CASE("Rational - operator>>") {
    Rational r1;
    std::istringstream istrm1("-6/7 2/3");
    istrm1 >> r1;
    CHECK(r1 == Rational(-6, 7));
    CHECK(istrm1.good());
    CHECK(!istrm1.fail());
    CHECK(!istrm1.bad());
    CHECK(!istrm1.eof());

    Rational r2;
    std::istringstream istrm2("2/0");
    istrm2 >> r2;
    CHECK(r2 == Rational());
    CHECK(!istrm2.good());
    CHECK(istrm2.fail());
    CHECK(!istrm2.bad());
    CHECK(istrm2.eof());

    Rational r3;
    std::istringstream istrm3("10 / 12");
    istrm3 >> r3;
    CHECK(r3 == Rational());
    CHECK(!istrm3.good());
    CHECK(istrm3.fail());
    CHECK(!istrm3.bad());
    CHECK(istrm3.eof());

    Rational r4;
    std::istringstream istrm4("10/13 ");
    istrm4 >> r4;
    CHECK(r4 == Rational(10, 13));
    CHECK(istrm4.good());
    CHECK(!istrm4.fail());
    CHECK(!istrm4.bad());
    CHECK(!istrm4.eof());

    Rational r5;
    std::istringstream istrm5("3/");
    istrm5 >> r5;
    CHECK(r5 == Rational());
    CHECK(!istrm5.good());
    CHECK(istrm5.fail());
    CHECK(!istrm5.bad());
    CHECK(istrm5.eof());

    Rational r6;
    std::istringstream istrm6("4\\5 ");
    istrm6 >> r6;
    CHECK(r6 == Rational());
    CHECK(!istrm6.good());
    CHECK(istrm6.fail());
    CHECK(!istrm6.bad());
    CHECK(!istrm6.eof());

    Rational r7;
    std::istringstream istrm7("9 ");
    istrm7 >> r7;
    CHECK(r7 == Rational());
    CHECK(!istrm7.good());
    CHECK(istrm7.fail());
    CHECK(!istrm7.bad());
    CHECK(istrm7.eof());

    Rational r8;
    std::istringstream istrm8("");
    istrm8 >> r8;
    CHECK(r8 == Rational());
    CHECK(!istrm8.good());
    CHECK(istrm8.fail());
    CHECK(!istrm8.bad());
    CHECK(istrm8.eof());

    Rational r9;
    std::istringstream istrm9("5/-4");
    istrm9 >> r9;
    CHECK(r9 == Rational());
    CHECK(!istrm9.good());
    CHECK(istrm9.fail());
    CHECK(!istrm9.bad());
    CHECK(istrm9.eof());
}
