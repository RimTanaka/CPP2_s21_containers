#ifndef SRC_BINARY_TREE_BASE_BINARY_TREE_BASE_TPP_
#define SRC_BINARY_TREE_BASE_BINARY_TREE_BASE_TPP_

template <typename Key, typename T>
typename BinaryTreeBase<Key, T>::Node* BinaryTreeBase<Key, T>::CopyNodes(
    Node* node) {
  if (!node) return nullptr;
  Node* newNode = new Node(*node);
  newNode->left = CopyNodes(node->left);
  newNode->right = CopyNodes(node->right);
  return newNode;
}

template <typename Key, typename T>
BinaryTreeBase<Key, T>::BinaryTreeBase() : root_(nullptr), size_(0) {}

template <typename Key, typename T>
BinaryTreeBase<Key, T>::BinaryTreeBase(const BinaryTreeBase& other)
    : root_(CopyNodes(other.root_)), size_(other.size_) {}

template <typename Key, typename T>
BinaryTreeBase<Key, T>::BinaryTreeBase(BinaryTreeBase&& other) noexcept
    : root_(other.root_), size_(other.size_) {
  other.root_ = nullptr;
  other.size_ = 0;
}

template <typename Key, typename T>
BinaryTreeBase<Key, T>::BinaryTreeBase(std::initializer_list<Node> init)
    : root_(nullptr), size_(0) {
  for (const auto& elem : init) {
    Insert(elem.key, elem.value);
  }
}

template <typename Key, typename T>
BinaryTreeBase<Key, T>::~BinaryTreeBase() {
  Clear();
}

template <typename Key, typename T>
BinaryTreeBase<Key, T>& BinaryTreeBase<Key, T>::operator=(
    const BinaryTreeBase<Key, T>& other) {
  if (this != &other) {
    Clear();
    root_ = CopyNodes(other.root_);
    size_ = other.size_;
  }
  return *this;
}

template <typename Key, typename T>
BinaryTreeBase<Key, T>& BinaryTreeBase<Key, T>::operator=(
    BinaryTreeBase<Key, T>&& other) noexcept {
  if (this != &other) {
    Clear();
    root_ = other.root_;
    size_ = other.size_;
    other.root_ = nullptr;
    other.size_ = 0;
  }
  return *this;
}

template <typename Key, typename T>
std::pair<typename BinaryTreeBase<Key, T>::Iterator, bool>
BinaryTreeBase<Key, T>::Insert(const Key& key, const T& value) {
  Node* new_node = new Node(key, value);
  bool flag = true;

  if (!root_) {
    root_ = new_node;
    size_++;
  } else {
    Node* current = root_;
    Node* parent = nullptr;

    while (current) {
      parent = current;
      if (key < current->key) {
        current = current->left;
      } else if (key > current->key) {
        current = current->right;
      } else {
        // current->value = value;
        delete new_node;
        new_node = nullptr;
        flag = false;
        return {BinaryTreeBase<Key, T>::Iterator(current, this), flag};
      }
    }

    if (flag) {
      new_node->parent = parent;
      if (key < parent->key) {
        parent->left = new_node;
      } else {
        parent->right = new_node;
      }
      size_++;
    }
  }

  return {BinaryTreeBase<Key, T>::Iterator(new_node, this), flag};
}

template <typename Key, typename T>
typename BinaryTreeBase<Key, T>::size_type BinaryTreeBase<Key, T>::Erase(
    const Key& key) {
  Node* node = FindNode(key);
  size_type counter = 0;
  while (node) {
    Node* node_to_delete = node;
    if (!node->left) {
      Transplant(node, node->right);
    } else if (!node->right) {
      Transplant(node, node->left);
    } else {
      Node* successor = MinNode(node->right);
      if (successor->parent != node) {
        Transplant(successor, successor->right);
        successor->right = node->right;
        successor->right->parent = successor;
      }
      Transplant(node, successor);
      successor->left = node->left;
      successor->left->parent = successor;
    }

    node = FindNode(key);
    delete node_to_delete;
    --size_;
    ++counter;
  }
  return counter;
}

template <typename Key, typename T>
bool BinaryTreeBase<Key, T>::Contains(const Key& key) const {
  return FindNode(key) != nullptr;
}

template <typename Key, typename T>
bool BinaryTreeBase<Key, T>::Empty() const {
  return size_ == 0;
}

template <typename Key, typename T>
size_t BinaryTreeBase<Key, T>::Size() const {
  return size_;
}

template <typename Key, typename T>
void BinaryTreeBase<Key, T>::Clear() {
  ClearHelper(root_);
  root_ = nullptr;
  size_ = 0;
}

