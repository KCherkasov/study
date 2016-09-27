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
    void clear() { delete[] _buffer; _capacity = _size = 0; }
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

void print_int_array(Array<ssize_t>& to_print) {
  if (!to_print.empty()) {
    for (size_t i = 0; i < to_print.size(); ++i) {
      if (i != to_print.size() - 1) {
        printf("%d ", to_print[i]);
      } else {
        printf("%d\n", to_print[i]);
      }
    }
  }
}

template<class T>
size_t binary_search(Array<T>& array, const T& element, size_t from, size_t to) {
  while (from < to) {
    size_t middle = (from + to) / 2;
    if (element <= array[middle]) {
      to = middle;
    } else {
      from = middle + 1;
    }
  }
  if (from == array.size() || array[from] != element) {
    return array.capacity();
  } else {
    return from;
  }
}

template<class T>
size_t gallop_search(Array<T>& array, const T& element) {
  size_t boundary = 1;
  while (boundary < array.size() && element >= array[boundary]) {
    boundary *= 2;	
  }
  return (binary_search(array, element, boundary / 2, std::min(boundary, array.size())));
}

template<class T>
void get_intersection(Array<T>& data, Array<T>& pattern, Array<T>& intersection) {
  if (!data.empty() && !pattern.empty()) {
  	size_t prev_id = data.capacity();
    for (size_t i = 0; i < pattern.size() && i < data.size(); ++i) {
      size_t buffer = prev_id;
      if (prev_id != data.capacity()) {
      	buffer = binary_search(data, pattern[i], prev_id, data.size());
      } else {
      	buffer = gallop_search(data, pattern[i]);
      }
      if (buffer != data.capacity()) {
      	prev_id = buffer;
      	intersection.add(pattern[i]);
      }
    }
  }
}

int main() {
  Array<ssize_t> data;
  Array<ssize_t> pattern;
  Array<ssize_t> intersection;
  size_t data_size;
  size_t pattern_size;
  scanf("%d", &data_size);
  scanf("%d", &pattern_size);
  read_int_array(data_size, data);
  read_int_array(pattern_size, pattern);
  get_intersection(data, pattern, intersection);
  print_int_array(intersection);
  return 0;
}

