#ifndef S21_QUEUE_H_
#define S21_QUEUE_H_

#include <cstddef>
#include <initializer_list>
#include <iostream>
#include <stdexcept>

namespace s21 {
template <typename T>
class Queue {
 public:
  using value_type = T;           // тип
  using reference = value_type&;  // ссылка на объект типа
  using const_reference =
      const value_type&;  // ссылка на неизменяемый объект типа
  using size_type = std::size_t;  // беззнаковый тип

  Queue() : head_(nullptr), tail_(nullptr), size_(0) {}

  Queue(std::initializer_list<value_type> const& items)
      : head_(nullptr), tail_(nullptr), size_(0) {
    for (const auto& item : items) {
      Push(item);
    }
  }

  Queue(const Queue& q) {
    if (q.head_ == nullptr) {
      head_ = nullptr;
      tail_ = nullptr;
      size_ = 0;
    } else {
      head_ = new Node(q.head_->data);
      size_ = q.size_;

      Node* current = head_;
      Node* q_current = q.head_->next;
      // Node* previous = head_;

      while (q_current != nullptr) {
        Node* newNode = new Node(q_current->data);
        current->next = newNode;
        newNode->previous = current;

        current = newNode;
        q_current = q_current->next;
      }
      tail_ = current;
    }
  }

  Queue(Queue&& q) noexcept : head_(q.head_), tail_(q.tail_), size_(q.size_) {
    q.head_ = nullptr;
    q.tail_ = nullptr;
    q.size_ = 0;
  }

  ~Queue() {
    while (head_ != nullptr) {
      Pop();
    }
  }

  Queue& operator=(Queue&& q) {
    if (this != &q) {
      while (head_ != nullptr) {
        Pop();
      }
    }
    head_ = q.head_;
    tail_ = q.tail_;
    size_ = q.size_;

    q.head_ = nullptr;
    q.tail_ = nullptr;
    q.size_ = 0;

    return *this;
  }

  const_reference Front() {
    if (head_ == nullptr) {
      throw std::out_of_range("Queue is empty");
    }
    return head_->data;
  }

  const_reference Back() {
    if (tail_ == nullptr) {
      throw std::out_of_range("Queue is empty");
    }
    return tail_->data;
  }

  bool Empty() const { return size_ == 0; }
  size_type Size() const { return size_; }

  void Push(const_reference value) {
    Node* newNode = new Node(value);
    if (tail_ == nullptr) {
      head_ = tail_ = newNode;
    } else {
      tail_->next = newNode;
      newNode->previous = tail_;
      tail_ = newNode;
    }
    ++size_;
  }

  void Pop() {
    if (head_ == nullptr) {
      throw std::out_of_range("Queue is empty");
    } else {
      Node* temp = head_;
      head_ = head_->next;
      if (head_) {
        head_->previous = nullptr;
      } else {
        tail_ = nullptr;
      }
      delete temp;
      --size_;
    }
  }

  void Swap(Queue& other) noexcept {
    std::swap(head_, other.head_);
    std::swap(size_, other.size_);
    std::swap(tail_, other.tail_);
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
    Node* previous;  // указатель на предыдущий элемент
    Node(const_reference value)
        : data(value),
          next(nullptr),
          previous(nullptr) {}  // конструктор класса Node
  };

  Node* head_;      // первый
  Node* tail_;      // последний
  size_type size_;  // размер
};
}  // namespace s21

#endif