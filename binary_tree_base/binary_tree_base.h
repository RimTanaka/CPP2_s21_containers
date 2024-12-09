#ifndef SRC_BINARY_TREE_BASE_BINARY_TREE_BASE_H_
#define SRC_BINARY_TREE_BASE_BINARY_TREE_BASE_H_

#include <cstddef>
#include <iostream>
#include <string>
#include <utility>
template <typename Key, typename T>
class BinaryTreeBase {
 protected:
  struct Node {
    Key key;
    T value;
    Node* left;
    Node* right;
    Node* parent;

    // Создание нового узла
    Node(const Key& key, const T& value)
        : key(key),
          value(value),
          left(nullptr),
          right(nullptr),
          parent(nullptr) {}

    // Копирование из 1 узла в другой
    Node(const Node& other)
        : key(other.key),
          value(other.value),
          left(nullptr),
          right(nullptr),
          parent(nullptr) {}
  };

  Node* root_;
  size_t size_;

  BinaryTreeBase();
  BinaryTreeBase(const BinaryTreeBase& other);
  BinaryTreeBase(BinaryTreeBase&& other) noexcept;
  BinaryTreeBase(std::initializer_list<Node> init);
  Node* CopyNodes(Node* node);

  using size_type = std::size_t;
  size_type Erase(const Key& key);
  bool Contains(const Key& key) const;
  bool Empty() const;
  size_t Size() const;
  void Clear();

  Node* FindNode(const Key& key) const;

  Node* MinNode(Node* node) const;
  Node* MaxNode(Node* node) const;

 public:
  ~BinaryTreeBase();
  BinaryTreeBase& operator=(const BinaryTreeBase& other);
  BinaryTreeBase& operator=(BinaryTreeBase&& other) noexcept;
  class Iterator {
   private:
    Node* current_;
    const BinaryTreeBase* tree_;

   public:
    Iterator(Node* ptr, const BinaryTreeBase* tree);
    Key& operator*();
    Node* operator->();
    Iterator& operator--();
    Iterator& operator++();
    bool operator==(const Iterator& other) const;
    bool operator!=(const Iterator& other) const;
  };

  Iterator Begin();
  Iterator End();
  const Iterator Begin() const;
  const Iterator End() const;

 protected:
  std::pair<Iterator, bool> Insert(const Key& key, const T& value);

 private:
  void Transplant(Node* u, Node* v);
  void ClearHelper(Node* node);
};

#include "binary_tree_base.tpp"

#endif  // SRC_BINARY_TREE_BASE_BINARY_TREE_BASE_H_
