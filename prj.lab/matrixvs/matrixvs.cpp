#include <matrixvs/matrixvs.h>

#include <stdexcept>


MatrixVs::MatrixVs(const std::ptrdiff_t col_count, const std::ptrdiff_t row_count) {
    if (col_count <= 0 || row_count <= 0)
        throw std::logic_error("Matrix dimensions cannot be 0 or less");
    n_row_ = row_count;
    n_col_ = col_count;
    data_.resize(row_count * col_count);
}

float& MatrixVs::at(const std::ptrdiff_t i_row, const std::ptrdiff_t i_col) {
    if (i_row < 0 || i_row >= n_row_ || i_col < 0 || i_col >= n_col_)
        throw std::out_of_range("Index out of range");
    return data_[i_row * n_col_ + i_col];
}

float MatrixVs::at(const std::ptrdiff_t i_row, const std::ptrdiff_t i_col) const {
    if (i_row < 0 || i_row >= n_row_ || i_col < 0 || i_col >= n_col_)
        throw std::out_of_range("Index out of range");
    return data_[i_row * n_col_ + i_col];
}

MatrixVs& MatrixVs::transpose() noexcept {
    std::vector<float> new_data(n_row_ * n_col_);
    for (std::ptrdiff_t i = 0; i < n_row_; i++) {
        for (std::ptrdiff_t j = 0; j < n_col_; j++)
            new_data[j * n_row_ + i] = at(i, j);
    }
    std::swap(n_row_, n_col_);
    data_ = new_data;
    return *this;
}

MatrixVs& MatrixVs::multiply() {
    return *this;
}

MatrixVs& MatrixVs::multiply(MatrixVs& matrix) {
    if (n_col_ != matrix.n_row_)
        throw std::logic_error("Incorrect matrix dimensions for multiplication");
    std::vector<float> new_data(n_row_ * matrix.n_col_);
    for (int i = 0; i < n_row_; i++) {
        for (int j = 0; j < matrix.n_col_; j++) {
            for (int k = 0; k < n_col_; k++)
                new_data[i * matrix.n_col_ + j] += at(i, k) * matrix.at(k, j);
        }
    }
    n_col_ = matrix.n_col_;
    data_ = new_data;
    return *this;
}

void MatrixVs::swapRows(const std::ptrdiff_t i_first, const std::ptrdiff_t i_second) {
    if (i_first < 0 || i_first >= n_row_ || i_second < 0 || i_second >= n_row_)
        throw std::out_of_range("Index out of range");
    for (std::ptrdiff_t col = 0; col < n_col_; col++)
        std::swap(at(i_first, col), at(i_second, col));
}

void MatrixVs::swapColumns(const std::ptrdiff_t i_first, const std::ptrdiff_t i_second) {
    if (i_first < 0 || i_first >= n_col_ || i_second < 0 || i_second >= n_col_)
        throw std::out_of_range("Index out of range");
    for (std::ptrdiff_t row = 0; row < n_row_; row++)
        std::swap(at(row, i_first), at(row, i_second));
}
