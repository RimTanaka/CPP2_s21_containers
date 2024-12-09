#ifndef SRC_VECTOR_S21_VECTOR_TPP_
#define SRC_VECTOR_S21_VECTOR_TPP_

namespace s21 {

template <typename T>
Vector<T>::Vector() : arr_size_(0), arr_capacity_(0), arr_(nullptr) {}

template <typename T>
Vector<T>::Vector(sizeType n) : arr_size_(n), arr_capacity_(n), arr_(nullptr) {
  if (n > 0) arr_ = new valueType[arr_capacity_];
}

template <typename T>
Vector<T>::Vector(std::initializer_list<valueType> const &items)
    : arr_size_(items.size()), arr_capacity_(items.size()) {
  arr_ = new valueType[arr_capacity_];
  std::copy(items.begin(), items.end(), arr_);
}

template <typename T>
Vector<T>::Vector(const Vector &v)
    : arr_size_(v.arr_size_), arr_capacity_(v.arr_capacity_) {
  arr_ = new valueType[arr_capacity_];
  std::copy(v.Begin(), v.End(), arr_);
}

template <typename T>
Vector<T>::Vector(Vector &&v) noexcept
    : arr_size_(v.arr_size_), arr_capacity_(v.arr_capacity_), arr_(v.arr_) {
  v.arr_ = nullptr;
  v.arr_capacity_ = 0;
  v.arr_size_ = 0;
}

template <typename T>
Vector<T>::~Vector() {
  if (arr_ != nullptr) {
    delete[] arr_;
    arr_ = nullptr;
  }
}

template <typename T>
Vector<T> &Vector<T>::operator=(const Vector<T> &v) {
  if (this != &v) {
    delete[] arr_;

    arr_size_ = v.arr_size_;
    arr_capacity_ = v.arr_capacity_;

    arr_ = new valueType[arr_capacity_];

    for (size_t i = 0; i < arr_size_; ++i) {
      arr_[i] = v.arr_[i];
    }
  }
  return *this;
}

template <typename T>
Vector<T> &Vector<T>::operator=(Vector<T> &&v) noexcept {
  if (this != &v) {
    delete[] arr_;

    arr_size_ = std::move(v.arr_size_);
    arr_capacity_ = std::move(v.arr_capacity_);
    arr_ = v.arr_;

    v.arr_ = nullptr;
    v.arr_size_ = 0;
    v.arr_capacity_ = 0;
  }
  return *this;
}

template <typename T>
void Vector<T>::Swap(Vector &other) {
  std::swap(arr_capacity_, other.arr_capacity_);
  std::swap(arr_size_, other.arr_size_);
  std::swap(arr_, other.arr_);
}

template <typename T>
typename Vector<T>::reference Vector<T>::At(sizeType pos) {
  if (pos >= arr_size_)
    throw std::out_of_range(
        "vector::At(): index (which is " + std::to_string(pos) +
        ") >= Size this->Size() (which is " + std::to_string(arr_size_) + ")");
  return arr_[pos];
}

template <typename T>
typename Vector<T>::reference Vector<T>::operator[](sizeType pos) {
  return arr_[pos];
}

template <typename T>
typename Vector<T>::constReference Vector<T>::Front() const {
  return *Begin();
}

template <typename T>
typename Vector<T>::constReference Vector<T>::Back() const {
  return arr_[arr_size_ - 1];
}

template <typename T>
typename Vector<T>::iterator Vector<T>::Data() {
  return arr_;
}

template <typename T>
typename Vector<T>::iterator Vector<T>::Begin() {
  return arr_;
}

template <typename T>
typename Vector<T>::iterator Vector<T>::End() {
  return arr_ + arr_size_;
}

template <typename T>
typename Vector<T>::constIterator Vector<T>::Data() const {
  return arr_;
}

template <typename T>
typename Vector<T>::constIterator Vector<T>::Begin() const {
  return arr_;
}

template <typename T>
typename Vector<T>::constIterator Vector<T>::End() const {
  return arr_ + arr_size_;
}

template <typename T>
bool Vector<T>::Empty() {
  return arr_size_ == 0;
}

template <typename T>
typename Vector<T>::sizeType Vector<T>::Size() {
  return End() - Begin();
}

template <typename T>
typename Vector<T>::sizeType Vector<T>::MaxSize() {
  return std::numeric_limits<sizeType>::max() / sizeof(valueType) / 2;
}

template <typename T>
void Vector<T>::Reserve(sizeType size) {
  if (size > MaxSize()) {
    throw std::length_error("Requested Size exceeds the maximum Size.");
  }
  if (arr_capacity_ > size) {
    return;
  }

  auto *tmp = new valueType[size];
  for (size_t i = 0; i < arr_size_; ++i) {
    tmp[i] = std::move(arr_[i]);
  }
  delete[] arr_;
  arr_ = tmp;
  arr_capacity_ = size;
}

template <typename T>
typename Vector<T>::sizeType Vector<T>::Capacity() {
  return arr_capacity_;
}

template <typename T>
void Vector<T>::ShrinkToFit() {
  T *tmp = new valueType[arr_size_];
  for (size_t i = 0; i < arr_size_; ++i) {
    tmp[i] = std::move(arr_[i]);
  }
  delete[] arr_;
  arr_ = tmp;
  arr_capacity_ = arr_size_;
}

template <typename T>
void Vector<T>::Clear() {
  arr_size_ = 0;
}

template <typename T>
typename Vector<T>::iterator Vector<T>::Insert(iterator pos,
                                               constReference value) {
  Vector<valueType> tmp(arr_size_ + 1);
  sizeType i = 0, j = 0, position = pos - Begin();
  while (i < arr_size_ + 1) {
    if (i != position) {
      tmp.arr_[i] = std::move(arr_[j++]);
    } else {
      tmp.arr_[i] = std::move(value);
    }
    ++i;
  }

  *this = std::move(tmp);
  return arr_ + position;
}

template <typename T>
void Vector<T>::Erase(iterator pos) {
  Vector<valueType> tmp(arr_size_ - 1);
  sizeType i = 0, j = 0, position = pos - Begin();
  while (i < arr_size_) {
    if (i != position) {
      tmp.arr_[j++] = arr_[i];
    }
    ++i;
  }

  *this = std::move(tmp);
  tmp.arr_ = nullptr;
  tmp.arr_size_ = 0;
  tmp.arr_capacity_ = 0;
}

template <typename T>
void Vector<T>::PushBack(constReference value) {
  ReallocMemory();
  arr_[arr_size_++] = value;
}

template <typename T>
void Vector<T>::PopBack() {
  arr_size_--;
}

template <typename T>
template <typename... Args>
typename Vector<T>::iterator Vector<T>::InsertMany(constIterator pos,
                                                   Args &&...args) {
  s21::Vector<valueType> tmp{std::forward<Args>(args)...};

  auto position = (iterator)pos;
  for (sizeType i = 0; i < tmp.arr_size_; ++i) {
    position = Insert(position, tmp[i]) + 1;
  }
  return position;
}

template <typename T>
template <typename... Args>
void Vector<T>::InsertManyBack(Args &&...args) {
  s21::Vector<valueType> tmp{std::forward<Args>(args)...};
  iterator position = this->End();
  for (sizeType i = 0; i < tmp.arr_size_; ++i) {
    position = Insert(position, tmp[i]) + 1;
  }
}

template <typename T>
bool Vector<T>::EnsureCapacity() {
  if (arr_size_ == arr_capacity_) {
    arr_capacity_ = arr_capacity_ ? arr_capacity_ * 2 : 1;

    if (arr_capacity_ > MaxSize()) {
      throw std::length_error("Requested Size exceeds the maximum Size.");
    }
    return true;
  }
  return false;
}

template <typename T>
void Vector<T>::ReallocMemory() {
  if (EnsureCapacity()) {
    T *tmp = new valueType[arr_capacity_];

    for (sizeType i = 0; i < arr_size_; ++i) {
      tmp[i] = std::move(arr_[i]);
    }

    delete[] arr_;
    arr_ = tmp;
  }
}

}  // namespace s21

#endif  // SRC_VECTOR_S21_VECTOR_TPP_