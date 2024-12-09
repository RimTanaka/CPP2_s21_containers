#ifndef CPP2_S21_CONTAINERS_1_S21_ARRAY_H
#define CPP2_S21_CONTAINERS_1_S21_ARRAY_H

#include <initializer_list>
#include <iostream>

namespace s21 {

template <typename T, size_t S>
class Array {
 public:
  using valueType = T;
  using reference = T &;
  using constReference = const T &;
  using iterator = T *;
  using constIterator = const T *;
  using sizeType = size_t;

  Array();
  Array(std::initializer_list<valueType> const &items);
  Array(const Array &a);
  Array(Array &&a) noexcept;
  ~Array();

  Array &operator=(Array &&a) noexcept;
  Array &operator=(const Array<T, S> &a);

  constexpr reference At(sizeType pos);
  constexpr reference operator[](sizeType pos) noexcept;
  constexpr constReference Front() noexcept;
  constexpr constReference Back() noexcept;
  iterator Data();
  iterator Begin();
  iterator End();

  constIterator Data() const;
  constIterator Begin() const;
  constIterator End() const;

  constexpr bool Empty() const noexcept;
  constexpr sizeType Size() const noexcept;
  constexpr sizeType MaxSize() const noexcept;

  void Swap(Array &other);
  void Fill(constReference value);

 private:
  valueType arr_[S ? S : 1] = {};
};
}  // namespace s21

#include "s21_array.tpp"

#endif  // CPP2_S21_CONTAINERS_1_S21_ARRAY_H
