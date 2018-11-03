# Deque

Deque is a reusable double-ended queue (deque, pronounced "deck") iterable
container implemented as a circular array. Elements can be added or removed at
either end in amortized O(1) time. Elements can be erased or inserted in the
middle in O(n / 2) time. This was created after explaining simplified deques to
students for several hours as a computer science TA.

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

## Circular Array Algorithm

First, we'll create a `Deque` instance with an initial capacity of eight. The
size is zero because it is empty. For the purposes of this explanation, empty
positions are represented by dots.

```c++
Deque<int> deque(8);  // [ . . . . . . . . ]
deque.capacity();     // 8
deque.size();         // 0
```

Now, let's push back seven values so it only has one empty position.

```c++
deque.push_back(1);   // [ 1 . . . . . . . ]
deque.push_back(2);   // [ 1 2 . . . . . . ]
deque.push_back(3);   // [ 1 2 3 . . . . . ]
deque.push_back(4);   // [ 1 2 3 4 . . . . ]
deque.push_back(5);   // [ 1 2 3 4 5 . . . ]
deque.push_back(6);   // [ 1 2 3 4 5 6 . . ]
deque.push_back(7);   // [ 1 2 3 4 5 6 7 . ]
deque.capacity();     // 8
deque.size();         // 7
```

When we push back an eighth value, the deque doubles the capacity and allocates
more space to fit more values. Even if elements are popped, the capacity does
not decrease.

```c++
deque.push_back(8);   // [ 1 2 3 4 5 6 7 8 . . . . . . . . ]
deque.capacity();     // 16
deque.size();         // 8
deque.pop_back();     // [ 1 2 3 4 5 6 7 . . . . . . . . . ]
deque.pop_back();     // [ 1 2 3 4 5 6 . . . . . . . . . . ]
```

Up to this point, the deque has only behaved like a vector or a stack - only
inserting and removing at the end.

*To be continued.*
