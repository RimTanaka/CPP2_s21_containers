#ifndef SRC_MAP_S21_MAP_H_
#define SRC_MAP_S21_MAP_H_

#include "../binary_tree_base/binary_tree_base.h"

namespace s21 {

template <typename Key, typename T>
class Map : public BinaryTreeBase<Key, T> {
 public:
  using Node = typename BinaryTreeBase<Key, T>::Node;
  using Iterator = typename BinaryTreeBase<Key, T>::Iterator;

  Map() = default;
  Map(const Map &other) = default;
  Map(Map &&other) noexcept = default;
  Map(std::initializer_list<Node> init) : BinaryTreeBase<Key, T>(init) {}

  std::pair<Iterator, bool> Insert(const std::pair<Key, T> &value) {
    return BinaryTreeBase<Key, T>::Insert(value.first, value.second);
  }

  std::pair<Iterator, bool> Insert(std::pair<Key, T> &&value) {
    return BinaryTreeBase<Key, T>::Insert(std::move(value.first),
                                          std::move(value.second));
  }

  std::pair<typename Map<Key, T>::Iterator, bool> Insert(
      std::initializer_list<std::pair<Key, T>> ilist) {
    bool all_inserted = true;
    for (const auto &value : ilist) {
      auto [iterator, inserted] = Insert(value);
      all_inserted = all_inserted && inserted;
    }
    return {Begin(), all_inserted};
  }

  template <typename InputIt>
  std::pair<typename Map<Key, T>::Iterator, bool> Insert(InputIt first,
                                                         InputIt last) {
    bool all_inserted = true;
    for (auto it = first; it != last; ++it) {
      auto [iterator, inserted] = Insert(*it);
      all_inserted = all_inserted && inserted;
    }
    return {Begin(), all_inserted};
  }

  template <typename... Args>
  std::vector<std::pair<Iterator, bool>> InsertMany(Args &&...args) {
    std::vector<std::pair<Iterator, bool>> results;
    (results.push_back(this->Insert(std::forward<Args>(args))), ...);
    return results;
  }

  T &operator[](const Key &key) {
    auto it = this->Find(key);
    if (it != this->End()) {
      return it->value;
    } else {
      this->Insert({key, T()});
      return this->At(key);
    }
  }

  Map &operator=(const Map &other) {
    if (this != &other) {
      BinaryTreeBase<Key, T>::operator=(other);
    }
    return *this;
  }

  Map &operator=(Map &&other) noexcept {
    if (this != &other) {
      BinaryTreeBase<Key, T>::operator=(std::move(other));
    }
    return *this;
  }

  T &At(const Key &key) {
    Node *node = this->FindNode(key);
    if (!node) throw std::out_of_range("Ключ не найден!");
    return node->value;
  }

  bool Contains(const Key &key) const {
    return BinaryTreeBase<Key, T>::Contains(key);
  }

  Iterator Find(const Key &key) {
    Node *node = this->FindNode(key);
    return Iterator(node, this);
  }

  size_t Erase(const Key &key) { return BinaryTreeBase<Key, T>::Erase(key); }

  Iterator Begin() { return BinaryTreeBase<Key, T>::Begin(); }

  Iterator Begin() const { return BinaryTreeBase<Key, T>::Begin(); }

  Iterator End() { return BinaryTreeBase<Key, T>::End(); }

  Iterator End() const { return BinaryTreeBase<Key, T>::End(); }

  size_t Size() const { return BinaryTreeBase<Key, T>::Size(); }

  bool Empty() const { return BinaryTreeBase<Key, T>::Empty(); }

  void Clear() { BinaryTreeBase<Key, T>::Clear(); }
};

}  // namespace s21
#endif  // SRC_MAP_S21_MAP_H_
