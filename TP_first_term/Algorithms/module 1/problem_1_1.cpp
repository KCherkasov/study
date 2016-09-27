#include <cstdio>

size_t count_zeroes (size_t digit) {
  size_t zeroes = 0;
  while (digit != 0) {
    digit /= 5;
    zeroes += digit;
  }
  return zeroes;
}

int main() {
  size_t number;
  scanf("%d", &number);
  size_t zeroes = count_zeroes(number);
  printf("%d\n", zeroes);
  return 0;
}

