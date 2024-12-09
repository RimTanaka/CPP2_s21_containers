#ifndef SRC_SET_S21_SET_H_
#define SRC_SET_S21_SET_H_

#include "../binary_tree_base/binary_tree_base.h"

namespace s21 {
template <typename Key>
class Set : public BinaryTreeBase<Key, Key> {
 public:
  using Iterator = typename BinaryTreeBase<Key, Key>::Iterator;

  Set() = default;
  Set(const Set &other) = default;
  Set(Set &&other) noexcept = default;
  Set(std::initializer_list<Key> init) {
    for (const auto &val : init) {
      Insert(val);
    }
  }
  ~Set() = default;

  std::pair<Iterator, bool> Insert(const Key &value) {
    return BinaryTreeBase<Key, Key>::Insert(value, value);
  }

  std::pair<Iterator, bool> Insert(Key &&value) {
    return BinaryTreeBase<Key, Key>::Insert(std::move(value), std::move(value));
  }

  template <typename InputIt>
  void Insert(InputIt first, InputIt last) {
    for (auto it = first; it != last; ++it) {
      Insert(*it);
    }
  }

  void Insert(std::initializer_list<Key> init) {
    for (const auto &val : init) {
      Insert(val);
    }
  }

  template <typename... Args>
  std::vector<std::pair<Iterator, bool>> InsertMany(Args &&...args) {
    std::vector<std::pair<Iterator, bool>> results;
    (results.push_back(Insert(std::forward<Args>(args))), ...);
    return results;
  }

  size_t Erase(const Key &key) { return BinaryTreeBase<Key, Key>::Erase(key); }

  bool Contains(const Key &key) const {
    return BinaryTreeBase<Key, Key>::Contains(key);
  }

  Iterator Find(const Key &key) {
    typename BinaryTreeBase<Key, Key>::Node *node = this->FindNode(key);
    if (node) {
      return typename BinaryTreeBase<Key, Key>::Iterator(node, this);
    }
    return this->End();
  }

  Iterator Begin() { return BinaryTreeBase<Key, Key>::Begin(); }
  Iterator End() { return BinaryTreeBase<Key, Key>::End(); }
  Iterator Begin() const { return BinaryTreeBase<Key, Key>::Begin(); }
  Iterator End() const { return BinaryTreeBase<Key, Key>::End(); }

  bool Empty() const { return BinaryTreeBase<Key, Key>::Empty(); }
  size_t Size() const { return BinaryTreeBase<Key, Key>::Size(); }
  void Clear() { BinaryTreeBase<Key, Key>::Clear(); }
};
}  // namespace s21
#endif  // SRC_SET_S21_SET_H_
