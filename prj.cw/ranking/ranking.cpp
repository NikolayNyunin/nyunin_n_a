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

std::vector<std::set<std::string>> calculate_contradiction_kernel(const Ranking& r1, const Ranking& r2) {
    if (r1.object_names() != r2.object_names())  // Если у ранжировок разные списки носителей
        throw std::invalid_argument("The rankings have different sets of objects.");
    else if (r1.object_count() == 0)  // Если ранжировки пусты
        throw std::invalid_argument("The rankings are empty.");

    const unsigned long long n = r1.object_count();  // Число носителей в ранжировках
    const auto& y1 = r1.matrix();  // Матрица первой ранжировки
    const auto& y2 = r2.matrix();  // Матрица второй ранжировки

    // Вычисление Y_12 = Y_1 && Y_2
    std::vector<std::vector<bool>> y12(n, std::vector<bool>(n, false));
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++)
            y12[i][j] = y1[i][j] && y2[i][j];
    }

    // Вычисление Y'_12 = (Y_12)^T
    std::vector<std::vector<bool>> y12_t(n, std::vector<bool>(n, false));
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++)
            y12_t[i][j] = y12[j][i];
    }

    // Вычисление матрицы противоречий Y = Y_12 || Y'_12
    std::vector<std::vector<bool>> y(n, std::vector<bool>(n, false));
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++)
            y[i][j] = y12[i][j] || y12_t[i][j];
    }

    // Вектор из имён носителей в ранжировках
    const auto& k = r1.object_names();

    // Вычисление ядра противоречий
    std::vector<std::set<std::string>> kernel;
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) {
            if (!y[i][j]) {
                if (kernel.empty())  // Если ядро противоречий пока пусто
                    kernel.push_back(std::set<std::string>{k[i], k[j]});
                else {
                    bool found = false;  // Найден ли существующий кластер с нужным носителем
                    for (auto& cluster : kernel) {
                        if (cluster.contains(k[i])) {
                            cluster.insert(k[j]);
                            found = true;
                            break;
                        } else if (cluster.contains(k[j])) {
                            cluster.insert(k[i]);
                            found = true;
                            break;
                        }
                    }
                    if (!found)  // Существующий кластер не найден
                        kernel.push_back(std::set<std::string>{k[i], k[j]});
                }
            }
        }
    }

    return kernel;
}
