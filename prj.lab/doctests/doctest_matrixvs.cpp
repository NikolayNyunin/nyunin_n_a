#define DOCTEST_CONFIG_IMPLEMENT_WITH_MAIN
#include <doctest/doctest.h>

#include <matrixvs/matrixvs.h>


TEST_CASE("MatrixVs - constructor") {
    MatrixVs m1;
    CHECK(m1.colCount() == 0);
    CHECK(m1.rowCount() == 0);

    MatrixVs m2(3, 4);
    CHECK(m2.colCount() == 3);
    CHECK(m2.rowCount() == 4);

    CHECK_THROWS(MatrixVs(5, 0));
    CHECK_THROWS(MatrixVs(-3, 2));
}

TEST_CASE("MatrixVs - at") {
    MatrixVs m(1, 1);
    CHECK(doctest::Approx(m.at(0, 0)) == 0.0);

    m.at(0, 0) = 5.0;
    CHECK(doctest::Approx(m.at(0, 0)) == 5.0);

    CHECK_THROWS(m.at(-1, 0));
    CHECK_THROWS(m.at(0, -5));
    CHECK_THROWS(m.at(0, 2));
    CHECK_THROWS(m.at(4, 0));
}

TEST_CASE("MatrixVs - at (const)") {
    const MatrixVs m(1, 1);
    CHECK(doctest::Approx(m.at(0, 0)) == 0.0);

    CHECK_THROWS(m.at(-1, 0));
    CHECK_THROWS(m.at(0, -5));
    CHECK_THROWS(m.at(0, 2));
    CHECK_THROWS(m.at(4, 0));
}

TEST_CASE("MatrixVs - transpose") {
    MatrixVs m(3, 2);
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

TEST_CASE("MatrixVs - multiply") {
    MatrixVs m1(4, 2);
    m1.at(0, 0) = 1.0;
    m1.at(0, 1) = -1.0;
    m1.at(0, 2) = 2.0;
    m1.at(0, 3) = -2.0;
    m1.at(1, 0) = 1.0;
    m1.at(1, 1) = 1.0;
    m1.at(1, 2) = 2.0;
    m1.at(1, 3) = 2.0;

    CHECK_NOTHROW(m1.multiply());

    MatrixVs m2(2, 4);
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

    CHECK_THROWS(MatrixVs(3, 3).multiply(MatrixVs(2, 2)));
    CHECK_THROWS(MatrixVs(3, 2).multiply(MatrixVs(3, 2)));
    CHECK_THROWS(MatrixVs(3, 2).multiply(MatrixVs(2, 2)));

    CHECK_NOTHROW(MatrixVs(3, 2).multiply(MatrixVs(2, 3)));
    CHECK_NOTHROW(MatrixVs(2, 2).multiply(MatrixVs(2, 2)));
    CHECK_NOTHROW(MatrixVs(3, 4).multiply(MatrixVs(2, 3)));
}

TEST_CASE("MatrixVs - swapRows") {
    MatrixVs m(3, 2);
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

TEST_CASE("MatrixVs - swapColumns") {
    MatrixVs m(2, 3);
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
