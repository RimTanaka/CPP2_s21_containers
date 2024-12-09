#ifndef SRC_VECTOR_S21_VECTOR_H_
#define SRC_VECTOR_S21_VECTOR_H_

#include <iostream>
#include <limits>

namespace s21 {

template <typename T>
class Vector {
 public:
  using valueType = T;
  using reference = T &;
  using constReference = const T &;
  using iterator = T *;
  using constIterator = const T *;
  using sizeType = size_t;

  Vector();
  explicit Vector(sizeType n);
  Vector(std::initializer_list<valueType> const &items);
  Vector(const Vector &v);
  Vector(Vector &&v) noexcept;
  ~Vector();

  Vector &operator=(const Vector &v);

  Vector &operator=(Vector &&v) noexcept;

  void Swap(Vector &other);

  reference At(sizeType pos);

  reference operator[](sizeType pos);

  constReference Front() const;
  constReference Back() const;

  iterator Data();
  iterator Begin();
  iterator End();

  constIterator Data() const;
  constIterator Begin() const;
  constIterator End() const;
  bool Empty();

  sizeType Size();

  sizeType MaxSize();

  void Reserve(sizeType size);

  sizeType Capacity();

  void ShrinkToFit();
  void Clear();

  iterator Insert(iterator pos, constReference value);
  void Erase(iterator pos);

  void PushBack(constReference value);

  void PopBack();

  template <typename... Args>
  iterator InsertMany(constIterator pos, Args &&...args);

  template <typename... Args>
  void InsertManyBack(Args &&...args);

 private:
  size_t arr_size_;
  size_t arr_capacity_;
  iterator arr_;

  void ReallocMemory();
  bool EnsureCapacity();
};

}  // namespace s21

#include "s21_vector.tpp"

#endif  // SRC_VECTOR_S21_VECTOR_H_
