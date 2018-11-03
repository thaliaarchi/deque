#ifndef AA_DEQUE_H_
#define AA_DEQUE_H_

#include <string>
#include <ostream>
#include <sstream>
#include <initializer_list>
#include <stdexcept>

#include "deque_iterator.h"

const size_t CAPACITY = 64;

template<typename T>
class Deque {
public:
  Deque();
  Deque(size_t);
  Deque(std::initializer_list<T>);
  ~Deque();
  Deque& operator=(const Deque&);

  void push_front(T);
  void push_back(T);
  void pop_front();
  void pop_back();
  void erase(DequeIterator<T>, DequeIterator<T>);
  void erase(DequeIterator<T>);
  void insert(DequeIterator<T>, T);
  void reserve(size_t);
  void resize(size_t, T = T());
  void clear();

  T& front();
  T& back();
  T& at(size_t);
  T& operator[](size_t);
  T front() const;
  T back() const;
  T at(size_t) const;
  T operator[](size_t) const;

  size_t capacity() const;
  size_t size() const;
  bool empty() const;
  std::string to_string() const;

  template <typename U>
  friend std::ostream& operator<<(std::ostream&, const Deque<U>&);

  DequeIterator<T> begin() const;
  DequeIterator<T> end() const;

private:
  T* container_;
  size_t capacity_;
  size_t size_;
  size_t front_;

  void check_nonempty();
  void reallocate();
  void shift_left(size_t, size_t, size_t);
  void shift_right(size_t, size_t, size_t);
};

template <typename T> Deque<T>::Deque() : Deque(CAPACITY) {}

template <typename T> Deque<T>::Deque(size_t capacity)
    : container_(new T[capacity]), capacity_(capacity), size_(0), front_(0) {}

template <typename T> Deque<T>::Deque(std::initializer_list<T> container)
    : Deque(2 * container.size()) {
  size_t i = 0;
  for (const T& value : container) {
    container_[i++] = value;
  }
  size_ = container.size();
}

template <typename T> Deque<T>::~Deque() {
  delete[] container_;
}

template <typename T> Deque<T>& Deque<T>::operator=(const Deque<T>& deque) {
  if (capacity_ < deque.capacity_) {
    delete[] container_;
    container_ = new T[deque.capacity_];
  }
  for (size_t i = 0; i < deque.size_; i++) {
    container_[i] = deque.container_[(i + deque.front_) % deque.capacity_];
  }
  capacity_ = deque.capacity_;
  size_ = deque.size_;
  front_ = 0;
  return *this;
}

template <typename T> void Deque<T>::push_front(T value) {
  front_ = (front_ - 1) % capacity_;
  container_[front_] = value;
  size_++;
  reallocate();
}

template <typename T> void Deque<T>::push_back(T value) {
  container_[(front_ + size_) % capacity_] = value;
  size_++;
  reallocate();
}

template <typename T> void Deque<T>::pop_front() {
  check_nonempty();
  size_--;
  front_ = (front_ + 1) % capacity_;
}

template <typename T> void Deque<T>::pop_back() {
  check_nonempty();
  size_--;
}

template <typename T> void Deque<T>::erase(DequeIterator<T> begin, DequeIterator<T> end) {
  if (begin.index_ >= size_ || end.index_ > size_ || begin.index_ > end.index_) {
    throw std::out_of_range("Deque: DequeIterator out of range");
  }
  size_t offset = end.index_ - begin.index_;
  if (begin.index_ + end.index_ < size_) {
    shift_right(0, begin.index_, offset);
    front_ += offset;
  }
  else {
    shift_left(end.index_, size_, offset);
  }
  size_ -= offset;
}

template <typename T> void Deque<T>::erase(DequeIterator<T> it) {
  return erase(it, it + 1);
}

template <typename T> void Deque<T>::insert(DequeIterator<T> it, T value) {

}

template <typename T> void Deque<T>::reserve(size_t capacity) {
  if (capacity <= capacity_) {
    return;
  }
  T* new_container = new T[capacity];
  for (size_t i = 0; i < size_; i++) {
    new_container[i] = container_[(i + front_) % capacity_];
  }
  delete[] container_;
  container_ = new_container;
  capacity_ = capacity;
  front_ = 0;
}

template <typename T> void Deque<T>::resize(size_t size, T value) {
  if (size > capacity_) {
    reserve(size);
  }
  for (size_t i = front_ + size_; i < front_ + size; i++) {
    container_[i % capacity_] = value;
  }
  size_ = size;
}

template <typename T> void Deque<T>::clear() {
  size_ = 0;
  front_ = 0;
}

template <typename T> T& Deque<T>::front() {
  check_nonempty();
  return container_[front_];
}

template <typename T> T& Deque<T>::back() {
  check_nonempty();
  return container_[(front_ + size_ - 1) % capacity_];
}

template <typename T> T& Deque<T>::at(size_t index) {
  if (index >= size_) {
    std::ostringstream out;
    out << "Deque: index (which is " << index
      << ") >= this->size() (which is " << size_ << ")";
    throw std::out_of_range(out.str());
  }
  return operator[](index);
}

template <typename T> T& Deque<T>::operator[](size_t index) {
  return container_[(front_ + index) % capacity_];
}

template <typename T> T Deque<T>::front() const {
  return front();
}

template <typename T> T Deque<T>::back() const {
  return back();
}

template <typename T> T Deque<T>::at(size_t index) const {
  return at(index);
}

template <typename T> T Deque<T>::operator[](size_t index) const {
  return operator[](index);
}

template <typename T> size_t Deque<T>::capacity() const {
  return capacity_;
}

template <typename T> size_t Deque<T>::size() const {
  return size_;
}

template <typename T> bool Deque<T>::empty() const {
  return size_ == 0;
}

template <typename T> std::string Deque<T>::to_string() const {
  std::ostringstream out;
  out << "[ ";
  for (const T& value : *this) {
    out << value << " ";
  }
  out << "]";
  return out.str();
}

template <typename T> std::ostream& operator<<(std::ostream& out,
    const Deque<T>& deque) {
  return out << deque.to_string();
}

template <typename T> DequeIterator<T> Deque<T>::begin() const {
  return DequeIterator<T>(container_, capacity_, size_, front_, 0);
}

template <typename T> DequeIterator<T> Deque<T>::end() const {
  return DequeIterator<T>(container_, capacity_, size_, front_, size_);
}

template <typename T> void Deque<T>::check_nonempty() {
  if (size_ == 0) {
    throw std::out_of_range("Deque: cannot access element in empty deque");
  }
}

template <typename T> void Deque<T>::reallocate() {
  if (size_ < capacity_) {
    return;
  }
  reserve(capacity_ * 2);
}

template <typename T> void Deque<T>::shift_left(size_t begin, size_t end, size_t offset) {
  for (size_t i = begin + front_; i < end + front_; i++) {
    container_[(i - offset) % capacity_] = container_[i % capacity_];
  }
}

template <typename T> void Deque<T>::shift_right(size_t begin, size_t end, size_t offset) {
  for (size_t i = end + front_ - 1; i >= begin + front_; i--) {
    container_[(i + offset) % capacity_] = container_[i % capacity_];
  }
}

#endif
