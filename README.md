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
size is zero because it is empty. For the purposes of this tutorial, empty or
junk positions are represented by dots.

```c++
Deque<int> deque(5);   // [ . . . . . ]
deque.capacity();      // 5
deque.size();          // 0
```

Now, let's push back four values so it has one empty position.

```c++
deque.push_back(1);    // [ 1 . . . . ]
deque.push_back(2);    // [ 1 2 . . . ]
deque.push_back(3);    // [ 1 2 3 . . ]
deque.push_back(4);    // [ 1 2 3 4 . ]
deque.capacity();      // 5
deque.size();          // 4
```

When we push back an eighth value, the deque doubles the capacity and allocates
more space to fit more values. Even if elements are popped, the capacity does
not decrease.

```c++
deque.push_back(5);    // [ 1 2 3 4 5 . . . . . ]
deque.capacity();      // 10
deque.size();          // 5
deque.push_back(6);    // [ 1 2 3 4 5 6 . . . . ]
deque.pop_back();      // [ 1 2 3 4 5 . . . . . ]
deque.pop_back();      // [ 1 2 3 4 . . . . . . ]
```

With insertions or removals, a deque behaves like a vector or a stack at the
end. Whereas at the beginning, vectors need to shift every element to make room,
but for deques, everything remains at the same position and new elements are
wrapped when needed.

```c++
vector.push_front(0);  // [ 0 1 2 3 4 . . . . . ] - Shift elements
deque.push_front(0);   // [ 1 2 3 4 . . . . . 0 ] - Wrap elements
```

Since the deque uses a circular array, elements are not necessarily stored
internally starting at index 0. So, index of the first element is tracked to
allow wrapping.

```
  v- front
[ 1 2 3 4 5 6 . . . . . . . . . . ]
[ 1 2 3 4 5 6 . . . . . . . . . 0 ]
                         front -^
```

As more elements are pushed to the front, the position of the front moves. Each
insertion requires

```c++
                       //                     v- front
deque.pop_back();      // [ 1 2 3 . . . . . . 0 ]
deque.push_front(1);   // [ 1 2 3 . . . . . 1 0 ]
deque.push_front(2);   // [ 1 2 3 . . . . 2 1 0 ]
deque.push_front(3);   // [ 1 2 3 . . . 3 2 1 0 ]
deque.push_front(4);   // [ 1 2 3 . . 4 3 2 1 0 ]
deque.push_back(4);    // [ 1 2 3 4 . 4 3 2 1 0 ]
                       //             ^- front
```

Inserting another element fills the capacity, so more space is allocated. It may
be expected that the inserted value would go into the empty position with extra
space added at the end. However, this doesn't work when iterating starting at
the front as the empty values would appear in the middle of the data rather than
at the end. So, the elements must be moved so the front is at index 0. Most of
the time no reallocation is needed, so insertions are amortized O(1) time.

```c++
                       //             v- front
deque.push_back(5);    // [ 1 2 3 4 5 4 3 2 1 0 . . . . . . . . . . ] - Incorrect
deque.push_back(5);    // [ 4 3 2 1 0 1 2 3 4 5 . . . . . . . . . . ] - Correct
                       //   ^- front
```

To the user, index zero always refers to the first element and iterating is in
order of front to back.

```c++
deque.push_front(5);   // [ 4 3 2 1 0 1 2 3 4 5 . . . . . . . . . 5 ]
deque.push_front(6);   // [ 4 3 2 1 0 1 2 3 4 5 . . . . . . . . 6 5 ]

// These all loop from front to back
for (size_t i = 0; i < deque.size(); i++);
for (DequeIterator<int> it = deque.begin(); it != deque.end(); ++it);
for (const int& value : deque);

deque.to_string();     // "[ 6 5 4 3 2 1 0 1 2 3 4 5 ]"
std::cout << deque;    // "[ 6 5 4 3 2 1 0 1 2 3 4 5 ]"
```

Insertions and removals at the ends are not O(1) time like at the ends. Elements
are shifted to make room for the new elements. It is shifted in the direction
requiring the fewest shifts making it at most O(n / 2).

```c++
deque.erase(deque.end() - 3);                       // [ 4 3 2 1 0 1 2 4 5 . . . . . . . . . 6 5 ] Shift back left
deque.erase(deque.begin() + 2, deque.begin() + 4);  // [ 6 5 2 1 0 1 2 4 5 . . . . . . . . . . . ] Shift front right
deque.insert(deque.begin() + 1, 7);                 // [ 7 5 2 1 0 1 2 4 5 . . . . . . . . . . 6 ] Shift front left
deque.insert(deque.begin() + 6, 8);                 // [ 7 5 2 1 0 8 1 2 4 5 . . . . . . . . . 6 ] Shift back right
```
