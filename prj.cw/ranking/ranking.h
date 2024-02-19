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
    Ranking(const Ranking& other) = default;  /**< Конструктор копирования. */
    Ranking& operator=(const Ranking& other) = default;  /**< Оператор присваивания. */
    ~Ranking() = default;  /**< Деструктор. */
    Ranking(Ranking&& other) = default;  /**< Конструктор перемещения. */
    Ranking& operator=(Ranking&& other) = default;  /**< Оператор перемещения. */

    //! @brief Конструктор от JSON-строки.
    //! @param ranking_string - Строка формата JSON с описанием ранжировки.
    //! @throw std::invalid_argument - Неправильный формат строки.
    explicit Ranking(const std::string& ranking_string);

    //! @brief Конструктор от вектора.
    //! @param ranking_vector - Вектор с описанием ранжировки.
    //! @throw std::invalid_argument - Неправильный формат вектора.
    explicit Ranking(const std::vector<std::vector<std::string>>& ranking_vector);

    //! @brief Метод для получения числа носителей в ранжировке.
    //! @return Число носителей в ранжировке.
    [[nodiscard]] unsigned long long object_count() const noexcept { return n_; }

    //! @brief Метод для получения матрицы ранжировки.
    //! @return Двоичная матрица ранжировки.
    [[nodiscard]] std::vector<std::vector<bool>> matrix() const noexcept { return y_; }

    //! @brief Метод для получения словаря соответствия имён и весов носителей.
    //! @return Словарь (std::map) вида {{`имя_носителя_1`, `вес_носителя_1`}, ...}.
    [[nodiscard]] std::map<std::string, long double> name_to_weight() const noexcept { return w_; }

    //! @brief Метод для получения вектора имён носителей.
    //! @return Вектор (std::vector) вида {`имя_носителя_1`, `имя_носителя_2`, ...}.
    [[nodiscard]] std::vector<std::string> object_names() const noexcept { return k_; }

    //! @brief Оператор сравнения.
    //! @param other - Другая ранжировка.
    //! @return `true` если ранжировки эквивалентны, иначе - `false`.
    bool operator==(const Ranking& other) const noexcept { return w_ == other.w_; }

    //! @brief Оператор сравнения.
    //! @param other - Другая ранжировка.
    //! @return `true` если ранжировки не эквивалентны, иначе - `false`.
    bool operator!=(const Ranking& other) const noexcept { return !operator==(other); }

    //! @brief Метод для записи ранжировки в поток.
    //! @param ostrm - Поток вывода.
    std::ostream& write_to(std::ostream& ostrm) const;

    //! @brief Метод для чтения ранжировки из потока.
    //! @param istrm - Поток ввода.
    //! @throw std::invalid_argument - Неправильный формат ранжировки во входном потоке.
    std::istream& read_from(std::istream& istrm);

private:
    unsigned long long n_{0};  /**< Число носителей в ранжировке. */
    std::vector<std::vector<bool>> y_;  /**< Двоичная матрица, описывающая ранжировку. */
    std::map<std::string, long double> w_;  /**< Веса носителей в ранжировке. */
    std::vector<std::string> k_;  /**< Строковые обозначения носителей. */
    nlohmann::json j_;  /**< Представление ранжировки в формате JSON. */

    static const char left_bracket{'['};
    static const char right_bracket{']'};
};

std::ostream& operator<<(std::ostream& ostrm, const Ranking& r);
std::istream& operator>>(std::istream& istrm, Ranking& r);

//! @brief Функция для вычисления ядра противоречий.
//!
//! Ядром противоречий для ранжировок называется множество кластеров носителей, для которых возникли противоречия
//! в ранжировках, и которые стали неразличимыми по степени выраженности рассматриваемых признаков.
//! @param r1 - Первая ранжировка.
//! @param r2 - Вторая ранжировка.
//! @return Вектор, содержащий ядро противоречий для ранжировок `r1` и `r2`.
//! @throw std::invalid_argument - Предоставленные ранжировки имеют различные списки носителей.
std::vector<std::vector<std::string>> calculate_contradiction_kernel(const Ranking& r1, const Ranking& r2);

//! @brief Вспомогательная функция для сравнения значений двух ключей в двух словарях.
//! @param key1 - Первый ключ.
//! @param key2 - Второй ключ.
//! @param map1 - Первый словарь.
//! @param map2 - Второй словарь.
//! @return -1, 0 или 1 в зависимости от результата сравнения.
int compare_keys(const std::string& key1, const std::string& key2,
                 const std::map<std::string, long double>& map1,
                 const std::map<std::string, long double>& map2) noexcept;

//! @brief Функция для вычисления согласованной ранжировки.
//!
//! Согласованной ранжировкой для заданных ранжировок называется такая ранжировка,
//! в которой носители упорядочены с учётом сразу всех рассматриваемых признаков.
//! @param r1 - Первая ранжировка.
//! @param r2 - Вторая ранжировка.
//! @return Согласованная ранжировка - экземпляр класса Ranking.
//! @throw std::invalid_argument - Предоставленные ранжировки имеют различные списки носителей.
Ranking calculate_combined_ranking(const Ranking& r1, const Ranking& r2);

#endif  // RANKING_RANKING_H_08022024
