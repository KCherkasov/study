#include <iostream>

void count_build_ways(const size_t& blocks_count) {
  // выделяем память под матрицу
  size_t **build_ways = new size_t*[blocks_count * 2 + 1];
  for (size_t i = 0; i < blocks_count * 2 + 1; ++i) {
    build_ways[i] = new size_t[blocks_count * 2 + 1];
  }
  // заполняем матрицу:
  // число вариантов заполнения - функция от двух аргументов: ширины верхнего этажа (числа блоков на последнем этаже пирамиды)
  // и количества оставшихся блоков. В сумме эти два параметра дадут общее число блоков в наличии
  // матрица устроена следующим образом: номер строки - число блоков в наличии, номер столбца - ширина верхнего этажа
  // на главной диагонали - число способов построения пирамиды из N блоков
  for (size_t diag = 0; diag < blocks_count * 2 + 1; ++diag) {
    for (size_t previous = 1; previous <= diag + 1; ++previous) {
      size_t remaining = diag - previous + 1;
      if (remaining == 0) {
        build_ways[remaining][previous] = 1; // если блоков не осталось, то существует единственный способ построения такой пирамиды
        // это описывает вариант построения одноэтажной пирамиды, либо ее последнего этажа (все оставшиеся блоки выложены в линию)
      } else {
      	//если остались еще блоки, считаем, сколькими способами можно сложить из них пирамиду
        build_ways[remaining][previous] = 0;
        //уменьшаем число свободных блоков на 1 за итерацию и считаем новым суммарным числом блоков
        for (int next = 1; next <= remaining; ++next) {
          size_t new_remaining = remaining - next;
          if (next < previous) {
            build_ways[remaining][previous] += build_ways[new_remaining][next]; //число вариантов построения большой пирамиды равно сумме вариантов построения пирамид меньших конфигураций
          }
        }
      }
    }
  }
  std::cout << (build_ways[blocks_count][blocks_count] + 1); // +1 т.к. для искомой конфигурации не учтен вариант "выложить все блоки в одну линию"
  delete[] build_ways;
}

int main() {
  int blocks;
  std::cin >> blocks;
  count_build_ways(blocks);
  return 0;
}
