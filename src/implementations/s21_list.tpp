namespace s21 {

template <typename value_type>
list<value_type>::list() : head_{nullptr}, tail_{nullptr}, size_{0} {
  end_ = new Node;
  end_->next = head_;
  end_->prev = tail_;
  end_->data = size_;
}

template <typename value_type>
list<value_type>::list(size_type n) : list<value_type>::list() {
  for (size_t i{0}; i < n; ++i) push_back(value_type());
}

template <typename value_type>
list<value_type>::list(const list &other) : list<value_type>::list() {
  if (this == &other) return;

  for (iterator it{other.head_}; it.ptr_ != other.end_; ++it)
    this->push_back(*it);
}

template <typename value_type>
list<value_type>::list(list &&other) : list<value_type>::list() {
  this->swap(other);
}

template <typename value_type>
list<value_type>::list(std::initializer_list<value_type> const &items)
    : list<value_type>::list() {
  for (const value_type &i : items) push_back(i);
}

template <typename value_type>
list<value_type>::~list() {
  clear();
  delete end_;
}

template <typename value_type>
typename list<value_type>::const_reference list<value_type>::front() const {
  return !head_ ? end_->data : head_->data;
}

template <typename value_type>
typename list<value_type>::const_reference list<value_type>::back() const {
  return !tail_ ? end_->data : tail_->data;
}

template <typename value_type>
typename list<value_type>::size_type list<value_type>::size() const noexcept {
  return size_;
}

template <typename value_type>
void list<value_type>::push_front(const_reference value) {
  Node *new_node{new Node};
  new_node->data = value;
  new_node->prev = end_;
  if (empty()) {
    new_node->next = end_;
    end_->next = end_->prev = head_ = tail_ = new_node;
  } else {
    new_node->next = head_;
    head_->prev = new_node;
    head_ = new_node;
    end_->next = head_;
  }
  ++size_;
}

template <typename value_type>
void list<value_type>::push_back(const_reference value) {
  Node *new_node{new Node};
  new_node->data = value;
  new_node->next = end_;
  if (empty()) {
    new_node->prev = end_;
    end_->next = end_->prev = head_ = tail_ = new_node;
  } else {
    new_node->prev = tail_;
    tail_->next = new_node;
    tail_ = new_node;
    end_->prev = tail_;
  }
  ++size_;
}

template <typename value_type>
void list<value_type>::pop_front() noexcept {
  if (empty()) return;

  if (size_-- == 1) {
    delete head_;
    head_ = tail_ = nullptr;
  } else {
    head_ = head_->next;
    delete head_->prev;
    head_->prev = end_;
  }
  end_->next = head_;
}

template <typename value_type>
void list<value_type>::pop_back() noexcept {
  if (empty()) return;

  if (size_-- == 1) {
    delete tail_;
    tail_ = head_ = nullptr;
  } else {
    tail_ = tail_->prev;
    delete tail_->next;
    tail_->next = end_;
  }
  end_->prev = tail_;
}

template <typename value_type>
bool list<value_type>::empty() const noexcept {
  return !head_ && !size_ ? true : false;
}

template <typename value_type>
void list<value_type>::clear() noexcept {
  while (!empty()) pop_back();
}

template <typename value_type>
void list<value_type>::reverse() noexcept {
  if (size_ < 2) return;

  iterator i{head_}, j{tail_};
  while (j != i && j + 1 != i) std::swap(*i++, *j--);
}

template <typename value_type>
void list<value_type>::swap(list &other) noexcept {
  if (this == &other) return;

  std::swap(this->head_, other.head_);
  std::swap(this->tail_, other.tail_);
  std::swap(this->size_, other.size_);
  std::swap(this->end_, other.end_);
}

template <typename value_type>
typename list<value_type>::size_type list<value_type>::max_size()
    const noexcept {
  return (std::numeric_limits<size_type>::max() / sizeof(Node) / 2);
}

template <typename value_type>
void list<value_type>::sort() {
  if (size_ < 2) return;

  Node *min_{nullptr};
  for (iterator it{head_}; it != end(); ++it) {
    min_ = it.ptr_;
    for (iterator j{it + 1}; j != end(); ++j) {
      min_ = (*j < min_->data) ? j.ptr_ : min_;
    }
    if (*it != min_->data && min_ != it.ptr_) std::swap(*it, min_->data);
  }
}

template <typename value_type>
void list<value_type>::merge(list &other) {
  if (this == &other || other.empty()) return;

  list<value_type> result;
  auto this_iter{this->begin()};
  auto othr_iter{other.begin()};
  while (this_iter != this->end() && othr_iter != other.end()) {
    if (*this_iter < *othr_iter) {
      result.push_back(*this_iter++);
    } else {
      result.push_back(*othr_iter++);
    }
  }
  if (this_iter == this->end()) {
    for (; othr_iter != other.end(); ++othr_iter) result.push_back(*othr_iter);
  } else if (othr_iter == other.end()) {
    for (; this_iter != this->end(); ++this_iter) result.push_back(*this_iter);
  }
  *this = std::move(result);
}

template <typename value_type>
void list<value_type>::unique() {
  if (size_ < 2) return;

  for (iterator i{head_->next}; i != end(); ++i) {
    if (*(i - 1) == *i) erase(i);
  }
}

template <typename value_type>
void list<value_type>::erase(iterator pos) {
  if (empty()) throw std::invalid_argument("List is empty");

  if (pos == end()) throw std::invalid_argument("You can't remove end()");

  if (pos == begin()) {
    pop_front();
  } else if (pos == --end()) {
    pop_back();
  } else {
    (pos - 1).ptr_->next = pos.ptr_->next;
    (pos + 1).ptr_->prev = pos.ptr_->prev;
    delete pos.ptr_;
    --size_;
  }
}

template <typename value_type>
typename list<value_type>::iterator list<value_type>::begin() noexcept {
  return !head_ ? iterator(end_) : iterator(head_);
};

template <typename value_type>
typename list<value_type>::iterator list<value_type>::end() noexcept {
  return iterator(end_);
};

template <typename value_type>
typename list<value_type>::iterator list<value_type>::insert(
    iterator pos, const_reference value) {
  if (pos == begin()) {
    push_front(value);
    return begin();
  } else if (pos == end()) {
    push_back(value);
    return --end();
  } else {
    iterator prv{pos.ptr_->prev};
    Node *new_node{new Node};
    new_node->data = value;
    new_node->prev = prv.ptr_;
    new_node->next = pos.ptr_;
    prv.ptr_->next = pos.ptr_->prev = new_node;
    ++size_;
    return iterator(new_node);
  }
}

template <typename value_type>
void list<value_type>::splice(const_iterator pos, list &other) {
  if (other.empty() || this == &other) return;

  if (this->empty()) {
    this->end_->prev = other.tail_;
    this->end_->next = other.head_;
    this->end_->data = other.size();
  }

  if (pos == this->end()) this->tail_ = other.tail_;

  if (pos == this->begin()) this->head_ = other.head_;

  (pos - 1).ptr_->next = other.head_;
  other.head_->prev = (pos - 1).ptr_;
  other.tail_->next = pos.ptr_;
  pos.ptr_->prev = other.tail_;
  this->size_ += other.size();
  other.head_ = other.tail_ = nullptr;
  other.size_ = 0;
}

template <typename value_type>
typename list<value_type>::list &list<value_type>::operator=(list &&other) {
  if (this != &other) {
    this->clear();
    this->swap(other);
  }
  return *this;
}

template <typename value_type>
template <typename... Args>
typename list<value_type>::iterator list<value_type>::insert_many(
    const_iterator pos, Args &&...args) {
  Node *retval{pos.ptr_};
  int i{0};
  for (const auto arg : {args...}) {
    if (!i++) {
      retval = insert(pos, arg).ptr_;
    } else {
      insert(pos, arg);
    }
  }

  return iterator(retval);
}

template <typename value_type>
template <typename... Args>
void list<value_type>::insert_many_back(Args &&...args) {
  for (const auto arg : {args...}) push_back(arg);
}

template <typename value_type>
template <typename... Args>
void list<value_type>::insert_many_front(Args &&...args) {
  iterator iter(begin());
  for (const auto arg : {args...}) insert(iter, arg);
}

}  // namespace s21
