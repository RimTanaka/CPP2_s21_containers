#ifndef S21_LIST_TPP_
#define S21_LIST_TPP_

namespace s21 {
template <typename T>
List<T>::List() : head_(nullptr), tail_(nullptr), size_(0) {}

template <typename T>
List<T>::List(size_type n) : head_(nullptr), tail_(nullptr), size_(0) {
  for (size_type i = 0; i < n; ++i) {
    PushBack(0);
  }
}

template <typename T>
List<T>::List(std::initializer_list<value_type> const& items)
    : head_(nullptr), tail_(nullptr), size_(0) {
  for (const auto& item : items) {
    PushBack(item);
  }
}

template <typename T>
List<T>::List(const List& l) {
  if (l.head_ == nullptr) {
    head_ = nullptr;
    tail_ = nullptr;
    size_ = 0;
  } else {
    head_ = new Node(l.head_->data);
    size_ = l.size_;

    Node* current = head_;
    Node* l_current = l.head_->next;
    // Node* previous = head_;

    while (l_current != nullptr) {
      Node* newNode = new Node(l_current->data);
      current->next = newNode;
      newNode->previous = current;

      current = newNode;
      l_current = l_current->next;
    }
    tail_ = current;
  }
}

template <typename T>
List<T>::List(List&& l) noexcept
    : head_(l.head_), tail_(l.tail_), size_(l.size_) {
  l.head_ = nullptr;
  l.tail_ = nullptr;
  l.size_ = 0;
}

template <typename T>
List<T>::~List() {
  Clear();
}

template <typename T>
List<T>& List<T>::operator=(List&& l) {
  if (this != &l) {
    while (head_ != nullptr) {
      PopBack();
    }
  }
  head_ = l.head_;
  tail_ = l.tail_;
  size_ = l.size_;

  l.head_ = nullptr;
  l.tail_ = nullptr;
  l.size_ = 0;

  return *this;
}

template <typename T>
bool List<T>::operator==(List& l) {
  bool flag = true;
  if (size_ != l.size_) {
    return false;
  }
  iterator first = Begin();
  iterator second = l.Begin();
  for (size_type i = 0; i < size_ && flag == true; ++i) {
    if (*first != *second) {
      flag = false;
    }
    ++first;
    ++second;
  }
  return flag;
}

template <typename T>
typename List<T>::const_reference List<T>::Front() const {
  if (head_ == nullptr) {
    throw std::out_of_range("List is empty");
  }
  return head_->data;
}

template <typename T>
typename List<T>::const_reference List<T>::Back() const {
  if (tail_ == nullptr) {
    throw std::out_of_range("List is empty");
  }
  return tail_->data;
}

template <typename T>
bool List<T>::Empty() const {
  return size_ == 0;
}

template <typename T>
typename List<T>::size_type List<T>::Size() const {
  return size_;
}

template <typename T>
void List<T>::Clear() {
  while (head_ != nullptr) {
    PopBack();
  }
}

template <typename T>
void List<T>::PushBack(const_reference value) {
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

template <typename T>
void List<T>::PushFront(const_reference value) {
  Node* newNode = new Node(value);
  if (head_ == nullptr) {
    head_ = tail_ = newNode;
  } else {
    head_->previous = newNode;
    newNode->next = head_;
    head_ = newNode;
  }
  ++size_;
}

template <typename T>
void List<T>::PopBack() {
  if (tail_ == nullptr) {
    throw std::out_of_range("List is empty");
  } else {
    Node* temp = tail_;
    tail_ = tail_->previous;
    if (tail_) {
      tail_->next = nullptr;
    } else {
      head_ = nullptr;
    }
    delete temp;  // что-то исправить
    --size_;
  }
}

template <typename T>
void List<T>::PopFront() {
  if (head_ == nullptr) {
    throw std::out_of_range("List is empty");
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

template <typename T>
void List<T>::Swap(List& other) {
  std::swap(head_, other.head_);
  std::swap(size_, other.size_);
  std::swap(tail_, other.tail_);
}

template <typename T>
void List<T>::Reverse() {
  // if (size_ < 2) {
  //     return;
  // }
  Node* head = head_;
  Node* tail = tail_;
  for (size_type i = 0; i < (size_ / 2); ++i) {
    std::swap(head->data, tail->data);
    head = head->next;
    tail = tail->previous;
  }
}

template <typename T>
typename List<T>::iterator List<T>::Begin() {
  return iterator(head_);
}

template <typename T>
typename List<T>::iterator List<T>::End() {
  return iterator(nullptr);
}

template <typename T>
typename List<T>::const_iterator List<T>::Cbegin() const {
  return const_iterator(head_);
}

template <typename T>
typename List<T>::const_iterator List<T>::Cend() const {
  return const_iterator(nullptr);
}

template <typename T>
void List<T>::Sort() {
  for (size_type i = 0; i < size_ - 1; ++i) {
    Node* current = head_;
    Node* next = head_->next;
    for (size_type j = 0; j < size_ - 1 - i; ++j) {
      if (current->data > next->data) {
        std::swap(current->data, next->data);
      }
      current = next;
      next = current->next;
    }
  }
}

template <typename T>
void List<T>::Unique() {
  Node* cur = head_->next;
  for (size_type i = 0; i < size_ - 1; ++i) {
    if (cur->data == cur->previous->data) {
      Erase(iterator(cur->previous));
      i--;
    }
    cur = cur->next;
  }
}

template <typename T>
typename List<T>::iterator List<T>::Insert(iterator pos,
                                           const_reference value) {
  if (pos == End()) {
    PushBack(value);
    return iterator(tail_);
  } else if (pos == Begin()) {
    PushFront(value);
    return iterator(head_);
  }

  Node* currentNode = pos.current_;
  Node* newNode = new Node(value);

  newNode->next = currentNode;
  newNode->previous = currentNode->previous;
  currentNode->previous->next = newNode;
  currentNode->previous = newNode;

  ++size_;
  return iterator(newNode);
}

template <typename T>
void List<T>::Erase(iterator pos) {
  if (pos == End()) {
    throw std::out_of_range("Iterator out of range");
  }
  Node* deleteNode = pos.current_;
  if (deleteNode == head_) {
    PopFront();
  } else if (deleteNode == tail_) {
    PopBack();
  } else {
    deleteNode->previous->next = deleteNode->next;
    deleteNode->next->previous = deleteNode->previous;
    delete deleteNode;
    --size_;
  }
}

template <typename T>
void List<T>::Merge(List& other) {
  if (*this == other) {
    return;
  }
  size_type other_size = other.size_;
  for (size_type i = 0; i < other_size; ++i) {
    PushBack(other.head_->data);
    other.PopFront();
  }
  Sort();
  Unique();
}

template <typename T>
void List<T>::Splice(const_iterator pos, List& other) {
  size_type other_size = other.size_;
  for (size_type i = 0; i < other_size; ++i) {
    Insert(pos, other.head_->data);
    other.PopFront();
  }
}

template <typename T>
template <typename... Args>
typename List<T>::iterator List<T>::InsertMany(const_iterator pos,
                                               Args&&... args) {
  for (const auto& arg : {args...}) {
    Insert(pos, arg);
  }
  return pos;
}

template <typename T>
template <typename... Args>
void List<T>::InsertManyBack(Args&&... args) {
  for (const auto& arg : {args...}) {
    PushBack(arg);
  }
}

template <typename T>
template <typename... Args>
void List<T>::InsertManyFront(Args&&... args) {
  for (const auto& arg : {args...}) {
    PushFront(arg);
  }
}

}  // namespace s21

#endif
