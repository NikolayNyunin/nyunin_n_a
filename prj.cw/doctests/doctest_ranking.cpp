#define DOCTEST_CONFIG_IMPLEMENT_WITH_MAIN

#include <doctest/doctest.h>

#include <ranking/ranking.h>

using vec_vec_str = std::vector<std::vector<std::string>>;
using vec_vec_bool = std::vector<std::vector<bool>>;
using map_str_dbl = std::map<std::string, long double>;
using vec_str = std::vector<std::string>;


TEST_CASE("Ranking - constructor") {
    SUBCASE("Ranking()") {
        CHECK_NOTHROW(Ranking());
    }

    SUBCASE("Ranking(const Ranking&)") {
        CHECK_NOTHROW(Ranking(Ranking()));
    }

    SUBCASE("Ranking(const std::string&)") {
        CHECK_THROWS(Ranking(""));
        CHECK_THROWS(Ranking("[]"));
        CHECK_THROWS(Ranking(R"({"A","B"})"));
        CHECK_THROWS(Ranking("[1,2]"));
        CHECK_THROWS(Ranking(R"(["B","C","A")"));
        CHECK_NOTHROW(Ranking(R"(["B",["C"],"A"])"));
    }

    SUBCASE("Ranking(const std::vector<std::vector<std::string>>&") {
        CHECK_THROWS(Ranking(vec_vec_str{}));
        CHECK_THROWS(Ranking(vec_vec_str{{"a","b"},{}}));
        CHECK_THROWS(Ranking(vec_vec_str{{"A"},{"A"}}));
        CHECK_NOTHROW(Ranking(vec_vec_str{{"A"},{"B"}}));
    }
}

TEST_CASE("Ranking::object_count()") {
    Ranking r1;
    CHECK((r1.object_count() == 0));

    Ranking r2(R"(["A","B"])");
    CHECK((r2.object_count() == 2));

    Ranking r3(R"(["A","B","C","D","E"])");
    CHECK((r3.object_count() == 5));

    std::stringstream strm;
    strm << R"(["X","Y","Z"])";
    strm >> r3;
    CHECK((r3.object_count() == 3));

    CHECK((Ranking(r2).object_count() == 2));
}

TEST_CASE("Ranking::matrix()") {
    Ranking r1;
    CHECK(r1.matrix().empty());

    Ranking r2(R"(["1","2"])");
    CHECK((r2.matrix() == vec_vec_bool{{1,1},{0,1}}));

    std::stringstream strm;
    strm << R"(["B","C","A"])";
    strm >> r2;
    CHECK((r2.matrix() == vec_vec_bool{{1,0,0},{1,1,1},{1,0,1}}));

    CHECK((Ranking(r2).matrix() == vec_vec_bool{{1,0,0},{1,1,1},{1,0,1}}));
}

TEST_CASE("Ranking::name_to_weight()") {
    Ranking r1;
    CHECK(r1.name_to_weight().empty());

    Ranking r2(R"(["C",["A","D"],"B","F",["E","G","H"],["I","J"]])");
    map_str_dbl map2 = {{"C",1.0},{"A",2.5},{"D",2.5},{"B",4.0},{"F",5.0},
                        {"E",7.0},{"G",7.0},{"H",7.0},{"I",9.5},{"J",9.5}};
    CHECK((r2.name_to_weight() == map2));

    CHECK((Ranking(r2).name_to_weight() == map2));
}

TEST_CASE("Ranking::object_names()") {
    Ranking r1;
    CHECK(r1.object_names().empty());

    Ranking r2(R"(["C",["A","D"],"B","F",["E","G","H"],["I","J"]])");
    vec_str v2 = {"A","B","C","D","E","F","G","H","I","J"};
    CHECK((r2.object_names() == v2));

    CHECK((Ranking(r2).object_names() == v2));
}

TEST_CASE("Ranking::operator==(const Ranking&)") {
    Ranking r1;
    Ranking r2;
    CHECK((r1 == r2));

    std::stringstream strm;
    strm << R"(["A","B","C"])";
    strm >> r1;
    strm << R"(["A","B","C"])";
    strm >> r2;
    CHECK((r1 == r2));

    const vec_vec_str v34 = {{"1"},{"2","3"}};
    Ranking r3(v34);
    Ranking r4(v34);
    CHECK((r3 == r4));

    Ranking r5(R"([["A","B"]])");
    Ranking r6(R"([["B","A"]])");
    CHECK((r5 == r6));
}

TEST_CASE("Ranking::operator!=(const Ranking&)") {
    Ranking r1;
    Ranking r2(R"(["A"])");
    CHECK((r1 != r2));

    Ranking r3(R"(["B","A"])");
    Ranking r4(R"(["A","B"])");
    CHECK((r3 != r4));
}

TEST_CASE("operator<<(std::ostream&, const Ranking&)") {
    std::ostringstream ostrm1;
    ostrm1 << Ranking();
    CHECK((ostrm1.str() == "[]"));

    std::ostringstream ostrm2;
    ostrm2 << Ranking(R"(["2","1",["3","4"]])");
    CHECK((ostrm2.str()) == R"(["2","1",["3","4"]])");
}

TEST_CASE("operator>>(std::istream&, Ranking&)") {
    Ranking r1;

    std::stringstream strm1;
    strm1 << R"(["1"])";
    CHECK_NOTHROW(strm1 >> r1);
    CHECK((r1 == Ranking(R"(["1"])")));

    std::stringstream strm2;
    strm2 << R"(["1","2","5",["4","3"]])";
    CHECK_NOTHROW(strm2 >> r1);
    CHECK((r1 == Ranking(R"(["1","2","5",["4","3"]])")));
}

TEST_CASE("calculate_contradiction_kernel(const Ranking&, const Ranking&)") {
    Ranking r1;
    Ranking r2;
    CHECK_THROWS(calculate_contradiction_kernel(r1, r2));

    Ranking r3(R"(["A","B"])");
    CHECK_THROWS(calculate_contradiction_kernel(r2, r3));

    Ranking r4(R"(["A","B"])");
    CHECK((calculate_contradiction_kernel(r3, r4).empty()));

    Ranking r5(R"([["A","B"],["C","D","E"],"F","G","I",["H","J"]])");
    Ranking r6(R"(["C",["A","D"],"B","F",["E","G","H"],["I","J"]])");
    CHECK((calculate_contradiction_kernel(r5, r6) == vec_vec_str{{"A","B","C","D"},{"E","F"},{"H","I"}}));
}

TEST_CASE("calculate_combined_ranking(const Ranking&, const Ranking&)") {
    Ranking r1;
    Ranking r2;
    CHECK_THROWS(calculate_combined_ranking(r1, r2));

    Ranking r3(R"(["A","B"])");
    CHECK_THROWS(calculate_combined_ranking(r2, r3));

    Ranking r4(R"(["A","B"])");
    CHECK((calculate_combined_ranking(r3, r4) == r4));

    Ranking r5(R"([["A","B"],["C","D","E"],"F","G","I",["H","J"]])");
    Ranking r6(R"(["C",["A","D"],"B","F",["E","G","H"],["I","J"]])");
    Ranking r7(R"([["A","B","C","D"],["E","F"],"G",["H","I"],"J"])");
    CHECK((calculate_combined_ranking(r5, r6) == r7));
}
