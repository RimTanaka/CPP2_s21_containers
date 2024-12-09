#ifndef S21_STACK_H_
#define S21_STACK_H_

#include <cstddef>
#include <initializer_list>
#include <iostream>
#include <stdexcept>

namespace s21 {
template <typename T>
class Stack {
 public:
  using value_type = T;           // тип
  using reference = value_type&;  // ссылка на объект типа
  using const_reference =
      const value_type&;  // ссылка на неизменяемый объект типа
  using size_type = std::size_t;  // беззнаковый тип

  Stack() : head_(nullptr), size_(0) {}

  Stack(std::initializer_list<value_type> const& items)
      : head_(nullptr), size_(0) {
    for (const auto& item : items) {
      Push(item);
    }
  }

  Stack(const Stack& s) {
    if (s.head_ == nullptr) {
      head_ = nullptr;
      size_ = 0;
    } else {
      head_ = new Node(*s.head_);
      size_ = s.size_;

      Node* current = head_;
      Node* s_current = s.head_->next;

      while (s_current != nullptr) {
        current->next = new Node(*s_current);
        current = current->next;
        s_current = s_current->next;
      }
    }
  }

  Stack(Stack&& s) noexcept : head_(s.head_), size_(s.size_) {
    s.head_ = nullptr;
    s.size_ = 0;
  }

  ~Stack() {
    while (head_ != nullptr) {
      Pop();
    }
  }

  Stack& operator=(Stack&& s) {
    if (this != &s) {
      while (head_ != nullptr) {
        Pop();
      }
      head_ = s.head_;
      size_ = s.size_;
      s.head_ = nullptr;
      s.size_ = 0;
    }
    return *this;
  }

  const_reference Top() {
    if (head_ == nullptr) {
      throw std::out_of_range("Stack is empty");
    }
    return head_->data;
  }

  bool Empty() const { return size_ == 0; }

  size_type Size() const { return size_; }

  void Push(const_reference value) {
    Node* newNode = new Node(value);
    newNode->next = head_;
    head_ = newNode;
    ++size_;
  }

  void Pop() {
    if (head_ == nullptr) {
      throw std::out_of_range("Stack is empty");
    } else {
      Node* temp = head_;
      head_ = head_->next;
      delete temp;
      --size_;
    }
  }

  void Swap(Stack& other) noexcept {
    std::swap(head_, other.head_);
    std::swap(size_, other.size_);
  }

  template <typename... Args>
  void InsertManyBack(Args&&... args) {
    for (const auto& arg : {args...}) {
      Push(arg);
    }
  }

 private:
  struct Node {
    value_type data;  // значение
    Node* next;       // указатель на след элемент
    Node(const_reference value)
        : data(value), next(nullptr) {}  // конструктор класса Node
  };

  Node* head_;      // верхний элемент
  size_type size_;  // размер стека
};
}  // namespace s21

#endif
