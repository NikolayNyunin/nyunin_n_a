#ifndef STACKL_STACKL_H_22112021
#define STACKL_STACKL_H_22112021


class StackL {
public:
    StackL() = default;
    StackL(const StackL& s);
    StackL& operator=(const StackL& rhs);
    ~StackL();

    void push(const float value);
    void pop();
    float& top();
    const float& top() const;
    bool is_empty() const;

private:
    struct Node {
        float value = 0.0f;
        Node* next = nullptr;
        Node(const float v = 0.0f) : value(v) {}
    };

private:
    Node* head_ = nullptr;

    void copy_from(const StackL& s);
    void delete_list();
};

#endif // STACKL_STACKL_H_22112021
