# Deque

Deque is a reusable double-ended queue (deque) iterable container implemented as
a circular array. Elements can be added or removed at either end in amortized
O(1) time. Elements can be erased or inserted in the middle in O(n / 2) time.
This was created after explaining simplified deques to students for several
hours as a computer science TA.

## Deque\<T>

```c++
Deque();
Deque(size_t capacity);
Deque(const Deque<T>& deque);
Deque(std::initializer_list<T> container);
~Deque();
Deque& operator=(const Deque& deque);
Deque& operator=(std::initializer_list<T> container);

void push_front(T value);
void push_back(T value);
void pop_front();
void pop_back();
void erase(const DequeIterator<T>& begin, const DequeIterator<T>& end);
void erase(const DequeIterator<T>& it);
void insert(const DequeIterator<T>& it, T value);
void reserve(size_t capacity);
void resize(size_t size, T value = T());
void clear();

T& front();
T& back();
T& at(size_t index);
T& operator[](size_t index);
T front() const;
T back() const;
T at(size_t index) const;
T operator[](size_t index) const;

DequeIterator<T> begin() const;
DequeIterator<T> end() const;

size_t capacity() const;
size_t size() const;
bool empty() const;
std::string to_string() const;

friend std::ostream& operator<<(std::ostream& out, const Deque<T>& deque);
```

## DequeIterator\<T>

| Operation                                | Description         |
| ---------------------------------------- | ------------------- |
| *Iter* a(b)       <br> a = b             | Copy                |
| a*                                       | Dereference         |
| a[n]                                     | Offset dereference  |
| a++    <br> ++a                          | Increment           |
| a--    <br> --a                          | Decrement           |
| a += n <br> a -= n                       | Compound assignment |
| a + n  <br> n + a <br> a - n             | Integer arithmetic  |
| a - b                                    | Iterator difference |
| a == b <br> a != b                       | Equality            |
| a <= b <br> a >= b <br> a < b <br> a > b | Inequality          |

Where *Iter* is the DequeIterator\<T> type, a and b are objects of this iterator
type, and n is an integer value.
