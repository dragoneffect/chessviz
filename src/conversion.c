#include "conversion.h"
int F_current_char(char arr[I][J], char current_ch) {
  //для вычисления столбца, в котором содержится буква текущей позиции
  int i, j;
  for (i = 8; i < I; i++) {
    for (j = 0; j < J; j++) {
      if (arr[i][j] == current_ch) {
        return j;
      }
    }
  }
  return 0;
}

int F_current_number(char arr[I][J], char current_n) {
  //для вычисления строки, где находится цифра текущей позиции
  int i, j;
  for (i = 0; i < I; i++) {
    for (j = 0; j < 1; j++) {
      if (arr[i][j] == current_n) {
        return i;
      }
    }
  }
  return 0;
}

int F_next_char(char arr[I][J], char next_ch) {
  //для вычисления столбца, в котором содержится буква следующего хода
  int i, j;
  for (i = 8; i < I; i++) {
    for (j = 0; j < J; j++) {
      if (arr[i][j] == next_ch) {
        return j;
      }
    }
  }
  return 0;
}

int F_next_number(char arr[I][J], char next_n) {
  //для вычисления строки, в котором находится цифра следующего хода
  int i, j;
  for (i = 0; i < I; i++) {
    for (j = 0; j < 1; j++) {
      if (arr[i][j] == next_n) {
        return i;
      }
    }
  }
  return 0;
}
