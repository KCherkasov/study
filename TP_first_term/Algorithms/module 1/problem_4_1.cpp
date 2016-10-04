#include <cstdio>
#include <cassert>
#include <algorithm>

const size_t DEFAULT_CAPACITY = 4;
const size_t GROW_FACTOR = 2;

const size_t DEQUEUE_KEY = 2;
const size_t ENQUEUE_KEY = 3;

const ssize_t EMPTY_DEQUEUE = -1;

class Queue {
  public:
    Queue(const size_t& capacity = DEFAULT_CAPACITY);
    ~Queue() { delete[] _buffer; }
    size_t capacity() { return _capacity; } 
    bool empty() { return _head == _tail || _buffer == NULL; }
    bool full() { return _head == (_tail + 1) % _capacity; }
    void enqueue(const ssize_t& value);
    ssize_t dequeue();
  protected:
    void grow();
    size_t _capacity;
    size_t _head;
    size_t _tail;
    ssize_t* _buffer;
};

Queue::Queue(const size_t& capacity): _capacity(capacity), _head(0), _tail(0) {
  if (capacity != 0) {
    _buffer = new ssize_t[_capacity];
  } else {
    _buffer = NULL;
  }
}

void Queue::grow() {
  size_t new_capacity = std::max(_capacity * GROW_FACTOR, DEFAULT_CAPACITY);
  size_t new_tail = 0;
  ssize_t* new_buffer = new ssize_t[new_capacity];
  if (_head <= _tail) {
    for (size_t i = 0; i < _tail; ++i) {
      new_buffer[i] = _buffer[i];
      ++new_tail;
    }
  } else {
    for (size_t i = _head; i < _capacity; ++i) {
      new_buffer[new_tail++] = _buffer[i];
    }
    for (size_t i = 0; i < _tail; ++i) {
      new_buffer[new_tail++] = _buffer[i];
    }
  }
  _capacity = new_capacity;
  _head = 0;
  _tail = new_tail;
  delete[] _buffer;
  _buffer = new_buffer;
}

void Queue::enqueue(const ssize_t& value) {
  if ((_tail + 1) % _capacity == _head) {
    grow();
  }
  _buffer[_tail++] = value;
  _tail %= _capacity;
}

ssize_t Queue::dequeue() {
  if (_head == _tail) {
    return EMPTY_DEQUEUE;
  }
  ssize_t result = _buffer[_head++];
  _head %= _capacity;
  return result;
}

void read_key_value(size_t& key, ssize_t& value) {
  scanf("%d", &key);
  scanf("%d", &value);
}

bool interpret_input(const size_t& key, const ssize_t& value, Queue& queue) {
  bool outcome = true;
  switch(key) {
    case DEQUEUE_KEY: {
      outcome &= (queue.dequeue() == value);
      break;
    }
    case ENQUEUE_KEY: {
      queue.enqueue(value);
      break;
    }
    default: {
      outcome = false;
      break;
    }
  }
  return outcome;
}

int main() {
  ssize_t commands_number;
  size_t key;
  ssize_t value;
  scanf("%d", &commands_number);
  Queue queue(commands_number / 2);
  bool all = true;
  for (size_t i = 0; i < commands_number; ++i) {
    read_key_value(key, value);
    if (!interpret_input(key, value, queue)) {
      printf("NO");
      return 0;
    }
  }
  printf("YES");
  return 0;
}
