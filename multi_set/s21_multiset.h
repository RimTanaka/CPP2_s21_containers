#ifndef SRC_MULTISET_S21_MULTISET_H_
#define SRC_MULTISET_S21_MULTISET_H_

#include "../binary_tree_base/binary_tree_base.h"

namespace s21 {

template <typename Key>
class MultiSet : public BinaryTreeBase<Key, Key> {
 public:
  using Iterator = typename BinaryTreeBase<Key, Key>::Iterator;
  using size_type = typename BinaryTreeBase<Key, Key>::size_type;

  MultiSet() : BinaryTreeBase<Key, Key>() {}

  MultiSet(const MultiSet& other) : BinaryTreeBase<Key, Key>(other) {}

  MultiSet(MultiSet&& other) noexcept
      : BinaryTreeBase<Key, Key>(std::move(other)) {}
  MultiSet(std::initializer_list<Key> init) {
    for (const auto& val : init) {
      Insert(val);
    }
  }

  std::pair<Iterator, bool> Insert(const Key& key) {
    typename BinaryTreeBase<Key, Key>::Node* new_node =
        new typename BinaryTreeBase<Key, Key>::Node(key, key);

    typename BinaryTreeBase<Key, Key>::Node* current = this->root_;
    typename BinaryTreeBase<Key, Key>::Node* parent = nullptr;

    while (current) {
      parent = current;
      if (key < current->key) {
        current = current->left;
      } else {
        current = current->right;
      }
    }
    new_node->parent = parent;
    if (!parent) {
      this->root_ = new_node;
    } else if (key < parent->key) {
      parent->left = new_node;
    } else {
      parent->right = new_node;
    }
    ++this->size_;
    return {Iterator(new_node, this), true};
  }

  std::pair<Iterator, bool> Insert(Key&& value) noexcept {
    typename BinaryTreeBase<Key, Key>::Node* new_node =
        new typename BinaryTreeBase<Key, Key>::Node(std::move(value),
                                                    std::move(value));

    typename BinaryTreeBase<Key, Key>::Node* current = this->root_;
    typename BinaryTreeBase<Key, Key>::Node* parent = nullptr;
    while (current) {
      parent = current;
      if (value < current->key) {
        current = current->left;
      } else {
        current = current->right;
      }
    }
    new_node->parent = parent;
    if (!parent) {
      this->root_ = new_node;
    } else if (value < parent->key) {
      parent->left = new_node;
    } else {
      parent->right = new_node;
    }
    ++this->size_;
    return {Iterator(new_node, this), true};
  }

  template <typename InputIt>
  std::pair<Iterator, bool> Insert(InputIt first, InputIt last) {
    bool all_inserted = true;
    Iterator first_inserted = this->End();
    for (auto it = first; it != last; ++it) {
      auto [insert_it, inserted] = Insert(*it);
      if (inserted && all_inserted) {
        first_inserted = insert_it;
      }
      all_inserted = all_inserted && inserted;
    }
    return {first_inserted, all_inserted};
  }

  std::pair<Iterator, bool> Insert(std::initializer_list<Key> init) {
    bool all_inserted = true;
    Iterator first_inserted = this->End();
    for (const auto& val : init) {
      auto [insert_it, inserted] = Insert(val);
      if (inserted && all_inserted) {
        first_inserted = insert_it;
      }
      all_inserted = all_inserted && inserted;
    }
    return {first_inserted, all_inserted};
  }

  template <typename... Args>
  std::vector<std::pair<Iterator, bool>> InsertMany(Args&&... args) {
    std::vector<std::pair<Iterator, bool>> results;
    (results.push_back(Insert(std::forward<Args>(args))), ...);
    return results;
  }

  size_t Erase(const Key& key) { return BinaryTreeBase<Key, Key>::Erase(key); }

  Iterator Find(const Key& key) { return Iterator(this->FindNode(key), this); }

  bool Contains(const Key& key) const {
    return BinaryTreeBase<Key, Key>::Contains(key);
  }

  size_type Count(const Key& key) const {
    size_type count = 0;
    typename BinaryTreeBase<Key, Key>::Node* node = this->root_;
    while (node) {
      if (node->key == key) {
        ++count;
      }
      node = (key < node->key) ? node->left : node->right;
    }
    return count;
  }

  MultiSet& operator=(const MultiSet& other) {
    if (this != &other) {
      BinaryTreeBase<Key, Key>::operator=(other);
    }
    return *this;
  }

  MultiSet& operator=(MultiSet&& other) noexcept {
    if (this != &other) {
      BinaryTreeBase<Key, Key>::operator=(std::move(other));
    }
    return *this;
  }
  bool Empty() const { return BinaryTreeBase<Key, Key>::Empty(); }
  size_t Size() const { return BinaryTreeBase<Key, Key>::Size(); }
};

}  // namespace s21

#endif  // SRC_MULTISET_S21_MULTISET_H_
