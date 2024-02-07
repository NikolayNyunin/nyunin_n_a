#include <rational/rational.h>

#include <iostream>
#include <sstream>


bool test_parse(const std::string& str) {
    using namespace std;

    istringstream istrm(str);
    Rational r;
    istrm >> r;

    if (!istrm.fail() && !istrm.bad())
        cout << "Read success: \"" << str << "\" -> " << r << endl;
    else
        cout << "Read error: \"" << str << "\" -> " << r << endl;

    return istrm.good();
}


int main() {
    using namespace std;

    Rational a;
    cout << "Rational a; -> " << a << endl;
    Rational b(5);
    cout << "Rational b(5); -> " << b << endl << endl;

    try {
        Rational r(1, 0);
    } catch (const std::invalid_argument ex) {
        cout << "Rational r(1, 0); -> Error: " << ex.what() << "." << endl << endl;
    }

    Rational r1(6, 9);
    cout << "(6, 9) -> " << r1 << endl;
    Rational r2(6, -9);
    cout << "(6, -9) -> " << r2 << endl;
    Rational r3(-9, 6);
    cout << "(-9, 6) -> " << r3 << endl;
    Rational r4(-9, -6);
    cout << "(-9, -6) -> " << r4 << endl << endl;

    Rational r5(5, 4);
    cout << "operator-: " << r5 << " -> " << -r5 << endl << endl;

    cout << r1 << " + " << r2 << " == " << r1 + r2 << endl;
    cout << r4 << " - " << r1 << " == " << r4 - r1 << endl;
    cout << r2 << " * " << r3 << " == " << r2 * r3 << endl;
    cout << r3 << " / " << r4 << " == " << r3 / r4 << endl << endl;

    const Rational r0(0);
    try {
        r3 / r0;
    } catch (const std::invalid_argument ex) {
        cout << r3 << " / " << r0 << " -> Error: " << ex.what() << "." << endl << endl;
    }

    cout << r1 << " += " << r2;
    r1 += r2;
    cout << " -> " << r1 << endl;

    cout << r1 << " -= " << r2;
    r1 -= r2;
    cout << " -> " << r1 << endl;

    cout << r4 << " *= " << r3;
    r4 *= r3;
    cout << " -> " << r4 << endl;

    cout << r4 << " /= " << r2;
    r4 /= r2;
    cout << " -> " << r4 << endl << endl;

    try {
        r4 /= r0;
    } catch (const std::invalid_argument ex) {
        cout << r4 << " /= " << r0 << " -> Error: " << ex.what() << "." << endl << endl;
    }

    cout << r1 << " == " << -r2 << " -> " << (r1 == -r2) << endl;
    cout << r1 << " != " << -r2 << " -> " << (r1 != -r2) << endl;
    cout << r3 << " < " << r2 << " -> " << (r3 < r2) << endl;
    cout << r2 << " <= " << r3 << " -> " << (r2 <= r3) << endl;
    cout << r2 << " > " << r2 << " -> " << (r2 > r2) << endl;
    cout << r4 << " >= " << r1 << " -> " << (r4 >= r1) << endl << endl;

    test_parse("-6/7 2/3");
    test_parse("2/0");
    test_parse("10 / 12");
    test_parse("10/13 ");
    test_parse("3/");
    test_parse("4\\5 ");
    test_parse("9 ");
    test_parse("");
    test_parse("5/-4");

    return 0;
}
