#include <iostream>
#include <string.h>

using namespace std;

enum DIMENSITY_IDS { X_INDEX, Y_INDEX, Z_INDEX, DIMENSITY };

//структура для описания ящика
struct Crate {
  size_t _tag; // бирка с порядковым номером
  ssize_t _x_size; // -|
  ssize_t _y_size; //   > габариты ящика по трем осям
  ssize_t _z_size; // -|
  Crate(): _tag(), _x_size(0), _y_size(0), _z_size(0) {}
  friend bool operator > (const Crate& lhs, const Crate& rhs);
};

// сравнивать ящики будем по третьему габариту (почему - см.ниже)
bool operator > (const Crate& lhs, const Crate& rhs) {
  return lhs._z_size > rhs._z_size;
}

//шаблонная функция для двоичного поиска
template<class T>
size_t BinarySearch (T* array, int end, T to_find) {
  size_t left = 0, right = end;
  while(left < right) {
    size_t middle = (left + right) / 2;
    if(to_find > array[middle]) {
      left = middle + 1;
    } else {
      right = middle;
    }
  }
  return right;
}

//шаблонная функция для сортировки вставками (из материалов лекции)
template<class T>
void InsertionSort(T *array, int left, int right) {
  for (size_t i = left + 1; i < right; ++i) {
    size_t new_position = BinarySearch(array, i, array[i]);
    if( new_position < i ) {
      T tmp = array[i];
      memmove( &array[new_position + 1], &array[new_position], (i - new_position) * sizeof(T));
      array[new_position] = tmp;
    }
  }
}

// функция считывания массива ящиков
void read_crates(Crate*& array, const size_t& count) {
  ssize_t* dimensions = new ssize_t[DIMENSITY]; // буфер для чтения габаритов
  size_t box_index = 0; // инициализируем первый порядковый номер ящика
  while(box_index < count) {
    for(size_t i = 0; i < DIMENSITY; ++i) {
      cin >> dimensions[i];  // читаем габариты
    }
    InsertionSort(dimensions, X_INDEX, DIMENSITY); // "поворачиваем" ящик так, чтобы размер по Х был самым маленьким, а по Z - самым большим
    // помещаем ящик в массив
	array[box_index]._x_size = dimensions[X_INDEX];
    array[box_index]._y_size = dimensions[Y_INDEX];
    array[box_index]._z_size = dimensions[Z_INDEX];
    array[box_index]._tag = box_index; // пишем номер ящика в бирку
    ++box_index;
  }
  delete[] dimensions;
}

// функция печати бирок ящиков (выходные данные по условию задачи)
void print_crate_tags(Crate* array, const size_t& count) {
  for(size_t i = 0; i < count ; ++i) {
    cout << array[i]._tag << " ";
  }
}

// функция для определения порядка вложенности ящиков
void inclosures_order(Crate* array, const size_t& count) {
  InsertionSort(array, 0, count); // т.к. размеры всех ящиков отсортированы при считывании, сортировка по максимальному размеру даст порядок вложенности
  print_crate_tags(array, count); // печатаем бирки в полученном порядке
}

int main() {
  size_t boxes_count = 0;
  cin >> boxes_count;
  Crate* boxes = new Crate[boxes_count];
  read_crates(boxes, boxes_count);
  inclosures_order(boxes, boxes_count);
  delete[] boxes;
  return 0;
}