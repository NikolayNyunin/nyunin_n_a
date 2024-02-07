#include <complex/complex.h>

#include <iostream>
#include <sstream>


bool test_parse(const std::string& str) {
    using namespace std;

    istringstream istrm(str);
    Complex c;
    istrm >> c;

    if (istrm.good())
        cout << "Read success: \"" << str << "\" -> " << c << endl;
    else
        cout << "Read error: \"" << str << "\" -> " << c << endl;

    return istrm.good();
}


int main() {
    using namespace std;

    Complex a;
    cout << "Complex a; -> " << a << endl;
    Complex b(5.0);
    cout << "Complex b(5.0); -> " << b << endl;
    Complex c(8.0, 10.0);
    cout << "Complex c(8.0, 10.0); -> " << c << endl << endl;

    Complex d(5.0);
    cout << b << " == " << d << " -> " << (b == d) << endl;
    cout << b << " != " << d << " -> " << (b != d) << endl << endl;
    cout << b << " == 5.0 -> " << (b == 5.0) << endl;
    cout << b << " != 5.0 -> " << (b != 5.0) << endl << endl;

    cout << "operator-: " << c << " -> " << -c << endl << endl;

    cout << a << " + " << b << " == " << a + b << endl;
    cout << a << " + 6.0 == " << a + 6.0 << endl;
    cout << "8.0 + " << d << " == " << 8.0 + d << endl << endl;

    cout << b << " - " << c << " == " << b - c << endl;
    cout << c << " - 3.0 == " << c - 3.0 << endl;
    cout << "-4.5 - " << a << " == " << -4.5 - a << endl << endl;

    cout << c << " * " << d << " == " << c * d << endl;
    cout << d << " * 0.5 == " << d * 0.5 << endl;
    cout << "15.0 * " << b << " == " << 15.0 * b << endl << endl;

    cout << b << " / " << c << " == " << b / c << endl << endl;
    cout << b << " / 0.33 == " << b / 0.33 << endl;
    cout << "-7.0 / " << c << " == " << -7.0 / c << endl << endl;

    try {
        b / a;
    } catch (const std::invalid_argument ex) {
        cout << b << " / " << a << " -> Error: " << ex.what() << "." << endl << endl;
    }

    cout << a << " += " << c << " -> ";
    a += c;
    cout << a << endl;

    cout << b << " += 11.0 -> ";
    b += 11.0;
    cout << b << endl;

    cout << c << " -= " << b << " -> ";
    c -= b;
    cout << c << endl;

    cout << c << " -= 2.0 -> ";
    c -= 2.0;
    cout << c << endl;

    cout << b << " *= " << c << " -> ";
    b *= c;
    cout << b << endl;

    cout << a << " *= 10.0 -> ";
    a *= 10.0;
    cout << a << endl;

    cout << a << " /= " << c << " -> ";
    a /= c;
    cout << a << endl;

    cout << a << " /= 10.0 -> ";
    a /= 10.0;
    cout << a << endl << endl;

    test_parse("{8.9,9}");
    test_parse("{8.9, 9}");
    test_parse("{8.9,9");

    return 0;
}
