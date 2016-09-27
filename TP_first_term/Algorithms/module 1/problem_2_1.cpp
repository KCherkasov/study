#include <cstdio>
#include <cassert>
#include <algorithm>

const size_t BASE_CAPACITY = 2;
const size_t GROW_FACTOR = 2;

template<class T>
class Array {
  public:
    Array(const size_t& capacity = BASE_CAPACITY): _size(0), _capacity(capacity) { if ( _capacity > 0) _buffer = new T[capacity]; else _buffer = NULL; }
    ~Array() { delete[] _buffer; }
    void add(const T& new_element);
    size_t size() { return _size; }
    size_t capacity() { return _capacity; }
    bool empty() { return _capacity == 0; }
    T max();
    size_t find(const T& element);
    T operator [] (const size_t& index) { assert(_buffer != NULL && index < _size); return _buffer[index]; }
  protected:
    void grow();
    size_t _size;
    size_t _capacity;
    T* _buffer;
};

template<class T>
void Array<T>::grow() {
  size_t new_capacity = std::max(GROW_FACTOR * _capacity, BASE_CAPACITY); 
  T* new_buffer = new T[new_capacity]; 
  if (_buffer != NULL) {
    for (size_t i = 0; i < _capacity; ++i) {
      new_buffer[i] = _buffer[i];
    }
  }
  _buffer = new_buffer;
  _capacity = new_capacity;
}

template<class T>
void Array<T>::add(const T& new_element) {
  if ( _size == _capacity ) {
    grow();
  }
  _buffer[_size++] = new_element;
}

template<class T>
T Array<T>::max() {
  assert(_buffer != NULL);
  T max = _buffer[0];
  for (size_t i = 1; i < _size; ++i) {
    if ( max < _buffer[i] ) {
      max = _buffer[i];
    }
  }
  return max;
}

template<class T>
size_t Array<T>::find(const T& element) {
  for (size_t i = 0; i < _capacity; ++i) {
    if ( _buffer[i] == element ) {
      return i;
    }
  }
  return _capacity;
}

void read_int_array(const size_t& length, Array<ssize_t>& target) {
  for (size_t i = 0; i < length; ++i) {
    ssize_t to_add;
    scanf("%d", &to_add);
    target.add(to_add);
  }
}

int main() {
  size_t length;
  scanf("%d", &length);
  Array<ssize_t> first;
  Array<ssize_t> second;
  read_int_array(length, first);
  read_int_array(length, second);
  ssize_t second_max = second.max();
  size_t second_max_id = second.find(second_max);
  ssize_t sum = second_max + first[0];
  size_t first_id = 0;
  for (size_t i = 1; i <= second_max_id && i < first.size(); ++i) {
    ssize_t new_sum = first[i] + second_max;
    if (sum < new_sum) {
      sum = new_sum;
      first_id = i;
    }
  }
  printf("%d %d\n", first_id, second_max_id);
  return 0;
}

