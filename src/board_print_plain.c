#include "board_print_plain.h"

void print_initial_board(char arr[I][J], FILE *board_file) {
  //печать изначального состояния доски
  int i, j;
  /*посимвольно считываем данные доски из текстового файла в двумерный
  массив и выводим доску на экран */
  for (i = 0; i < I; i++) {
    for (j = 0; j < J; j++) {
      arr[i][j] = getc(board_file);
      putchar(arr[i][j]);
    }
  }
}

void print_board(char arr[I][J], FILE *notes_file) {
  //печать доски и запись в файл с ходами
  int i, j;
  for (i = 0; i < I; i++) {
    for (j = 0; j < J; j++) {
      putchar(arr[i][j]);
      fputc(arr[i][j], notes_file);
    }
  }
  fputs("\n\n", notes_file);
}
