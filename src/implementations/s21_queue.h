#ifndef SRC_IMPLEMENTATIONS_s_QUEUE_H
#define SRC_IMPLEMENTATIONS_s_QUEUE_H

#include "s_stack.h"

namespace s21 {

template <typename T>
class queue : public s21::stack<T> {
 public:
  using value_type = typename s21::stack<T>::value_type;
  using reference = typename s21::stack<T>::reference;
  using const_reference = typename s21::stack<T>::const_reference;
  using size_type = typename s21::stack<T>::size_type;

  /* Member functions */
  queue() : s21::stack<T>() {}
  queue(std::initializer_list<value_type> const& items)
      : s21::stack<T>(items) {}
  explicit queue(const queue& other) : s21::stack<T>(other) {}
  queue(queue&& other) : s21::stack<T>(std::move(other)) {}
  ~queue() = default;

  queue& operator=(queue&& other) {
    s21::list<T>::operator=(std::move(other));
    return *this;
  }

  /* Queue Element access */
  const_reference front() const { return s21::list<T>::front(); }
  const_reference back() const { return s21::stack<T>::top(); }

  /* Modifiers */
  void pop() { s21::list<T>::pop_front(); }

  /* Part 3 */
  template <typename... Args>
  void insert_many_back(Args&&... args) {
    s21::stack<T>::insert_many_front(args...);
  }
};
}  // namespace s21

#endif  // SRC_IMPLEMENTATIONS_s_QUEUE_H
