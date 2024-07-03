#ifndef SRC_IMPLEMENTATIONS_TREE_H
#define SRC_IMPLEMENTATIONS_TREE_H

#include <limits>

namespace s21 {
template <class Key = int>
class RBtree {
  struct tree_node {
    explicit tree_node(Key data = Key(), tree_node* parent = nullptr,
                       tree_node* left = nullptr, tree_node* right = nullptr)
        : data(data), parent(parent), left(left), right(right){};
    Key data;
    tree_node* parent;
    tree_node* left;
    tree_node* right;
  };

 public:
  using key_type = Key;
  using size_type = size_t;
  using const_reference = const key_type&;

  RBtree() : tree_root_{nullptr}, nodes_count_{0} {}
  ~RBtree() { clear(tree_root_); }
  void clear() { clear(tree_root_); }

  void clear(tree_node* root) {
    if (!root) return;

    clear(root->left);
    clear(root->right);
    RemoveNode(root->data);
  }

  // constructor initializer_list
  RBtree(std::initializer_list<key_type> const& init, bool duplicate)
      : tree_root_{nullptr}, nodes_count_{0} {
    for (auto& it : init) InsertNode(it, duplicate);
  }

  // constructor copy
  RBtree(const RBtree& other) : tree_root_{nullptr}, nodes_count_{0} {
    *this = other;
  }

  // constructor move
  RBtree(RBtree&& other) noexcept : tree_root_{nullptr}, nodes_count_{0} {
    swap(other);
  }

  // operator assignment copy
  RBtree& operator=(const RBtree& other) {
    if (this == &other || other.empty()) return *this;

    clear();
    for (auto it = other.begin(); it != other.end(); ++it) InsertNode(*it, 1);

    return *this;
  }

  // operator assignment move
  RBtree& operator=(RBtree&& other) noexcept {
    if (this == &other) return *this;

    swap(other);
    other.clear();
    return *this;
  }

  RBtree::tree_node* GetRoot() { return tree_root_; }

  template <class key_type>
  class TreeIterator {
   public:
    using value_type = Key;
    using reference = value_type&;
    using pointer = value_type*;
    using iterator = TreeIterator;

    explicit TreeIterator(tree_node* node) : current(node) {}

    reference operator*() const { return current->data; }

    pointer operator->() const { return &(current->data); }

    iterator& operator++() {
      if (current->right) {
        current = current->right;
        while (current->left) current = current->left;

      } else {
        tree_node* parent{current->parent};
        while (parent && current == parent->right) {
          current = parent;
          parent = parent->parent;
        }
        current = parent;
      }
      return *this;
    }

    iterator operator++(int) {
      iterator temp = *this;
      ++(*this);
      return temp;
    }

    iterator& operator--() {
      if (current->left) {
        current = current->left;
        while (current->right) current = current->right;

      } else {
        tree_node* parent = current->parent;
        while (parent && current == parent->left) {
          current = parent;
          parent = parent->parent;
        }
        current = parent;
      }
      return *this;
    }

    iterator operator--(int) {
      iterator temp = *this;
      --(*this);
      return temp;
    }

    bool operator==(const iterator& other) const {
      return current == other.current;
    }

    bool operator!=(const iterator& other) const { return !(*this == other); }

   private:
    tree_node* current;
    friend class RBtree<value_type>;
  };  // class TreeIterator

  template <class key_type>
  class ConstTreeIterator : public TreeIterator<key_type> {
   public:
    ConstTreeIterator(TreeIterator<key_type> other)
        : TreeIterator<key_type>(other) {}
    const_reference operator*() { return TreeIterator<key_type>::operator*(); }
  };

  using iterator = TreeIterator<key_type>;
  using const_iterator = ConstTreeIterator<key_type>;

  RBtree<key_type>::iterator begin() const {
    tree_node* current{tree_root_};

    while (current && current->left) current = current->left;

    return iterator(current);
  }

  RBtree<key_type>::iterator end() const {
    tree_node* current{tree_root_};
    while (current->right) current = current->right;

    return ++iterator(current);
  }

  RBtree<key_type>::iterator find(const key_type& key) {
    tree_node* current{FindNodeByKey(tree_root_, key)};
    return iterator(current);
  }

  bool contains(const key_type& key) {
    return FindNodeByKey(tree_root_, key) != nullptr;
  }

  bool empty() const { return nodes_count_ == 0; }

  void erase(iterator pos) { RemoveNode(*pos); }

  std::pair<iterator, bool> insert(const key_type& value, bool duplicate) {
    bool result{InsertNode(value, duplicate)};
    iterator it = end();
    if (result) it = find(value);

    return std::pair<iterator, bool>(it, result);
  }

  void swap(RBtree& other) {
    std::swap(tree_root_, other.tree_root_);
    std::swap(nodes_count_, other.nodes_count_);
  }

  size_type size() const { return nodes_count_; }

  size_type max_size() const {
    size_type size =
        std::numeric_limits<size_type>::max() / sizeof(tree_node) / 2.5;
    size -= 13;
    return size;
  }

  void merge(RBtree& other, bool duplicate) {
    RBtree<key_type> temp(other);
    for (auto it = temp.begin(); it != temp.end(); ++it) {
      if (!find(*it).current || duplicate) {
        insert(*it, duplicate);
        other.erase(it);
      }
    }
  }

 private:
  tree_node* tree_root_;
  size_type nodes_count_;

  bool InsertNode(key_type data, bool duplicate) {
    if (!tree_root_) {
      tree_root_ = new tree_node(data);
      nodes_count_++;
      return true;
    }
    if (duplicate || !find(data).current) {
      tree_node* current{tree_root_};
      tree_node* parent{nullptr};
      while (current) {
        parent = current;
        if (data < current->data) {
          current = current->left;
        } else {
          current = current->right;
        }
      }
      if (data < parent->data) {
        parent->left = new tree_node(data);
        parent->left->parent = parent;
        nodes_count_++;
      } else {
        parent->right = new tree_node(data);
        parent->right->parent = parent;
        nodes_count_++;
      }
      return true;
    }
    return false;
  }

  RBtree::tree_node* FindMin(tree_node* current) {
    if (current) {
      while (current->left) current = current->left;
    }

    return current;
  }

  void RemoveNode(key_type data) { tree_root_ = RemoveNode(tree_root_, data); }

  RBtree::tree_node* RemoveNode(tree_node* current, key_type data) {
    if (!current) return nullptr;

    if (data < current->data) {
      current->left = RemoveNode(current->left, data);
    } else if (data > current->data) {
      current->right = RemoveNode(current->right, data);
    } else if (data == current->data) {
      if (!current->left && !current->right) {
        delete current;
        current = nullptr;
      } else if (!current->left || !current->right) {
        tree_node* temp{current};
        current->left == nullptr ? current = current->right
                                 : current = current->left;
        current->parent = temp->parent;
        delete temp;
      } else {
        tree_node* successor{FindMin(current->right)};
        current->data = successor->data;
        current->right = RemoveNode(current->right, successor->data);
      }
      nodes_count_--;
    }
    return current;
  }

  RBtree::tree_node* FindNodeByKey(tree_node* current, key_type data) {
    if (!current || data == current->data) {
      return current;
    } else if (data < current->data) {
      return FindNodeByKey(current->left, data);
    } else {
      return FindNodeByKey(current->right, data);
    }
  }

};  // class RBtree

};  // namespace s21

#endif  //  SRC_IMPLEMENTATIONS_TREE_H
