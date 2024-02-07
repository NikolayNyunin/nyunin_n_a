#ifndef QUEUEA_QUEUEA_H_22112021
#define QUEUEA_QUEUEA_H_22112021

#include <cstddef>


class QueueA {
public:
    QueueA() = default;
    QueueA(const QueueA& q);
    QueueA& operator=(const QueueA& rhs);
    ~QueueA();

    void push(const float value);
    void pop();
    float& top();
    const float& top() const;
    bool is_empty() const;

private:
    std::ptrdiff_t capacity_ = 0;
    std::ptrdiff_t i_head_ = -1;
    std::ptrdiff_t i_tail_ = -1;
    float* data_ = nullptr;

    void copy_from(const QueueA& q);
};

#endif // QUEUEA_QUEUEA_H_22112021
