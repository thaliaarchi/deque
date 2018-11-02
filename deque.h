#ifndef AA_DEQUE_H_
#define AA_DEQUE_H_

#include <string>
#include <ostream>
#include <sstream>

const size_t CAPACITY = 64;

template<typename T>
class Deque {
public:
  Deque();
  Deque(size_t);
  ~Deque();
  Deque& operator=(const Deque&);

  void push_front(T);
  void push_back(T);
  void pop_front();
  void pop_back();
  T& front();
  T& back();
  T& at(size_t);
  T front() const;
  T back() const;
  T at(size_t) const;
  size_t size() const;
  std::string to_string() const;

  template <typename U>
  friend std::ostream& operator<<(std::ostream&, const Deque<U>&);

  //DequeIterator<T> insert(DequeIterator<T>, T);
  //void remove(T);
  //T& operator[](size_t);
  //DequeIterator<T> begin();
  //DequeIterator<T> end();

private:
  T* container_;
  size_t capacity_;
  size_t size_;
  size_t start_;

  void check_nonempty();
  void reallocate();
};

template <typename T> Deque<T>::Deque() : Deque(CAPACITY) {}

template <typename T> Deque<T>::Deque(size_t capacity)
  : container_(new T[capacity]), capacity_(capacity), size_(0), start_(0) {}

template <typename T> Deque<T>::~Deque() {
  delete[] container_;
}

template <typename T> Deque<T>& Deque<T>::operator=(const Deque<T>& deque) {
  delete[] container_;
  if (capacity_ != deque.capacity_) {
    container_ = new T[deque.capacity_];
  }
  for (size_t i = 0; i < deque.size_; i++) {
    container_[i] = deque.container_[(i + deque.start_) % deque.capacity_];
  }
  capacity_ = deque.capacity_;
  size_ = deque.size_;
  start_ = 0;
  return *this;
}

template <typename T> void Deque<T>::push_front(T value) {
  reallocate();
  start_ = (start_ - 1) % capacity_;
  container_[start_] = value;
  size_++;
}

template <typename T> void Deque<T>::push_back(T value) {
  reallocate();
  container_[(start_ + size_) % capacity_] = value;
  size_++;
}

template <typename T> void Deque<T>::pop_front() {
  check_nonempty();
  size--;
  start_ = (start_ + 1) % capacity_;
}

template <typename T> void Deque<T>::pop_back() {
  check_nonempty();
  size_--;
}

template <typename T> T& Deque<T>::front() {
  check_nonempty();
  return container_[start_];
}

template <typename T> T& Deque<T>::back() {
  check_nonempty();
  return container_[(start_ + size_ - 1) % capacity_];
}

template <typename T> T& Deque<T>::at(size_t index) {
  if (index >= size_) {
    throw "Index out of bounds";
  }
  return container_[(start_ + index) % capacity_];
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

template <typename T> size_t Deque<T>::size() const {
  return size_;
}

template <typename T> std::string Deque<T>::to_string() const {
  std::ostringstream out;
  out << "[";
  for (size_t i = 0; i < size_; i++) {
    out << " " << container_[(i + start_) % capacity_];
  }
  out << " ]";
  return out.str();
}

template <typename T> std::ostream& operator<<(std::ostream& out,
    const Deque<T>& deque) {
  return out << deque.to_string();
}

template <typename T> void Deque<T>::check_nonempty() {
  if (size_ == 0) {
    throw "Deque contains no elements";
  }
}

template <typename T> void Deque<T>::reallocate() {
  if (size_ < capacity_) {
    return;
  }
  size_t new_capacity = capacity_ * 2;
  T* new_container = new T[new_capacity];
  for (size_t i = 0; i < size_; i++) {
    new_container[i] = container_[(i + start_) % capacity_];
  }
  delete[] container_;
  container_ = new_container;
  capacity_ = new_capacity;
  start_ = 0;
}

#endif