template <typename Key, typename T>
typename BinaryTreeBase<Key, T>::Node* BinaryTreeBase<Key, T>::MinNode(
    Node* node) const {
  if (!node) return nullptr;
  while (node && node->left) {
    node = node->left;
  }
  return node;
}

template <typename Key, typename T>
typename BinaryTreeBase<Key, T>::Node* BinaryTreeBase<Key, T>::MaxNode(
    Node* node) const {
  while (node->right) {
    node = node->right;
  }
  return node;
}

template <typename Key, typename T>
typename BinaryTreeBase<Key, T>::Node* BinaryTreeBase<Key, T>::FindNode(
    const Key& key) const {
  Node* current = root_;
  while (current && current->key != key) {
    if (key < current->key) {
      current = current->left;
    } else {
      current = current->right;
    }
  }
  return current;
}

/*
 * Помогает в удаление узлов удаляя узел сдвигает нижележащий узел на место
 * удаляемого Если узел first является корнем дерева (т.е. у него нет родителя),
 * мы просто заменяем корень на second. Если first является левым дочерним узлом
 * своего родителя, мы обновляем ссылку на левый дочерний узел родителя, чтобы
 * указывать на second. Если first является правым дочерним узлом, обновляем
 * ссылку на правый дочерний узел. Если second не является nullptr, мы
 * устанавливаем его родителя равным родителю узла first.
 * */
template <typename Key, typename T>
void BinaryTreeBase<Key, T>::Transplant(Node* first, Node* second) {
  if (!first->parent) {
    root_ = second;
  } else if (first == first->parent->left) {
    first->parent->left = second;
  } else {
    first->parent->right = second;
  }
  if (second) {
    second->parent = first->parent;
  }
}

template <typename Key, typename T>
void BinaryTreeBase<Key, T>::ClearHelper(Node* node) {
  if (node) {
    ClearHelper(node->left);
    ClearHelper(node->right);
    delete node;
  }
}

// Работа с итераторами
template <typename Key, typename T>
BinaryTreeBase<Key, T>::Iterator::Iterator(Node* ptr,
                                           const BinaryTreeBase* tree)
    : current_(ptr), tree_(tree) {}

template <typename Key, typename T>
Key& BinaryTreeBase<Key, T>::Iterator::operator*() {
  return current_->key;
}

template <typename Key, typename T>
typename BinaryTreeBase<Key, T>::Iterator&
BinaryTreeBase<Key, T>::Iterator::operator--() {
  const BinaryTreeBase* tmp = tree_;
  if (!current_) {
    if (tree_ && tree_->root_) {
      current_ = tree_->MaxNode(tree_->root_);
    }
  } else if (current_->left) {
    current_ = tree_->MaxNode(current_->left);
  } else {
    Node* parent = current_->parent;
    while (parent && current_ == parent->left) {
      current_ = parent;
      parent = parent->parent;
    }
    if (!parent) {
      current_ = tree_->MaxNode(tmp->root_);
    } else {
      current_ = parent;
    }
  }
  return *this;
}

template <typename Key, typename T>
typename BinaryTreeBase<Key, T>::Iterator&
BinaryTreeBase<Key, T>::Iterator::operator++() {
  if (!current_) return *this;
  if (current_->right) {
    current_ = tree_->MinNode(current_->right);
  } else {
    Node* parent = current_->parent;
    while (parent && current_ == parent->right) {
      current_ = parent;
      parent = parent->parent;
    }
    current_ = parent;
  }
  return *this;
}

template <typename Key, typename T>
bool BinaryTreeBase<Key, T>::Iterator::operator==(const Iterator& other) const {
  return current_ == other.current_;
}

template <typename Key, typename T>
bool BinaryTreeBase<Key, T>::Iterator::operator!=(const Iterator& other) const {
  return current_ != other.current_;
}

template <typename Key, typename T>
typename BinaryTreeBase<Key, T>::Iterator BinaryTreeBase<Key, T>::Begin() {
  return Iterator(MinNode(root_), this);
}

template <typename Key, typename T>
typename BinaryTreeBase<Key, T>::Iterator BinaryTreeBase<Key, T>::End() {
  return Iterator(nullptr, this);
}

template <typename Key, typename T>
const typename BinaryTreeBase<Key, T>::Iterator BinaryTreeBase<Key, T>::Begin()
    const {
  return Iterator(MinNode(root_), this);
}

template <typename Key, typename T>
const typename BinaryTreeBase<Key, T>::Iterator BinaryTreeBase<Key, T>::End()
    const {
  return Iterator(nullptr, this);
}

template <typename Key, typename T>
typename BinaryTreeBase<Key, T>::Node*
BinaryTreeBase<Key, T>::Iterator::operator->() {
  return current_;
}

#endif  // SRC_BINARY_TREE_BASE_BINARY_TREE_BASE_TPP_
