#ifndef SRC_IMPLEMENTATIONS_s_SET_H
#define SRC_IMPLEMENTATIONS_s_SET_H

#include "s_vector.h"
#include "tree.h"

namespace s21 {
template <typename Key>
class set : protected s21::RBtree<Key> {
 public:
  using key_type = Key;
  using value_type =
      typename RBtree<key_type>::TreeIterator<key_type>::value_type;
  using reference =
      typename RBtree<key_type>::TreeIterator<key_type>::reference;
  using const_reference = typename RBtree<key_type>::const_reference;
  using size_type = size_t;
  using iterator = typename RBtree<key_type>::TreeIterator<key_type>;
  using const_iterator = typename RBtree<key_type>::ConstTreeIterator<key_type>;

  set() : s21::RBtree<key_type>() {}
  set(std::initializer_list<value_type> const &items)
      : s21::RBtree<key_type>(items, 0) {}
  set(const set &s) : s21::RBtree<key_type>(s) {}
  set(set &&s) : s21::RBtree<Key>(std::move(s)) {}
  ~set() { s21::RBtree<key_type>::clear(); }

  // operator assignment move
  set &operator=(set &&s) {
    s21::RBtree<Key>::operator=(std::move(s));
    return *this;
  }

  // operator assignment copy
  set &operator=(const set &s) {
    s21::RBtree<key_type>::operator=(s);
    return *this;
  }

  /* Iterators */
  iterator begin() { return s21::RBtree<key_type>::begin(); }
  iterator end() { return s21::RBtree<key_type>::end(); }

  /* Capacity */
  bool empty() const { return s21::RBtree<key_type>::empty(); }
  size_type size() { return s21::RBtree<key_type>::size(); }
  size_type max_size() { return s21::RBtree<key_type>::max_size(); }

  /* Modifiers */
  void clear() { s21::RBtree<key_type>::clear(); }

  std::pair<iterator, bool> insert(const value_type &value) {
    return s21::RBtree<key_type>::insert(value, 0);
  }

  void erase(iterator pos) { s21::RBtree<key_type>::erase(pos); }
  void swap(set &other) { s21::RBtree<key_type>::swap(other); }
  void merge(set &other) { s21::RBtree<key_type>::merge(other, 0); }

  /* Lookup */
  iterator find(const key_type &key) {
    return s21::RBtree<key_type>::find(key);
  };
  bool contains(const key_type &key) {
    return s21::RBtree<key_type>::contains(key);
  }

  /*Part3*/
  template <class... Args>
  std::vector<std::pair<iterator, bool>> insert_many(Args &&...args) {
    std::initializer_list<value_type> items{std::forward<Args>(args)...};
    std::vector<std::pair<iterator, bool>> result;
    for (auto &n : items) {
      result.push_back(insert(n));
    }
    return result;
  }
};  // class set

}  // namespace s21

#endif  // SRC_IMPLEMENTATIONS_s_SET_H
