#ifndef S21_LIST_H_
#define S21_LIST_H_

#include <cstddef>
#include <initializer_list>
#include <iostream>
#include <limits>
#include <stdexcept>

namespace s21 {
template <typename T>
class List {
  struct Node;

 public:
  class ListIterator;

  using value_type = T;           // тип
  using reference = value_type&;  // ссылка на объект типа
  using const_reference =
      const value_type&;  // ссылка на неизменяемый объект типа
  using size_type = std::size_t;  // беззнаковый тип
  using iterator = List<T>::ListIterator;  // тип для итерации по контейнеру
  using const_iterator =
      const List<T>::ListIterator;  // тип константы для итерации по контейнеру

  class ListIterator {
    friend class List;

   public:
    ListIterator(Node* node) : current_(node) {}

    reference operator*() const;

    iterator& operator++();
    iterator& operator--();

    bool operator==(const iterator& other) const;
    bool operator!=(const iterator& other) const;

   private:
    Node* current_;
  };

  // constructors
  List();
  List(size_type n);
  List(std::initializer_list<value_type> const& items);
  List(const List& l);
  List(List&& l) noexcept;
  ~List();

  List& operator=(List&& l);
  bool operator==(List& l);

  const_reference Front() const;
  const_reference Back() const;

  bool Empty() const;
  size_type Size() const;

  size_type MaxSize() { return std::numeric_limits<size_type>::max(); }

  void Clear();

  void PushBack(const_reference value);
  void PushFront(const_reference value);

  void PopBack();
  void PopFront();

  void Swap(List& other);
  void Reverse();

  iterator Begin();
  iterator End();

  const_iterator Cbegin() const;
  const_iterator Cend() const;

  void Sort();
  void Unique();

  iterator Insert(ListIterator pos, const_reference value);
  void Erase(ListIterator pos);
  void Merge(List& other);
  void Splice(const_iterator pos, List& other);

  template <typename... Args>
  iterator InsertMany(const_iterator pos, Args&&... args);

  template <typename... Args>
  void InsertManyBack(Args&&... args);

  template <typename... Args>
  void InsertManyFront(Args&&... args);

 private:
  struct Node {
    value_type data;  // значение
    Node* next;       // указатель на след элемент
    Node* previous;  // указатель на предыдущий элемент
    Node() : data(0), next(nullptr), previous(nullptr){};
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

#include "s21_list.tpp"
#include "s21_list_iterator.tpp"

#endif