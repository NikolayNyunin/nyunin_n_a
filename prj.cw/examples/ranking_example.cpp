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
    std::cout << "Object count: " << r1.object_count() << '\n' << std::endl;

    // Передача пустой строки в конструктор
    try {
        Ranking r2("");
    } catch (std::invalid_argument& e) {
        std::cout << "Exception in `Ranking r2(\"\");`: " << e.what() << '\n' << std::endl;
    }

    // Передача невалидного JSON в конструктор
    try {
        Ranking r3("[1,2");
    } catch (std::invalid_argument& e) {
        std::cout << "Exception in `Ranking r3(\"[1,2\");`: " << e.what() << '\n' << std::endl;
    }

//    std::string s2 = R"([["A","B"],["C","D","E"],"F","G","I",["H","J"]])";
//    Ranking r2(s2);
//    std::cout << "Ranking 2: " << r2 << std::endl;

    return 0;
}
