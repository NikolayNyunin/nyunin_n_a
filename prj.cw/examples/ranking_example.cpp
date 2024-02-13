#include <ranking/ranking.h>

#include <iostream>
#include <string>


int main() {
    // Использование конструктора по умолчанию
    Ranking r;
    std::cout << "Empty ranking: " << r << std::endl;

    // Использование конструктора, принимающего JSON-строку
    std::string s1 = R"(["A",["B","C"],"D",["E","F","G"],"H","I","J"])";
    Ranking r1(s1);
    std::cout << "Ranking 1: " << r1 << std::endl;

    std::string s2 = R"([["A","B"],["C","D","E"],"F","G","I",["H","J"]])";
    Ranking r2(s2);
    std::cout << "Ranking 2: " << r2 << std::endl;

    return 0;
}
