#ifndef SRC_IMPLEMENTATIONS_s_MULTISET_H
#define SRC_IMPLEMENTATIONS_s_MULTISET_H

#include "s_set.h"
#include "s_vector.h"

namespace s21 {
template <typename Key>
class multiset : public s21::set<Key> {
 public:
  using key_type = Key;
  using value_type = Key;
  using reference = value_type&;
  using const_reference = const value_type&;
  using size_type = size_t;
  using iterator = typename RBtree<key_type>::TreeIterator<key_type>;
  using const_iterator = typename RBtree<key_type>::ConstTreeIterator<key_type>;

  multiset() : s21::set<key_type>() {}

  multiset(std::initializer_list<value_type> const& items) {
    for (const value_type& item : items) s21::RBtree<key_type>::insert(item, 1);
  }

  multiset(const multiset& ms) : s21::set<key_type>(ms) {}
  multiset(multiset&& ms) : s21::set<key_type>(std::move(ms)) {}
  ~multiset() = default;

  multiset& operator=(multiset&& ms) {
    s21::RBtree<key_type>::operator=(std::move(ms));
    return *this;
  }

  multiset& operator=(const multiset& ms) {
    s21::RBtree<key_type>::operator=(ms);
    return *this;
  }

  /* Modifiers */
  std::pair<iterator, bool> insert(const value_type& value) {
    return s21::RBtree<key_type>::insert(value, 1);
  }

  void merge(multiset& other) { s21::RBtree<key_type>::merge(other, 1); }

  /* Lookup */
  size_type count(const key_type& key) {
    size_type count = 0;
    for (auto it = s21::set<key_type>::begin(); it != s21::set<key_type>::end();
         ++it) {
      if (*it == key) ++count;
    }
    return count;
  }

  std::pair<iterator, iterator> equal_range(const key_type& key) {
    iterator first = s21::set<key_type>::find(key);
    size_type count{this->count(key)};
    iterator last{first};
    while (count--) ++last;

    return std::pair<iterator, iterator>(first, last);
  }

  iterator lower_bound(const key_type& key) { return equal_range(key).first; }
  iterator upper_bound(const key_type& key) { return equal_range(key).second; }

  /*Part3*/
  template <class... Args>
  std::vector<std::pair<iterator, bool>> insert_many(Args&&... args) {
    std::initializer_list<value_type> items{std::forward<Args>(args)...};
    std::vector<std::pair<iterator, bool>> result;
    for (auto& n : items) {
      result.push_back(insert(n));
    }
    return result;
  }
};
}  // namespace s21

#endif  // SRC_IMPLEMENTATIONS_s_MULTISET_H
