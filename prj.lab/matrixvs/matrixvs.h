#ifndef MATRIXVS_MATRIXVS_H_08112021
#define MATRIXVS_MATRIXVS_H_08112021

#include <iosfwd>
#include <vector>


//! \brief Матрица float значений, реализация при помощи приведенного индекса.
class MatrixVs {
public:
    MatrixVs() = default;
    MatrixVs(const MatrixVs&) = default;
    ~MatrixVs() = default;
    MatrixVs& operator=(const MatrixVs&) = default;

    MatrixVs(const std::ptrdiff_t col_count, const std::ptrdiff_t row_count);

    std::ptrdiff_t rowCount() const noexcept { return n_row_; }
    std::ptrdiff_t colCount() const noexcept { return n_col_; }

    float& at(const std::ptrdiff_t i_row, const std::ptrdiff_t i_col);
    float at(const std::ptrdiff_t i_row, const std::ptrdiff_t i_col) const;
    MatrixVs& transpose() noexcept;
    MatrixVs& multiply();
    MatrixVs& multiply(MatrixVs& matrix);
    void swapRows(const std::ptrdiff_t i_first, const std::ptrdiff_t i_second);
    void swapColumns(const std::ptrdiff_t i_first, const std::ptrdiff_t i_second);

private:
    std::ptrdiff_t n_row_ = 0;
    std::ptrdiff_t n_col_ = 0;
    std::vector<float> data_;
};

#endif // MATRIXVS_MATRIXVS_H_08112021
