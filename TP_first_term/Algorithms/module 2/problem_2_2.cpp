#include <iostream>
#include <algorithm>
#include <vector>

const size_t DEFAULT_CAPACITY = 4;

template <class T>
class Heap {
  public:
    Heap() {}
	~Heap() {}
	size_t size() const { return _buffer.size(); }
	size_t capacity() const { return _buffer.capacity(); }
	void clear() { _buffer.clear(); }
	bool empty() const { return _buffer.empty(); }
    void push_back(const T& value) { _buffer.push_back(value); }
	void make_heap();
	void sort();
	T operator [] (const size_t& index) const { return _buffer[index]; }
  private:
    void heapify(const size_t& last, const size_t& index);
    std::vector<T> _buffer;
};

template<class T>
void Heap<T>::heapify(const size_t& last, const size_t& index) {
  size_t left = 2 * index + 1;
  size_t right = 2 * index + 2;
  size_t largest = index;
  if (left < last && _buffer[left] > _buffer[index]) {
    largest = left;
  }
  if (right < last && _buffer[right] > _buffer[largest]) {
    largest = right;
  }
  if (largest != index) {
    T tmp = _buffer[index];
	_buffer[index] = _buffer[largest];
	_buffer[largest] = tmp;
	heapify(last, largest);
  }
}

template<class T>
void Heap<T>::make_heap() {
  for (size_t i = _buffer.size() / 2; i > 0; --i) {
    heapify(_buffer.size(), i - 1);
  }
}

template<class T>
void Heap<T>::sort() {
  size_t current_last = _buffer.size();
  for (size_t i = 0; i < _buffer.size(); ++i) {
    T tmp = _buffer[0];
	_buffer[0] = _buffer[current_last - 1];
	_buffer[current_last - 1] = tmp;
	heapify(--current_last, 0);
  }
}

template<class T>
size_t count_time(const Heap<T>& data) {
  size_t operation_time = data[0];
  size_t total_time = 0;
  for (size_t i = 1; i <= data.size() / 2; ++i) {
    operation_time += data[i];
	total_time += operation_time;
  }
  size_t halfsum_time = operation_time;
  operation_time = data[data.size() - 1];
  for (size_t i = data.size() - 2; i >= data.size() / 2 + 1; --i) {
    operation_time += data[i];
	total_time += operation_time;
  }
  total_time += halfsum_time + operation_time;
  return total_time;
}

int main() {
  size_t elements;
  std::cin >> elements;
  Heap<ssize_t> heap;
  for (size_t i = 0; i < elements; ++i) {
    ssize_t value;
	std::cin >> value;
    heap.push_back(value);
  }
  heap.make_heap();
  heap.sort();
  std::cout << count_time<ssize_t>(heap);
  return 0;
}