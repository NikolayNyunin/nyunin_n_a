#include <ranking/ranking.h>

using json = nlohmann::json;


Ranking::Ranking(const std::string& ranking_string) {
    std::stringstream istrm;
    istrm << ranking_string;
    read_from(istrm);
}

std::ostream& Ranking::write_to(std::ostream &ostrm) const {
    if (j_.empty())  // Если JSON-объект пустой
        ostrm << left_bracket << right_bracket;
    else
        ostrm << j_.dump();

    return ostrm;
}

std::istream& Ranking::read_from(std::istream &istrm) {
    try {
        istrm >> j_;  // Парсинг объекта JSON из потока ввода
    } catch (json::parse_error& e) {
        throw std::invalid_argument(e.what());
    }

    if (!j_.is_array())  // Полученный на вход JSON-объект не является массивом
        throw std::invalid_argument("The input stream does not contain a JSON array.");

    // Заполнение словаря весов носителей в ранжировке
    w_.clear();
    long double weight = 1.0;  // Вес носителя
    for (const auto& value : j_) {
        if (value.is_array()) {  // Если элемент является кластером носителей (массивом)
            if (value.empty())  // Если массив пустой
                throw std::invalid_argument("The JSON array is empty.");
            const long double cluster_weight = weight + (value.size() - (long double)1) / 2;  // Вес элементов кластера
            for (const auto& child_value : value) {
                if (!child_value.is_string())  // Если элемент в массиве не является строкой
                    throw std::invalid_argument("The JSON array element is not a string.");
                w_[child_value] = cluster_weight;  // Запись веса носителя
            }
            weight += value.size();  // Увеличение переменной веса носителя
        } else if (value.is_string()) {  // Если элемент является отдельным носителем
            w_[value] = weight;  // Запись веса носителя
            weight++;  // Увеличение переменной веса носителя
        } else {
            throw std::invalid_argument("The JSON array element is not a string.");
        }
    }

    // Заполнения вектора названий носителей
    k_.clear();
    for (const auto& [key, value] : w_)
        k_.push_back(key);

    // Заполнение матричного представления ранжировки
    n_ = w_.size();  // Запись числа носителей в ранжировке
    y_.assign(n_, std::vector<bool>(n_, false));
    for (int i = 0; i < n_; i++) {
        for (int j = 0; j < n_; j++) {
            if (w_[k_[i]] <= w_[k_[j]])
                y_[i][j] = true;
        }
    }

    return istrm;
}

std::ostream& operator<<(std::ostream& ostrm, const Ranking& r) {
    return r.write_to(ostrm);
}

std::istream& operator>>(std::istream& istrm, Ranking& r) {
    return r.read_from(istrm);
}
