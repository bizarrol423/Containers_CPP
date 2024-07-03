#ifndef SRC_IMPLEMENTATIONS_MAP_s_MAP_H
#define SRC_IMPLEMENTATIONS_MAP_s_MAP_H

#include "s_vector.h"
#include "tree.h"

namespace s21 {
template <typename Key = int, typename T = int>
class map {
 public:
  // Member type
  using key_type = Key;
  using mapped_type = T;
  using value_type = std::pair<key_type, mapped_type>;
  using reference = value_type &;
  using const_reference = const value_type &;
  using iterator = typename RBtree<value_type>::TreeIterator<value_type>;
  using const_iterator = typename RBtree<key_type>::ConstTreeIterator<key_type>;
  using size_type = size_t;

  // Member functions
  map() : tree_(){};

  map(std::initializer_list<value_type> const &items) : tree_(items, false) {
    for (const value_type &item : items) {
      tree_.insert(item, 0);
    }
  }

  map(const map &m) : tree_(m.tree_) {}

  map(map &&m) : tree_() { tree_.swap(m.tree_); }

  ~map() { tree_.clear(); }

  map &operator=(map &m) {
    this->clear();
    for (auto it = m.begin(); it != m.end(); it++) {
      this->tree_.insert(*it, 0);
    }
    return *this;
  }

  map &operator=(map &&m) {
    tree_.clear();
    tree_.swap(m.tree_);
    return *this;
  }

  // Element access
  T &at(const Key &key) {
    for (auto i = begin(); i != end(); i++) {
      if (key == i->first) {
        return i->second;
      }
    }
    throw std::invalid_argument("\"s_map::at\" thrown in the test body.");
  }

  T &operator[](const Key &key) {
    if (size() == 0) {
      auto ret = tree_.insert(std::pair(key, NULL), 0);
      return ret.first->second;
    }
    auto i = begin();
    for (; i != end(); ++i) {
      if (i->first == key) {
        return i->second;
      }
    }
    auto ret = tree_.insert(std::pair(key, NULL), 0);
    return ret.first->second;
  }

  // iterators
  iterator begin() { return tree_.begin(); }

  iterator end() { return tree_.end(); }

  // Capacity
  bool empty() { return !(this->size()); }

  size_type size() { return tree_.size(); }

  size_type max_size() const noexcept { return tree_.max_size(); }

  // Modifiers
  void clear() { this->tree_.clear(); }

  std::pair<iterator, bool> insert(const Key &key, const T &obj) {
    if (size() == 0) {
      tree_.insert(std::pair(key, obj), 0);

      return std::pair(begin(), 1);
    }
    for (auto i = begin(); i != end(); i++) {
      if (i->first == key) {
        return std::pair(i, 0);
      }
    }
    tree_.insert(std::pair(key, obj), 0);
    auto i = begin();
    for (; i != end(); i++) {
      if (i->first == key) {
        break;
      }
    }
    return std::pair(i, 1);
  }

  std::pair<iterator, bool> insert_or_assign(const Key &key, const T &obj) {
    for (auto i = begin(); i != end(); i++) {
      if (i->first == key) {
        i->second = obj;
        return std::pair(i, 0);
      }
    }
    tree_.insert(std::pair(key, obj), 0);
    auto i = begin();
    for (; i != end(); i++) {
      if (i->first == key) {
        break;
      }
    }
    return std::pair(i, 1);
  }

  void erase(iterator pos) { tree_.erase(pos); }

  void swap(map &other) { tree_.swap(other.tree_); }

  void merge(map &other) {
    for (auto i = other.begin(); i != other.end(); i++) {
      if (!(contains(i->first))) {
        tree_.insert((*i), 0);
        other.erase(i);
      }
    }
  }

  // Lookup
  bool contains(const Key &key) {
    for (auto i = begin(); i != end(); i++) {
      if (i->first == key) {
        return true;
      }
    }
    return false;
  }

  // part3*
  template <typename... key_type, typename... mapped_type>
  std::vector<std::pair<iterator, bool>> insert_many(
      std::pair<key_type, mapped_type> &&...args) {
    std::vector<std::pair<iterator, bool>> ret;
    for (const auto &arg : {args...}) {
      ret.push_back(insert(arg.first, arg.second));
    }
    return ret;
  }

  // other function
  iterator find(key_type key) {
    for (auto i = begin(); i != end(); i++) {
      if (i->first == key) {
        return i;
      }
    }
  }

 private:
  s21::RBtree<std::pair<key_type, mapped_type>> tree_;
};
}  // namespace s21

#endif  // SRC_IMPLEMENTATIONS_MAP_s_MAP_H
