#ifndef SRC_IMPLEMENTATIONS_s_STACK_H
#define SRC_IMPLEMENTATIONS_s_STACK_H

#include "s_list.h"

namespace s21 {

template <typename T>
class stack : protected s21::list<T> {
 public:
  using value_type = typename s21::list<T>::value_type;
  using reference = typename s21::list<T>::reference;
  using const_reference = typename s21::list<T>::const_reference;
  using size_type = typename s21::list<T>::size_type;

  /* Member functions */
  stack() : s21::list<T>() {}
  stack(std::initializer_list<value_type> const& items) : s21::list<T>(items) {}
  explicit stack(const stack& other) : s21::list<T>(other) {}
  stack(stack&& other) : s21::list<T>(std::move(other)) {}
  ~stack() = default;

  stack& operator=(stack&& other) {
    s21::list<T>::operator=(std::move(other));
    return *this;
  }

  /* Element access */
  const_reference top() const { return s21::list<T>::back(); }

  /* Capacity */
  bool empty() const { return s21::list<T>::empty(); }
  size_type size() const { return s21::list<T>::size(); }

  /* Modifiers */
  void push(const_reference value) { s21::list<T>::push_back(value); }
  void pop() { s21::list<T>::pop_back(); }
  void swap(stack& other) noexcept { s21::list<T>::swap(other); }

  /* Part 3 */
  template <typename... Args>
  void insert_many_front(Args&&... args) {
    s21::list<T>::insert_many_back(args...);
  }
};
}  // namespace s21

#endif  // SRC_IMPLEMENTATIONS_s_STACK_H
