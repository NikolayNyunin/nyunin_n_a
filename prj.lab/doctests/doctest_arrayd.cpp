#define DOCTEST_CONFIG_IMPLEMENT_WITH_MAIN
#include <doctest/doctest.h>

#include <arrayd/arrayd.h>


TEST_CASE("ArrayD - constructor") {
    SUBCASE("Default constructor") {
        ArrayD arr1;
        CHECK(arr1.size() == 0);
        CHECK_THROWS(arr1[0]);
    }

    SUBCASE("Constructor (const std::ptrdiff_t size)") {
        CHECK_THROWS(ArrayD(-1));
        CHECK_NOTHROW(ArrayD(0));

        ArrayD arr2(5);
        CHECK(arr2.size() == 5);
        CHECK(doctest::Approx(arr2[0]) == 0.0f);
        CHECK(doctest::Approx(arr2[4]) == 0.0f);
        CHECK_THROWS(arr2[5]);
    }

    SUBCASE("Constructor (const ArrayD& arr)") {
        ArrayD arr3(3);
        arr3[1] = 1.0f;
        arr3[2] = 2.0f;

        ArrayD arr4(arr3);
        CHECK(arr4.size() == arr3.size());
        CHECK(doctest::Approx(arr4[0]) == 0.0f);
        CHECK(doctest::Approx(arr4[1]) == 1.0f);
        CHECK(doctest::Approx(arr4[2]) == 2.0f);
    }
}

TEST_CASE("ArrayD - operator=") {
    ArrayD arr1(3);
    arr1[0] = 3.0f;
    arr1[1] = 5.0f;
    arr1[2] = 7.0f;

    ArrayD arr2;
    arr2 = arr1;

    CHECK(arr2.size() == arr1.size());
    CHECK(doctest::Approx(arr2[0]) == 3.0f);
    CHECK(doctest::Approx(arr2[1]) == 5.0f);
    CHECK(doctest::Approx(arr2[2]) == 7.0f);

    arr2 = arr2;

    CHECK(arr2.size() == arr1.size());
    CHECK(doctest::Approx(arr2[0]) == 3.0f);
    CHECK(doctest::Approx(arr2[1]) == 5.0f);
    CHECK(doctest::Approx(arr2[2]) == 7.0f);
}

TEST_CASE("ArrayD - operator[]") {
    ArrayD arr1(3);
    CHECK_THROWS(arr1[-1]);
    CHECK_THROWS(arr1[3]);
    CHECK(doctest::Approx(arr1[0]) == 0.0f);

    arr1[0] = 1.0f;
    arr1[1] = 2.0f;
    arr1[2] = 3.0f;
    CHECK(doctest::Approx(arr1[0]) == 1.0f);
    CHECK(doctest::Approx(arr1[1]) == 2.0f);
    CHECK(doctest::Approx(arr1[2]) == 3.0f);

    arr1[1] = 5.0f;
    CHECK(doctest::Approx(arr1[1]) == 5.0f);
}

TEST_CASE("ArrayD - operator[] (const)") {
    ArrayD arr1(3);
    arr1[0] = 5.0f;

    const ArrayD arr2(arr1);
    CHECK(doctest::Approx(arr2[0]) == 5.0f);
    CHECK_THROWS(arr1[-1]);
    CHECK_THROWS(arr1[3]);
}

TEST_CASE("ArrayD - resize") {
    ArrayD arr1(5);
    CHECK_THROWS(arr1.resize(-1));
    CHECK_NOTHROW(arr1.resize(0));
    CHECK_NOTHROW(arr1.resize(2));
    CHECK_NOTHROW(arr1.resize(10));

    CHECK(arr1.size() == 10);
    CHECK(doctest::Approx(arr1[9]) == 0.0f);

    arr1[5] = 5.0f;
    arr1.resize(2);
    arr1.resize(8);
    CHECK(arr1.size() == 8);
    CHECK(doctest::Approx(arr1[5]) == 0.0f);

    arr1[0] = 4.0f;
    arr1[1] = 6.0f;
    arr1[2] = 8.0f;
    arr1.resize(2);
    CHECK(arr1.size() == 2);
    CHECK(doctest::Approx(arr1[0]) == 4.0f);
    CHECK(doctest::Approx(arr1[1]) == 6.0f);
    CHECK_THROWS(arr1[2]);
}
