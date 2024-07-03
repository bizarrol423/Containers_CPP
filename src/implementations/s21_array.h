#ifndef SRC_IMPLEMENTATIONS_s_ARRAY_H
#define SRC_IMPLEMENTATIONS_s_ARRAY_H

namespace s21 {

template <typename T, std::size_t N>
class array {
 public:
  using value_type = T;
  using reference = T &;
  using const_reference = const T &;
  using iterator = T *;
  using const_iterator = const T *;
  using size_type = size_t;

  /* Member functions */
  array() {}

  explicit array(std::initializer_list<T> const &items) {
    size_type i{0};
    for (auto j = items.begin(); j != items.end(); ++j) arr_data[i++] = *j;
  }

  array(const array &other) {
    if (this == &other) return;

    for (size_type i = 0; i < arr_size; ++i) arr_data[i] = other.arr_data[i];
  }

  array(array &&other) { *this = std::move(other); }

  ~array() {}

  array<T, N> &operator=(array &&other) {
    if (this != &other)
      std::move(other.arr_data, other.arr_data + arr_size, arr_data);

    return *this;
  }

  /* Element access */
  typename array<T, N>::reference at(size_type pos) {
    if (pos >= arr_size)
      throw std::length_error("requested position >= array size");

    return arr_data[pos];
  }

  reference operator[](size_type pos) { return arr_data[pos]; }
  const_reference front() const { return arr_data[0]; }
  const_reference back() const { return arr_data[arr_size - 1]; }
  iterator data() { return arr_data; }

  /* Iterators */
  iterator begin() { return arr_data; }
  iterator end() { return arr_data + arr_size; }

  /* Capacity */
  bool empty() const { return arr_size == 0; }
  size_type size() const { return arr_size; }
  size_type max_size() const { return arr_size; }

  /* Modifiers */
  void swap(array &other) {
    if (this == &other) return;

    std::swap(arr_size, other.arr_size);
    std::swap(arr_data, other.arr_data);
  }

  void fill(const_reference value) {
    if (!arr_size) return;

    for (size_type i{0}; i < arr_size; ++i) arr_data[i] = value;
  }

 private:
  T arr_data[N];
  size_type arr_size = N;

};  // class array

}  // namespace s21

#endif  // SRC_IMPLEMENTATIONS_s_ARRAY_H
