#ifndef SRC_IMPLEMENTATIONS_s_VECTOR_H
#define SRC_IMPLEMENTATIONS_s_VECTOR_H

namespace s21 {

template <typename T>
class vector {
 public:
  using value_type = T;
  using reference = T &;
  using const_reference = const T &;
  using iterator = T *;
  using const_iterator = const T *;
  using size_type = size_t;

  /* Member functions */
  vector();
  explicit vector(size_type n);
  explicit vector(std::initializer_list<value_type> const &items);
  vector(const vector<T> &v);
  vector(vector<T> &&v);
  ~vector();
  vector<T> &operator=(vector &&v);

  /* Element access */
  reference at(size_type pos);
  reference operator[](size_type pos);
  const_reference front();
  const_reference back();
  iterator data();

  /* Iterators */
  iterator begin();
  iterator end();

  /* Capacity */
  bool empty();
  size_type size();
  size_type max_size();
  void reserve(size_type size);
  size_type capacity();
  void shrink_to_fit();

  /* Modifiers */
  void clear();
  iterator insert(iterator pos, const_reference value);
  void erase(iterator pos);
  void push_back(T value);
  void pop_back();
  void swap(vector<T> &other);

  /* Part 3 */
  template <typename... Args>
  iterator insert_many(const_iterator pos, Args &&...args);

  template <typename... Args>
  void insert_many_back(Args &&...args);

 private:
  size_type sz{0};
  size_type ln{0};
  T *data_{nullptr};
  void shrink();  // for shrink_to_fit and reserve
};

}  // namespace s21

#include "s_vector.tpp"

#endif  // SRC_IMPLEMENTATIONS_s_VECTOR_H
