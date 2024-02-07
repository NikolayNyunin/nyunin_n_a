#include <matrixls/matrixls.h>

#include <stdexcept>


MatrixLs::MatrixLs(const std::ptrdiff_t col_count, const std::ptrdiff_t row_count) {
    if (col_count <= 0 || row_count <= 0)
        throw std::logic_error("Matrix dimensions cannot be 0 or less");
    n_row_ = row_count;
    n_col_ = col_count;
    data_.resize(row_count * col_count);
    indexes_.resize(row_count);
    for (std::ptrdiff_t i = 0; i < row_count; i++)
        indexes_[i] = i * col_count;
}

float& MatrixLs::at(const std::ptrdiff_t i_row, const std::ptrdiff_t i_col) {
    if (i_row < 0 || i_row >= n_row_ || i_col < 0 || i_col >= n_col_)
        throw std::out_of_range("Index out of range");
    return data_[indexes_[i_row] + i_col];
}

float MatrixLs::at(const std::ptrdiff_t i_row, const std::ptrdiff_t i_col) const {
    if (i_row < 0 || i_row >= n_row_ || i_col < 0 || i_col >= n_col_)
        throw std::out_of_range("Index out of range");
    return data_[indexes_[i_row] + i_col];
}

MatrixLs& MatrixLs::transpose() noexcept {
    std::vector<float> new_data(n_row_ * n_col_);
    for (std::ptrdiff_t i = 0; i < n_row_; i++) {
        for (std::ptrdiff_t j = 0; j < n_col_; j++)
            new_data[j * n_row_ + i] = at(i, j);
    }
    std::swap(n_row_, n_col_);
    data_ = new_data;
    indexes_.resize(n_row_);
    for (int i = 0; i < n_row_; i++)
        indexes_[i] = i * n_col_;
    return *this;
}

MatrixLs& MatrixLs::multiply() {
    return *this;
}

MatrixLs& MatrixLs::multiply(MatrixLs& matrix) {
    if (n_col_ != matrix.n_row_)
        throw std::logic_error("Incorrect matrix dimensions for multiplication");
    std::vector<float> new_data(n_row_ * matrix.n_col_);
    std::vector<std::ptrdiff_t> new_indexes(n_row_);
    for (std::ptrdiff_t i = 0; i < n_row_; i++)
        new_indexes[i] = i * matrix.n_col_;
    for (int i = 0; i < n_row_; i++) {
        for (int j = 0; j < matrix.n_col_; j++) {
            for (int k = 0; k < n_col_; k++)
                new_data[new_indexes[i] + j] += at(i, k) * matrix.at(k, j);
        }
    }
    n_col_ = matrix.n_col_;
    data_ = new_data;
    indexes_ = new_indexes;
    return *this;
}

void MatrixLs::swapRows(const std::ptrdiff_t i_first, const std::ptrdiff_t i_second) {
    if (i_first < 0 || i_first >= n_row_ || i_second < 0 || i_second >= n_row_)
        throw std::out_of_range("Index out of range");
    std::swap(indexes_[i_first], indexes_[i_second]);
}

void MatrixLs::swapColumns(const std::ptrdiff_t i_first, const std::ptrdiff_t i_second) {
    if (i_first < 0 || i_first >= n_col_ || i_second < 0 || i_second >= n_col_)
        throw std::out_of_range("Index out of range");
    for (std::ptrdiff_t row = 0; row < n_row_; row++)
        std::swap(at(row, i_first), at(row, i_second));
}
