#include <stackl/stackl.h>

#include <stdexcept>


StackL::StackL(const StackL& s) {
    copy_from(s);
}

StackL& StackL::operator=(const StackL& rhs) {
    if (this == &rhs)
        return *this;
    delete_list();
    copy_from(rhs);
    return *this;
}

StackL::~StackL() {
    delete_list();
}

void StackL::push(const float value) {
    Node* new_head = new Node(value);
    new_head->next = head_;
    head_ = new_head;
}

void StackL::pop() {
    if (!is_empty()) {
        Node* old_head = head_;
        head_ = old_head->next;
        delete old_head;
    }
}

float& StackL::top() {
    if (is_empty())
        throw std::runtime_error("Stack is empty");
    return head_->value;
}

const float& StackL::top() const {
    if (is_empty())
        throw std::runtime_error("Stack is empty");
    return head_->value;
}

bool StackL::is_empty() const {
    return (head_ == nullptr);
}

void StackL::copy_from(const StackL& s) {
    Node* s_node = s.head_;
    Node* old_node = nullptr;
    while (s_node != nullptr) {
        Node* new_node = new Node(s_node->value);
        if (old_node == nullptr) {
            head_ = new_node;
            old_node = head_;
        } else {
            old_node->next = new_node;
            old_node = new_node;
        }
        s_node = s_node->next;
    }
}

void StackL::delete_list() {
    while (!is_empty())
        pop();
}
