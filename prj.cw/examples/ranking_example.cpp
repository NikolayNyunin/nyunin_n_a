#include <ranking/ranking.h>

#include <iostream>
#include <string>


int main() {
    // Использование конструктора по умолчанию
    Ranking r0;
    std::cout << "Empty ranking: " << r0 << std::endl;
    std::cout << "Object count: " << r0.object_count() << '\n' << std::endl;

    // Использование конструктора, принимающего JSON-строку
    std::string s1 = R"(["A",["B","C"],"D",["E","F","G"],"H","I","J"])";
    Ranking r1(s1);
    std::cout << "Ranking 1: " << r1 << std::endl;
    std::cout << "Object count: " << r1.object_count() << std::endl;

    const auto& names = r1.object_names();
    std::cout << "Object names:\t";
    for (const auto& name : names)
        std::cout << name << '\t';
    std::cout << std::endl;

    const auto& weights = r1.name_to_weight();
    std::cout << "Object weights:\t";
    for (const auto& [name, weight] : weights)
        std::cout << weight << '\t';
    std::cout << std::endl;

    const auto& matrix = r1.matrix();
    std::cout << "Ranking matrix:\n";
    for (const auto& row : matrix) {
        for (const auto& element : row)
            std::cout << element << ' ';
        std::cout << '\n';
    }
    std::cout << std::endl;

    std::string s2 = R"([["A","B"],["C","D","E"],"F","G","I",["H","J"]])";
    Ranking r2(s2);
    std::cout << "Ranking 2: " << r2 << '\n' << std::endl;

    const auto& kernel = calculate_contradiction_kernel(r1, r2);
    std::cout << "Contradiction kernel: ";
    for (const auto& cluster : kernel) {
        std::cout << '[' << ' ';
        for (const auto& object : cluster)
            std::cout << '"' << object << '"' << ' ';
        std::cout << ']' << ' ';
    }
    std::cout << '\n' << std::endl;

    const Ranking combined = calculate_combined_ranking(r1, r2);
    std::cout << "Combined ranking: " << combined << '\n' << std::endl;

    // Передача пустой строки в конструктор
    try {
        Ranking r3("");
    } catch (std::invalid_argument& e) {
        std::cout << "Exception in `Ranking r3(\"\");`: " << e.what() << '\n' << std::endl;
    }

    // Передача невалидного JSON в конструктор
    try {
        Ranking r4("[1,2");
    } catch (std::invalid_argument& e) {
        std::cout << "Exception in `Ranking r4(\"[1,2\");`: " << e.what() << '\n' << std::endl;
    }

    return 0;
}
