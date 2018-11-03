#ifndef AA_DEQUE_ITERATOR_H_
#define AA_DEQUE_ITERATOR_H_

#include "deque.h"

template <typename T>
class DequeIterator {
public:
  DequeIterator(T*, size_t, size_t, size_t, size_t);
  DequeIterator(const DequeIterator<T>&);
  DequeIterator<T>& operator=(const DequeIterator&);

  T& operator*();
  T& operator[](int);
  T operator*() const;
  T operator[](int) const;
  DequeIterator<T>& operator++();
  DequeIterator<T>& operator--();
  DequeIterator<T> operator++(int);
  DequeIterator<T> operator--(int);
  DequeIterator<T>& operator+=(int);
  DequeIterator<T>& operator-=(int);
  DequeIterator<T> operator+(int) const;
  DequeIterator<T> operator-(int) const;
  int operator-(const DequeIterator<T>&) const;
  bool operator==(const DequeIterator<T>&) const;
  bool operator!=(const DequeIterator<T>&) const;
  bool operator<=(const DequeIterator<T>&) const;
  bool operator>=(const DequeIterator<T>&) const;
  bool operator<(const DequeIterator<T>&) const;
  bool operator>(const DequeIterator<T>&) const;

  template <typename U>
  friend DequeIterator<U> operator+(int, const DequeIterator<U>&);

private:
  T* container_;
  size_t capacity_;
  size_t size_;
  size_t front_;
  size_t index_;

  bool same_container(const DequeIterator<T>& it) const;

  template <typename> friend class Deque;
};

template <typename T> DequeIterator<T>::DequeIterator(T* container,
    size_t capacity, size_t size, size_t front, size_t index)
    : container_(container), capacity_(capacity), size_(size), front_(front),
      index_(index) {}

template <typename T> DequeIterator<T>& DequeIterator<T>::operator=(const DequeIterator& it) {
  container_ = it.container_;
  capacity_ = it.capacity_;
  size_ = it.size_;
  front_ = it.front_;
  index_ = it.index_;
  return *this;
}

template <typename T> T& DequeIterator<T>::operator*() {
  return container_[(index_ + front_) % capacity_];
}

template <typename T> T& DequeIterator<T>::operator[](int offset) {
  return container_[(index_ + front_ + offset) % capacity_];
}

template <typename T> T DequeIterator<T>::operator*() const {
  return operator*();
}

template <typename T> T DequeIterator<T>::operator[](int offset) const {
  return operator[](offset);
}

template <typename T> DequeIterator<T>& DequeIterator<T>::operator++() {
  index_++;
  return *this;
}

template <typename T> DequeIterator<T>& DequeIterator<T>::operator--() {
  index_--;
  return *this;
}

template <typename T> DequeIterator<T> DequeIterator<T>::operator++(int) {
  DequeIterator<T> temp = *this;
  index_++;
  return temp;
}

template <typename T> DequeIterator<T> DequeIterator<T>::operator--(int) {
  DequeIterator<T> temp = *this;
  index_--;
  return temp;
}

template <typename T> DequeIterator<T>& DequeIterator<T>::operator+=(int offset) {
  index_ += offset;
  return *this;
}

template <typename T> DequeIterator<T>& DequeIterator<T>::operator-=(int offset) {
  index_ -= offset;
  return *this;
}

template <typename T> DequeIterator<T> DequeIterator<T>::operator+(int offset) const {
  DequeIterator<T> it = *this;
  it.index_ += offset;
  return it;
}

template <typename T> DequeIterator<T> operator+(int offset, const DequeIterator<T>& it) {
  return it.operator+(offset);
}

template <typename T> DequeIterator<T> DequeIterator<T>::operator-(int offset) const {
  return operator+(-offset);
}

template <typename T> int DequeIterator<T>::operator-(const DequeIterator<T>& it) const {
  return ((int) index_) - ((int) it.index_);
}

template <typename T> bool DequeIterator<T>::operator==(const DequeIterator<T>& it) const {
  return same_container(it) && index_ == it.index_;
}

template <typename T> bool DequeIterator<T>::operator!=(const DequeIterator<T>& it) const {
  return !same_container(it) || index_ != it.index_;
}

template <typename T> bool DequeIterator<T>::operator<=(const DequeIterator<T>& it) const {
  return same_container(it) && index_ <= it.index_;
}

template <typename T> bool DequeIterator<T>::operator>=(const DequeIterator<T>& it) const {
  return same_container(it) && index_ >= it.index_;
}

template <typename T> bool DequeIterator<T>::operator<(const DequeIterator<T>& it) const {
  return same_container(it) && index_ < it.index_;
}

template <typename T> bool DequeIterator<T>::operator>(const DequeIterator<T>& it) const {
  return same_container(it) && index_ > it.index_;
}

template <typename T> bool DequeIterator<T>::same_container(const DequeIterator<T>& it) const {
  return container_ == it.container_ && capacity_ && it.capacity_
    && size_ == it.size_ && front_ == it.front_;
}

#endif
