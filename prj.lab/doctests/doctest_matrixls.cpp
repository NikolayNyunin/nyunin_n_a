#define DOCTEST_CONFIG_IMPLEMENT_WITH_MAIN
#include <doctest/doctest.h>

#include <matrixls/matrixls.h>


TEST_CASE("MatrixLs - constructor") {
    MatrixLs m1;
    CHECK(m1.colCount() == 0);
    CHECK(m1.rowCount() == 0);

    MatrixLs m2(3, 4);
    CHECK(m2.colCount() == 3);
    CHECK(m2.rowCount() == 4);

    CHECK_THROWS(MatrixLs(5, 0));
    CHECK_THROWS(MatrixLs(-3, 2));
}

TEST_CASE("MatrixLs - at") {
    MatrixLs m(1, 1);
    CHECK(doctest::Approx(m.at(0, 0)) == 0.0);

    m.at(0, 0) = 5.0;
    CHECK(doctest::Approx(m.at(0, 0)) == 5.0);

    CHECK_THROWS(m.at(-1, 0));
    CHECK_THROWS(m.at(0, -5));
    CHECK_THROWS(m.at(0, 2));
    CHECK_THROWS(m.at(4, 0));
}

TEST_CASE("MatrixLs - at (const)") {
    const MatrixLs m(1, 1);
    CHECK(doctest::Approx(m.at(0, 0)) == 0.0);

    CHECK_THROWS(m.at(-1, 0));
    CHECK_THROWS(m.at(0, -5));
    CHECK_THROWS(m.at(0, 2));
    CHECK_THROWS(m.at(4, 0));
}

TEST_CASE("MatrixLs - transpose") {
    MatrixLs m(3, 2);
    m.at(0, 0) = 0.0;
    m.at(0, 1) = 1.0;
    m.at(0, 2) = 2.0;
    m.at(1, 0) = 3.0;
    m.at(1, 1) = 4.0;
    m.at(1, 2) = 5.0;

    m.transpose();

    CHECK(m.rowCount() == 3);
    CHECK(m.colCount() == 2);
    CHECK(doctest::Approx(m.at(0, 0)) == 0.0);
    CHECK(doctest::Approx(m.at(1, 0)) == 1.0);
    CHECK(doctest::Approx(m.at(2, 0)) == 2.0);
    CHECK(doctest::Approx(m.at(0, 1)) == 3.0);
    CHECK(doctest::Approx(m.at(1, 1)) == 4.0);
    CHECK(doctest::Approx(m.at(2, 1)) == 5.0);
}

TEST_CASE("MatrixLs - multiply") {
    MatrixLs m1(4, 2);
    m1.at(0, 0) = 1.0;
    m1.at(0, 1) = -1.0;
    m1.at(0, 2) = 2.0;
    m1.at(0, 3) = -2.0;
    m1.at(1, 0) = 1.0;
    m1.at(1, 1) = 1.0;
    m1.at(1, 2) = 2.0;
    m1.at(1, 3) = 2.0;

    CHECK_NOTHROW(m1.multiply());

    MatrixLs m2(2, 4);
    m2.at(0, 0) = 0.0;
    m2.at(0, 1) = 1.0;
    m2.at(1, 0) = 2.0;
    m2.at(1, 1) = 0.0;
    m2.at(2, 0) = 0.0;
    m2.at(2, 1) = 3.0;
    m2.at(3, 0) = 4.0;
    m2.at(3, 1) = 0.0;

    m1.multiply(m2);
    CHECK(m1.rowCount() == 2);
    CHECK(m1.colCount() == 2);

    CHECK(doctest::Approx(m1.at(0, 0)) == -10.0);
    CHECK(doctest::Approx(m1.at(0, 1)) == 7.0);
    CHECK(doctest::Approx(m1.at(1, 0)) == 10.0);
    CHECK(doctest::Approx(m1.at(1, 1)) == 7.0);

    CHECK_THROWS(MatrixLs(3, 3).multiply(MatrixLs(2, 2)));
    CHECK_THROWS(MatrixLs(3, 2).multiply(MatrixLs(3, 2)));
    CHECK_THROWS(MatrixLs(3, 2).multiply(MatrixLs(2, 2)));

    CHECK_NOTHROW(MatrixLs(3, 2).multiply(MatrixLs(2, 3)));
    CHECK_NOTHROW(MatrixLs(2, 2).multiply(MatrixLs(2, 2)));
    CHECK_NOTHROW(MatrixLs(3, 4).multiply(MatrixLs(2, 3)));
}

TEST_CASE("MatrixLs - swapRows") {
    MatrixLs m(3, 2);
    m.at(0, 0) = 0.0;
    m.at(0, 1) = 1.0;
    m.at(0, 2) = 2.0;
    m.at(1, 0) = 3.0;
    m.at(1, 1) = 4.0;
    m.at(1, 2) = 5.0;

    m.swapRows(0, 1);

    CHECK(m.rowCount() == 2);
    CHECK(m.colCount() == 3);
    CHECK(doctest::Approx(m.at(1, 0)) == 0.0);
    CHECK(doctest::Approx(m.at(1, 1)) == 1.0);
    CHECK(doctest::Approx(m.at(1, 2)) == 2.0);
    CHECK(doctest::Approx(m.at(0, 0)) == 3.0);
    CHECK(doctest::Approx(m.at(0, 1)) == 4.0);
    CHECK(doctest::Approx(m.at(0, 2)) == 5.0);

    CHECK_THROWS(m.swapRows(-1, 0));
    CHECK_THROWS(m.swapRows(1, -5));
    CHECK_THROWS(m.swapRows(0, 2));
    CHECK_THROWS(m.swapRows(3, 1));
}

TEST_CASE("MatrixLs - swapColumns") {
    MatrixLs m(2, 3);
    m.at(0, 0) = 0.0;
    m.at(0, 1) = 1.0;
    m.at(1, 0) = 2.0;
    m.at(1, 1) = 3.0;
    m.at(2, 0) = 4.0;
    m.at(2, 1) = 5.0;

    m.swapColumns(0, 1);

    CHECK(m.rowCount() == 3);
    CHECK(m.colCount() == 2);
    CHECK(doctest::Approx(m.at(0, 1)) == 0.0);
    CHECK(doctest::Approx(m.at(0, 0)) == 1.0);
    CHECK(doctest::Approx(m.at(1, 1)) == 2.0);
    CHECK(doctest::Approx(m.at(1, 0)) == 3.0);
    CHECK(doctest::Approx(m.at(2, 1)) == 4.0);
    CHECK(doctest::Approx(m.at(2, 0)) == 5.0);

    CHECK_THROWS(m.swapColumns(-1, 0));
    CHECK_THROWS(m.swapColumns(1, -5));
    CHECK_THROWS(m.swapColumns(0, 2));
    CHECK_THROWS(m.swapColumns(3, 1));
}
