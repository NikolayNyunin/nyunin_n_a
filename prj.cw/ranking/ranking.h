#ifndef RANKING_RANKING_H_08022024
#define RANKING_RANKING_H_08022024

#include <nlohmann/json.hpp>

#include <map>
#include <string>
#include <vector>


//! @brief Класс, описывающий ранжировку.
class Ranking {
public:
    Ranking() = default;  /**< Конструктор по умолчанию. */
    Ranking(const Ranking&) = default;  /**< Конструктор копирования. */
    Ranking& operator=(const Ranking&) = default;  /**< Оператор присваивания. */
    ~Ranking() = default;  /**< Деструктор. */

    //! @brief Конструктор от JSON-строки.
    //! @param ranking_string - Строка формата JSON с описанием ранжировки.
    explicit Ranking(const std::string& ranking_string);

    //! @brief Метод для получения числа носителей в ранжировке.
    //! @return Число носителей в ранжировке.
    int object_count() const noexcept { return n_; }

    //! @brief Метод для получения матрицы ранжировки.
    //! @return Двоичная матрица ранжировки.
    std::vector<std::vector<bool>> matrix() const noexcept { return y_; }

    //! @brief Метод для получения словаря соответствия имён и весов носителей.
    //! @return Словарь (std::map) вида {{`имя_носителя_1`, `вес_носителя_1`}, ...}.
    std::map<std::string, double> name_to_weight() const noexcept { return w_; }

    //! @brief Метод для получения словаря соответствия индексов и имён носителей.
    //! @return Словарь (std::map) вида {{`индекс_носителя_1`, `имя_носителя_1`}, ...}.
    std::map<int, std::string> index_to_name() const noexcept { return k_; }

    //! @brief Метод для записи ранжировки в поток.
    //! @param ostrm - Поток вывода.
    std::ostream& write_to(std::ostream& ostrm) const;

    //! @brief Метод для чтения ранжировки из потока.
    //! @param istrm - Поток ввода.
    std::istream& read_from(std::istream& istrm);

private:
    int n_{0};  /**< Число носителей в ранжировке. */
    std::vector<std::vector<bool>> y_;  /**< Двоичная матрица, описывающая ранжировку. */
    std::map<std::string, double> w_;  /**< Веса носителей в ранжировке. */
    std::map<int, std::string> k_;  /**< Строковые обозначения носителей. */
    nlohmann::json j_;  /**< Представление ранжировки в формате JSON. */

    static const char left_bracket{'['};
    static const char right_bracket{']'};
};

std::ostream& operator<<(std::ostream& ostrm, const Ranking& r);
std::istream& operator>>(std::istream& istrm, Ranking& r);

#endif  // RANKING_RANKING_H_08022024
