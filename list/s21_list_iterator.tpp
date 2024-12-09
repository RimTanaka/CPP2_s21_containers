#ifndef S21_LIST_ITERATOR_TPP_
#define S21_LIST_ITERATOR_TPP_

namespace s21 {

template <typename T>
typename List<T>::ListIterator& List<T>::ListIterator::operator++() {
  if (current_) {
    current_ = current_->next;
  } else {
    throw std::out_of_range("Node is nullptr");
  }
  return *this;
}

template <typename T>
typename List<T>::ListIterator& List<T>::ListIterator::operator--() {
  if (current_) {
    current_ = current_->previous;
  } else {
    throw std::out_of_range("Node is nullptr");
  }
  return *this;
}

template <typename T>
typename List<T>::reference List<T>::ListIterator::operator*() const {
  if (current_) {
    return current_->data;
  } else {
    throw std::out_of_range("Empty value");
  }
}

template <typename T>
bool List<T>::ListIterator::operator==(const ListIterator& other) const {
  return current_ == other.current_;
}

template <typename T>
bool List<T>::ListIterator::operator!=(const ListIterator& other) const {
  return !(*this == other);
}

}  // namespace s21

#endif  // S21_LIST_ITERATOR_TPP_