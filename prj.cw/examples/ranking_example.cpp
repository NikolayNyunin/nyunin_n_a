#include <ranking/ranking.h>

#include <iostream>
#include <string>


int main() {
    // Использование конструктора по умолчанию
    Ranking r0;
    std::cout << "Empty ranking: " << r0 << std::endl;  // Пустая ранжировка
    std::cout << "Object count: " << r0.object_count() << '\n' << std::endl;  // Число носителей: 0

    // Чтение ранжировки из потока
    std::stringstream strm;
    strm << R"(["C","A","B"])";
    strm >> r0;
    std::cout << "Ranking 0: " << r0 << std::endl;  // Строковое представление ранжировки
    std::cout << "Object count: " << r0.object_count() << '\n' << std::endl;  // Число носителей: 3

    // Использование конструктора, принимающего JSON-строку
    const std::string s1 = R"(["C",["A","D"],"B","F",["E","G","H"],["I","J"]])";
    Ranking r1(s1);
    std::cout << "Ranking 1: " << r1 << '\n' << std::endl;  // Строковое представление ранжировки

    // Использование конструктора, принимающего вектор
    const std::vector<std::vector<std::string>> v2 = {{"C"},{"A","D"},{"B"},{"F"},{"E","G","H"},{"I","J"}};
    Ranking r2(v2);

    // Получение строкового представления ранжировки
    std::cout << "Ranking 2: " << r2 << '\n' << std::endl;

    // Использование операторов сравнения
    if (r1 == r2)
        std::cout << "Ranking 1 == Ranking 2" << '\n' << std::endl;
    else if (r1 != r2)
        std::cout << "Ranking 1 != Ranking 2" << '\n' << std::endl;

    // Получение числа носителей в ранжировке
    std::cout << "Object count: " << r2.object_count() << '\n' << std::endl;

    // Получение обозначений носителей в ранжировке
    const auto& names = r2.object_names();
    std::cout << "Object names:\t";
    for (const auto& name : names)
        std::cout << name << '\t';
    std::cout << std::endl;

    // Получение весов носителей в ранжировке
    const auto& weights = r1.name_to_weight();
    std::cout << "Object weights:\t";
    for (const auto& [name, weight] : weights)
        std::cout << weight << '\t';
    std::cout << '\n' << std::endl;

    // Получение бинарной матрицы ранжировки
    const auto& matrix = r1.matrix();
    std::cout << "Ranking matrix:\n";
    for (const auto& row : matrix) {
        for (const auto& element : row)
            std::cout << element << "  ";
        std::cout << '\n';
    }
    std::cout << std::endl;

    // Инициализация ещё одной ранжировки, не равной r1 и r2
    const std::string s3 = R"([["A","B"],["C","D","E"],"F","G","I",["H","J"]])";
    Ranking r3(s3);
    std::cout << "Ranking 3: " << r2 << '\n' << std::endl;

    // Нахождение ядра противоречий между r2 и r3
    const auto& kernel = calculate_contradiction_kernel(r2, r3);
    std::cout << "Contradiction kernel: [ ";
    for (const auto& cluster : kernel) {
        std::cout << '[' << ' ';
        for (const auto& object : cluster)
            std::cout << '"' << object << '"' << ' ';
        std::cout << ']' << ' ';
    }
    std::cout << ']' << '\n' << std::endl;

    // Нахождение согласованной ранжировки для r2 и r3
    const Ranking combined = calculate_combined_ranking(r2, r3);
    std::cout << "Combined ranking: " << combined << '\n' << std::endl;

    // ВОЗМОЖНЫЕ ОШИБКИ
    // Передача пустой строки в конструктор
    try {
        Ranking r4("");
    } catch (std::invalid_argument& e) {
        std::cout << "r4 -> std::invalid_argument: " << e.what() << '\n' << std::endl;
    }

    // Передача вектора с пустыми элементами в конструктор
    try {
        const std::vector<std::vector<std::string>> v5 = {{"obj1","obj2"},{},{"obj3"},{}};
        Ranking r5(v5);
    } catch (std::invalid_argument& e) {
        std::cout << "r5 -> std::invalid_argument: " << e.what() << '\n' << std::endl;
    }

    // Передача невалидного JSON в конструктор
    try {
        Ranking r6(R"([["1"],["2"])");
    } catch (std::invalid_argument& e) {
        std::cout << "r6 -> std::invalid_argument: " << e.what() << '\n' << std::endl;
    }

    Ranking r7(R"(["a","b"])");
    Ranking r8(R"(["A","B"])");

    // Передача ранжировок с разными списками объектов в функцию нахождения ядра противоречий
    try {
        calculate_contradiction_kernel(r7, r8);
    } catch (std::invalid_argument& e) {
        std::cout << "r7, r8 -> std::invalid_argument: " << e.what() << '\n' << std::endl;
    }

    // Передача ранжировок с разными списками объектов в функцию нахождения согласованной ранжировки
    try {
        calculate_combined_ranking(r7, r8);
    } catch (std::invalid_argument& e) {
        std::cout << "r7, r8 -> std::invalid_argument: " << e.what() << '\n' << std::endl;
    }

    return 0;
}
