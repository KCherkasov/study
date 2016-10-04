#include <cstdio>
#include <cassert>
#include <algorithm>

const size_t DEFAULT_CAPACITY = 4;
const size_t GROW_FACTOR = 2;

template<class T>
class Array {
  public:
    Array(const size_t& capacity = DEFAULT_CAPACITY): _capacity(capacity), _size(0), _buffer(NULL) { if (_capacity > 0) _buffer = new T[_capacity]; }
    ~Array() { delete[] _buffer; }
    size_t capacity() { return _capacity; }
    size_t size() { return _size; }
    bool empty() { return _size == 0; }
    void clear(const bool& free_memory = true) { _size = 0; if (free_memory) { _capacity = 0; delete[] _buffer; } }
    void push_back(const T& value);

    T operator [] (const size_t& index) { assert(_buffer != NULL || index < _size); return _buffer[index]; }

  protected:
    void grow();
    size_t _capacity;
    size_t _size;
    T* _buffer;
};

template<class T>
void Array<T>::grow() {
  size_t new_capacity = std::max(_capacity * GROW_FACTOR, DEFAULT_CAPACITY);
  T* new_buffer = new T[new_capacity];
  for (size_t i = 0; i < _capacity; ++i) {
    new_buffer[i] = _buffer[i];
  }
  _capacity = new_capacity;
  delete[] _buffer;
  _buffer = new_buffer;
}

template<class T>
void Array<T>::push_back(const T& value) {
  if (_size == _capacity) {
    grow();
  }
  _buffer[_size++] = value;
}

void read_int_array(const size_t& size, Array<ssize_t>& array) {
  for (size_t i = 0; i < size; ++i) {
    ssize_t buffer;
    scanf("%d", &buffer);
    array.push_back(buffer);
  }
}

void find_max_sum_indices(Array<ssize_t>& a_array, Array<ssize_t>& b_array) {
  size_t a_max_index = 0;
  size_t b_max_index = 0;
  size_t current_a_max_index = a_max_index;
  for (size_t i = 1; i < b_array.size(); ++i) {
    if (a_array[i] > a_array[current_a_max_index]) {
      current_a_max_index = i;
    }
    if ((a_array[current_a_max_index] + b_array[i]) > (a_array[a_max_index] + b_array[b_max_index])) {
      a_max_index = current_a_max_index;
      b_max_index = i;
    }
  }  
  printf("%d %d", a_max_index, b_max_index);
}

int main() {
  size_t arrays_size;
  scanf("%d", &arrays_size);
  Array<ssize_t> first;
  Array<ssize_t> second;
  read_int_array(arrays_size, first);
  read_int_array(arrays_size, second);
  find_max_sum_indices(first, second);
  return 0;
}

