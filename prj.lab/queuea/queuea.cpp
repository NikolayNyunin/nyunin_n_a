#include <queuea/queuea.h>

#include <stdexcept>


QueueA::QueueA(const QueueA& q) {
    copy_from(q);
}

QueueA& QueueA::operator=(const QueueA& rhs) {
    if (this == &rhs)
        return *this;
    delete[] data_;
    copy_from(rhs);
    return *this;
}

QueueA::~QueueA() {
    delete[] data_;
}

void QueueA::push(const float value) {
    if (data_ == nullptr) {
        capacity_ = 10;
        data_ = new float[capacity_];
    }
    if (is_empty())
        i_head_++;
    i_tail_++;
    if (i_tail_ >= capacity_) {
        if (i_tail_ - i_head_ + 1 <= capacity_ / 2) {
            for (std::ptrdiff_t i = i_head_; i <= i_tail_; i++)
                data_[i - i_head_] = data_[i];
            i_tail_ -= i_head_;
            i_head_ = 0;
        }
        else {
            capacity_ = 2 * (i_tail_ - i_head_ + 1);
            float* new_data = new float[capacity_];
            for (std::ptrdiff_t i = i_head_; i <= i_tail_; i++)
                new_data[i - i_head_] = data_[i];
            i_head_ = 0;
            i_tail_ = (capacity_ / 2) - 1;
            delete[] data_;
            data_ = new_data;
        }
    }
    data_[i_tail_] = value;
}

void QueueA::pop() {
    if (!is_empty()) {
        i_head_++;
        if (is_empty()) {
            i_head_ = -1;
            i_tail_ = -1;
        }
    }
}

float& QueueA::top() {
    if (is_empty())
        throw std::runtime_error("Queue is empty");
    return data_[i_head_];
}

const float& QueueA::top() const {
    if (is_empty())
        throw std::runtime_error("Queue is empty");
    return data_[i_head_];
}

bool QueueA::is_empty() const {
    return (i_tail_ - i_head_ == -1 || i_head_ == -1);
}

void QueueA::copy_from(const QueueA& q) {
    if (q.is_empty()) {
        capacity_ = 0;
        i_head_ = -1;
        i_tail_ = -1;
        data_ = nullptr;
    }
    else {
        capacity_ = 2 * (q.i_tail_ - q.i_head_ + 1);
        data_ = new float[capacity_];
        for (std::ptrdiff_t i = q.i_head_; i <= q.i_tail_; i++)
            data_[i - q.i_head_] = q.data_[i];
        i_head_ = 0;
        i_tail_ = (capacity_ / 2) - 1;
    }
}
