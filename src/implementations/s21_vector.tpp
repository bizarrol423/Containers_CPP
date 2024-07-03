#include "s_vector.h"

namespace s21 {

template <typename T>
vector<T>::~vector() {
  if (data_) delete[] data_;

  data_ = nullptr;
}

template <typename T>
vector<T>::vector(vector &&other) : sz{other.sz}, ln{other.ln}, data_{nullptr} {
  std::swap(data_, other.data_);
}

template <typename T>
vector<T>::vector() : sz{4}, ln{0} {
  data_ = new T[4];
}

template <typename T>
vector<T>::vector(size_type volume) : sz{volume}, ln{0} {
  if (volume < 1) {
    throw std::invalid_argument("Error, size can't be 0 or less");
  }
  data_ = new T[volume];
}

template <typename T>
vector<T>::vector(std::initializer_list<T> const &items) : sz{4}, ln{0} {
  while (items.size() > sz) sz *= 2;

  data_ = new T[sz];
  for (auto &i : items) data_[ln++] = i;
}

template <typename T>
typename vector<T>::reference vector<T>::at(size_type pos) {
  if (pos > ln - 1) {
    throw std::out_of_range("Error, no element with such index");
  }
  return data_[pos];
}

template <typename T>
typename vector<T>::const_reference vector<T>::front() {
  return data_[0];
}

template <typename T>
typename vector<T>::const_reference vector<T>::back() {
  return data_[ln - 1];
}

template <typename T>
typename vector<T>::iterator vector<T>::data() {
  return data_;
}

template <typename T>
bool vector<T>::empty() {
  return ln == 0 ? 1 : 0;
}

template <typename T>
typename vector<T>::size_type vector<T>::capacity() {
  return sz;
}

template <typename T>
typename vector<T>::size_type vector<T>::size() {
  return ln;
}

template <typename T>
void vector<T>::swap(vector<T> &other) {
  std::swap(sz, other.sz);
  std::swap(ln, other.ln);
  std::swap(data_, other.data_);
}

template <typename T>
void vector<T>::shrink() {
  iterator newdata = new T[sz]();
  for (size_t i{0}; i < ln; ++i) newdata[i] = data_[i];

  std::swap(data_, newdata);
  delete[] newdata;
}

template <typename T>
void vector<T>::shrink_to_fit() {
  sz = ln;
  shrink();
}

template <typename T>
typename vector<T>::reference vector<T>::operator[](size_type pos) {
  return at(pos);
}

template <typename T>
void vector<T>::reserve(size_type size) {
  if (size < sz) {
    throw std::invalid_argument(
        "Error: new size of reserve is smaller than current");
  }

  sz = size;
  shrink();
}

template <typename T>
void vector<T>::push_back(T value) {
  if (ln == sz) reserve(sz * 2);

  data_[ln++] = value;
}

template <typename T>
void vector<T>::pop_back() {
  if (!ln) return;

  data_[--ln] = 0;
}

template <typename T>
void vector<T>::clear() {
  ln = 0;
  if (data_) delete[] data_;

  data_ = new T[sz]();
}

template <typename T>
typename vector<T>::size_type vector<T>::max_size() {
  return static_cast<size_type>(pow(2.0, 64.0) / static_cast<T>(sizeof(T))) /
             2 -
         1;
}

template <typename T>
void vector<T>::erase(iterator iter) {
  if (!ln) return;

  std::move(iter + 1, data_ + ln--, iter);
}

template <typename T>
typename vector<T>::iterator vector<T>::begin() {
  return data_;
}

template <typename T>
typename vector<T>::iterator vector<T>::end() {
  return data_ + ln;
}

template <typename T>
vector<T> &vector<T>::operator=(vector &&other) {
  sz = other.sz;
  ln = other.ln;
  delete[] data_;
  data_ = nullptr;
  std::swap(data_, other.data_);
  return *this;
}

template <typename T>
typename vector<T>::iterator vector<T>::insert(iterator iter,
                                               const_reference value) {
  return insert_many(iter, value);
}

template <typename T>
template <typename... Args>
typename vector<T>::iterator vector<T>::insert_many(const_iterator pos,
                                                    Args &&...args) {
  if (pos < begin() || pos > end()) {
    throw std::out_of_range("Pos is outside of array");
  }

  size_type pos_idx(pos - begin());
  const size_type args_size = sizeof...(Args);
  if (!args_size) return iterator(data_ + pos_idx);

  size_type last_elem_idx{ln - 1};
  size_type args_counter{last_elem_idx - pos_idx + 1};
  const value_type args_data[args_size] = {args...};
  if (ln + args_size > sz) reserve(sz * 2);

  for (size_type i = 0; i <= args_counter; ++i)
    data_[last_elem_idx + args_size - i] = data_[last_elem_idx - i];

  for (size_type i = 0; i < args_size; ++i) data_[pos_idx + i] = args_data[i];

  ln += args_size;
  return iterator(data_ + pos_idx);
}

template <typename T>
template <typename... Args>
void vector<T>::insert_many_back(Args &&...args) {
  for (const auto arg : {args...}) push_back(arg);
}

}  // namespace s21
