#include <matrixds/matrixds.h>

#include <stdexcept>


MatrixDs::MatrixDs(const std::ptrdiff_t col_count, const std::ptrdiff_t row_count) {
    if (col_count <= 0 || row_count <= 0)
        throw std::logic_error("Matrix dimensions cannot be 0 or less");
    n_row_ = row_count;
    n_col_ = col_count;
    data_.resize(row_count);
    for (std::ptrdiff_t i = 0; i < row_count; i++)
        data_[i].resize(col_count);
}

float& MatrixDs::at(const std::ptrdiff_t i_row, const std::ptrdiff_t i_col) {
    if (i_row < 0 || i_row >= n_row_ || i_col < 0 || i_col >= n_col_)
        throw std::out_of_range("Index out of range");
    return data_[i_row][i_col];
}

float MatrixDs::at(const std::ptrdiff_t i_row, const std::ptrdiff_t i_col) const {
    if (i_row < 0 || i_row >= n_row_ || i_col < 0 || i_col >= n_col_)
        throw std::out_of_range("Index out of range");
    return data_[i_row][i_col];
}

MatrixDs& MatrixDs::transpose() noexcept {
    std::vector<std::vector<float>> new_data(n_col_, std::vector<float> (n_row_));
    for (std::ptrdiff_t i = 0; i < n_row_; i++) {
        for (std::ptrdiff_t j = 0; j < n_col_; j++)
            new_data[j][i] = at(i, j);
    }
    std::swap(n_row_, n_col_);
    data_ = new_data;
    return *this;
}

MatrixDs& MatrixDs::multiply() {
    return *this;
}

MatrixDs& MatrixDs::multiply(MatrixDs& matrix) {
    if (n_col_ != matrix.n_row_)
        throw std::logic_error("Incorrect matrix dimensions for multiplication");
    std::vector<std::vector<float>> new_data(n_row_, std::vector<float>(matrix.n_col_));
    for (int i = 0; i < n_row_; i++) {
        for (int j = 0; j < matrix.n_col_; j++) {
            for (int k = 0; k < n_col_; k++)
                new_data[i][j] += at(i, k) * matrix.at(k, j);
        }
    }
    n_col_ = matrix.n_col_;
    data_ = new_data;
    return *this;
}

void MatrixDs::swapRows(const std::ptrdiff_t i_first, const std::ptrdiff_t i_second) {
    if (i_first < 0 || i_first >= n_row_ || i_second < 0 || i_second >= n_row_)
        throw std::out_of_range("Index out of range");
    for (std::ptrdiff_t col = 0; col < n_col_; col++)
        std::swap(at(i_first, col), at(i_second, col));
}

void MatrixDs::swapColumns(const std::ptrdiff_t i_first, const std::ptrdiff_t i_second) {
    if (i_first < 0 || i_first >= n_col_ || i_second < 0 || i_second >= n_col_)
        throw std::out_of_range("Index out of range");
    for (std::ptrdiff_t row = 0; row < n_row_; row++)
        std::swap(at(row, i_first), at(row, i_second));
}
