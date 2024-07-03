#ifndef SRC_IMPLEMENTATIONS_s_LIST_H
#define SRC_IMPLEMENTATIONS_s_LIST_H

namespace s21 {

template <typename T>
class list {
 public:
  using value_type = T;
  using reference = T &;
  using const_reference = const T &;
  using size_type = size_t;

  /* Functions */
  list();
  explicit list(size_type n);
  list(const list &other);
  list(list &&other);
  list(std::initializer_list<value_type> const &items);
  ~list();
  list &operator=(list &&other);

  /* Access */
  const_reference front() const;
  const_reference back() const;

  /* Capacity */
  bool empty() const noexcept;
  size_type size() const noexcept;
  size_type max_size() const noexcept;

  /* Modifiers */
  void push_front(const_reference value);
  void push_back(const_reference value);
  void pop_front() noexcept;
  void pop_back() noexcept;
  void sort();
  void clear() noexcept;
  void reverse() noexcept;
  void swap(list &other) noexcept;
  void merge(list &other);
  void unique();

 private:
  struct Node {
    value_type data;
    Node *prev, *next;
  };
  Node *head_, *tail_, *end_;
  size_type size_;

 public:
  template <class value_type>
  class ListIterator {
   public:
    explicit ListIterator(Node *ptr) : ptr_(ptr){};

    ListIterator &operator++() {
      ptr_ = ptr_->next;
      return *this;
    }

    ListIterator operator++(int) {
      ListIterator postfix{*this};
      ++(*this);
      return postfix;
    }

    ListIterator &operator--() {
      ptr_ = ptr_->prev;
      return *this;
    }

    ListIterator operator--(int) {
      ListIterator postfix{*this};
      --(*this);
      return postfix;
    }

    bool operator==(ListIterator other) { return this->ptr_ == other.ptr_; }

    bool operator!=(ListIterator other) { return this->ptr_ != other.ptr_; }

    ListIterator operator+(const size_type value) {
      ListIterator iter{*this};
      for (size_type i{0}; i < value; ++i) ++iter;

      return iter;
    }

    ListIterator operator-(const size_type value) {
      ListIterator iter{*this};
      for (size_type i{0}; i < value; ++i) --iter;

      return iter;
    }

    reference operator*() {
      if (!ptr_) throw std::invalid_argument("Value is nullptr");

      return ptr_->data;
    }

    T *operator->() const { return ptr_->data; }

   private:
    Node *ptr_{nullptr};
    friend class list<T>;
  };

  template <class value_type>
  class ListConstIterator : public ListIterator<T> {
   public:
    ListConstIterator(ListIterator<T> other) : ListIterator<T>(other) {}
    const_reference operator*() { return ListIterator<T>::operator*(); }
  };

  using iterator = ListIterator<T>;
  using const_iterator = ListConstIterator<T>;

  /* List Iterators */
  iterator begin() noexcept;
  iterator end() noexcept;

  /* Modifiers */
  iterator insert(iterator pos, const_reference value);
  void erase(iterator pos);
  void splice(const_iterator pos, list &other);

  /* Part 3 */
  template <typename... Args>
  iterator insert_many(const_iterator pos, Args &&...args);

  template <typename... Args>
  void insert_many_back(Args &&...args);

  template <typename... Args>
  void insert_many_front(Args &&...args);

};  // class list

}  // namespace s21

#include "s_list.tpp"

#endif  //  SRC_IMPLEMENTATIONS_s_LIST_H
