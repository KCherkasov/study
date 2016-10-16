#include <iostream>
#include <algorithm>
#include <string>

const size_t DEFAULT_CAPACITY = 4;
const ssize_t EMPTY_STACK_TOP = -1;
const size_t GROW_FACTOR = 2;

// стек на динамическом буфере
template <class T>
class Stack {
  public:
    Stack(const size_t& capacity = DEFAULT_CAPACITY): _top(EMPTY_STACK_TOP), _capacity(capacity), _buffer(NULL) { if (_capacity > 0) _buffer = new T[_capacity]; }
    ~Stack() { delete[] _buffer; }
    void push(const T&); 
    T pop(); // выводит верхний элемент со смещением _top на 1 влево
    T top(); // выводит верхний элемент без смещения _top
    // функции ниже реализованы для уподобления std::stack
    bool empty() const { return _top == EMPTY_STACK_TOP; } // проверка на пустоту
    size_t capacity() const { return _capacity; }; // возвращает число элементов, под которые выделена память в буфере
    void clear(bool free_memory = true); // чистка содержимого (в зависимости от флага работает с освобождением памяти буфера или без)
  private:
    void grow(); // расширение буфера
    ssize_t _top;
    size_t _capacity;
    T* _buffer;
};

template<class T>
void Stack<T>::grow() {
  size_t new_capacity = std::max(_capacity * GROW_FACTOR, DEFAULT_CAPACITY);
  T* new_buffer = new T[new_capacity];
  size_t j = 0;
  if (_buffer != NULL) {
    for (ssize_t i = _top; i < _capacity; ++i) {
      new_buffer[j++] = _buffer[i];
    }
    _top = 0;
  } else {
    _top = EMPTY_STACK_TOP;
  }
  _capacity = new_capacity;
  delete[] _buffer;
  _buffer = new_buffer;
}

template<class T>
void Stack<T>::push(const T& value) {
  if (_top == _capacity - 1 || _buffer == NULL) {
    grow();
  }
  _buffer[++_top] = value;
}

template<class T>
T Stack<T>::pop() {
  if (_top > -1) {
    return _buffer[_top--];
  } else {
    return 0;
  }
}

template<class T>
T Stack<T>::top() {
  if (_top > -1) {
    return _buffer[_top];
  } else {
    return 0;
  }
}

template<class T>
void Stack<T>::clear(bool free_memory) {
  _top = -1;
  if (free_memory) {
    delete[] _buffer;
  }
}

// функция проверки возможности построения из строки source стековой анаграммы, соответствующей строке demand
void check_anagram(const std::string& source, const std::string& demand) {
  Stack<char> stack;
  std::string anagram; // строка для стековой анаграммы
  size_t i = 0;
  size_t j = 0;
  // идем по строке-исходнику
  while (i < source.size()) {
    stack.push(source[i++]); // кладем i-ый символ исходника в стек
    // если верхний символ стека совпадает с текущим символом строки-результата,
    // перемещаем этот символ из стека в строку-анаграмму, пока стек не опустеет
    // либо не встретится первое различие
    while (stack.top() == demand[j] && !stack.empty()) {
      anagram.push_back(stack.pop());
      ++j;
    }
  }
  // если в стеке остались символы, переносим их в строку-анаграмму
  while (!stack.empty()) {
    anagram.push_back(stack.pop());
  }
  // если строка-анаграмма совпадает со строкой-результатом, выводим YES, иначе - NO
  if (anagram == demand) {
    std::cout << "YES";
  } else {
    std::cout << "NO";
  }
}

//функция считывания входных данных
void read_input(std::string& source, std::string& demand) {
  std::cin >> source;
  std::cin >> demand;
}

int main() {
  std::string source, demand;
  read_input(source, demand);
  check_anagram(source, demand);
  return 0;
}