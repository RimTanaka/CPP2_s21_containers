#ifndef CPP2_S21_CONTAINERS_1_S21_ARRAY_TPP
#define CPP2_S21_CONTAINERS_1_S21_ARRAY_TPP
#include "s21_array.h"

namespace s21 {

template <typename T, size_t S>
Array<T, S>::Array() = default;

template <typename T, size_t S>
Array<T, S>::Array(std::initializer_list<valueType> const &items) {
  for (size_t i = 0; i < items.size(); ++i) {
    arr_[i] = items.begin()[i];
  }
}

template <typename T, size_t S>
Array<T, S>::Array(const Array<T, S> &a) {
  for (size_t i = 0; i < S; ++i) {
    arr_[i] = a.arr_[i];
  }
}

template <typename T, size_t S>
Array<T, S>::Array(Array<T, S> &&a) noexcept {
  if (this != &a) {
    for (size_t i = 0; i < S; ++i) {
      arr_[i] = std::move(a.arr_[i]);
    }
  }
}

template <typename T, size_t S>
Array<T, S>::~Array() = default;

template <typename T, size_t S>
Array<T, S> &Array<T, S>::operator=(Array<T, S> &&a) noexcept {
  if (this != &a) {
    for (size_t i = 0; i < S; ++i) {
      arr_[i] = std::move(a.arr_[i]);
    }
  }
  return *this;
}

template <typename T, size_t S>
Array<T, S> &Array<T, S>::operator=(const Array<T, S> &a) {
  if (this != &a) {
    for (size_t i = 0; i < S; ++i) {
      arr_[i] = a.arr_[i];
    }
  }
  return *this;
}

template <typename T, size_t S>
constexpr typename Array<T, S>::reference Array<T, S>::At(sizeType pos) {
  if (pos >= S) {
    throw std::out_of_range(
        "array::At(): index (which is " + std::to_string(pos) +
        ") >= Size this->Size() (which is " + std::to_string(S) + ")");
  }
  return arr_[pos];
}

template <typename T, size_t S>
typename Array<T, S>::reference constexpr Array<T, S>::operator[](
    sizeType pos) noexcept {
  return arr_[pos];
}

template <typename T, size_t S>
typename Array<T, S>::constReference constexpr Array<T, S>::Front() noexcept {
  return arr_[0];
}

template <typename T, size_t S>
typename Array<T, S>::constReference constexpr Array<T, S>::Back() noexcept {
  return arr_[S - 1];
}

template <typename T, size_t S>
bool constexpr Array<T, S>::Empty() const noexcept {
  return S == 0;
}

template <typename T, size_t S>
typename Array<T, S>::sizeType constexpr Array<T, S>::Size() const noexcept {
  return S;
}

template <typename T, size_t S>
typename Array<T, S>::sizeType constexpr Array<T, S>::MaxSize() const noexcept {
  return S;
}

template <typename T, size_t S>
typename Array<T, S>::iterator Array<T, S>::Data() {
  return arr_;
}

template <typename T, size_t S>
typename Array<T, S>::iterator Array<T, S>::Begin() {
  return arr_;
}

template <typename T, size_t S>
typename Array<T, S>::iterator Array<T, S>::End() {
  return arr_ + S;
}

template <typename T, size_t S>
typename Array<T, S>::constIterator Array<T, S>::Data() const {
  return arr_;
}

template <typename T, size_t S>
typename Array<T, S>::constIterator Array<T, S>::Begin() const {
  return arr_;
}

template <typename T, size_t S>
typename Array<T, S>::constIterator Array<T, S>::End() const {
  return arr_ + S;
}

template <typename T, size_t S>
void Array<T, S>::Swap(Array &other) {
  for (iterator iter1 = Begin(), iter2 = other.Begin(); iter1 != End();
       ++iter1, ++iter2) {
    std::swap(*iter1, *iter2);
  }
}

template <typename T, size_t S>
void Array<T, S>::Fill(constReference value) {
  for (iterator iter = Begin(); iter != End(); ++iter) {
    *iter = value;
  }
}

}  // namespace s21
#endif  // CPP2_S21_CONTAINERS_1_S21_ARRAY_TPP