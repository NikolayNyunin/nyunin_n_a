#include <arrayd/arrayd.h>

#include <algorithm>
#include <stdexcept>


ArrayD::ArrayD(const ArrayD& arr) {
    size_ = arr.size_;
    capacity_ = size_;
    if (size_ != 0)
        data_ = new float[size_];
    for (int i = 0; i < size_; i++)
        data_[i] = arr[i];
}

ArrayD::ArrayD(const std::ptrdiff_t size) {
    if (size < 0)
        throw std::logic_error("Size cannot be less than 0");
    size_ = size;
    capacity_ = size;
    if (size != 0)
        data_ = new float[size];
    for (int i = 0; i < size; i++)
        data_[i] = float();
}

ArrayD& ArrayD::operator=(const ArrayD& rhs) {
    resize(rhs.size_);
    for (int i = 0; i < size_; i++)
        data_[i] = rhs[i];
    return *this;
}

float& ArrayD::operator[](const std::ptrdiff_t i) {
    if (i < 0 || i >= size_)
        throw std::out_of_range("Index out of range");
    return data_[i];
}

const float& ArrayD::operator[](const std::ptrdiff_t i) const {
    if (i < 0 || i >= size_)
        throw std::out_of_range("Index out of range");
    return data_[i];
}

void ArrayD::resize(const std::ptrdiff_t size) {
    if (size < 0)
        throw std::logic_error("Size cannot be less than 0");
    if (size > capacity_) {
        capacity_ = std::max(size, size_ * 2);
        float* new_data = new float[capacity_];
        for (int i = 0; i < size_; i++)
            new_data[i] = data_[i];
        for (int i = size_; i < capacity_; i++)
            new_data[i] = float();
        delete[] data_;
        data_ = new_data;
    } else {
        for (int i = size; i < capacity_; i++)
            data_[i] = float();
    }

    size_ = size;
}
