#include <stdio.h>

const int I = 9;
const int J = 18;

void check_for_figure(char arr[I][J], char current_ch, char next_ch,
                      char current_n, char next_n);
void pawn_move(char arr[I][J], int current_ch, char next_ch, int current_n,
               char next_n);

int main() {
  FILE *file;
  FILE *notes;
  char arr_b[I][J];

  int i, j;

  int choice = 3; //костыль для количества ходов

  char current_char, next_char, current_num, next_num;

  file = fopen("board.txt", "r");
  notes = fopen("notes.txt", "w+");

  for (i = 0; i < I; i++) {
    for (j = 0; j < J; j++) {
      arr_b[i][j] = getc(file);
      putchar(arr_b[i][j]);
    }
  }
  while (choice != 0) {
    printf("\n\nMake your move:\n");
    scanf("\n%c%c - %c%c", &current_char, &current_num, &next_char, &next_num);

    printf("\nYour move is: %c%c - %c%c\n\n", current_char, current_num,
           next_char, next_num);

    check_for_figure(arr_b, current_char, next_char, current_num, next_num);

    for (i = 0; i < I; i++) {
      for (j = 0; j < J; j++) {
        putchar(arr_b[i][j]);
        fputc(arr_b[i][j], notes);

      }
    }
    fputs("\n\n", notes);
    choice--;
  }

  fclose(file);
  return 0;
}

void pawn_move(char arr[I][J], int current_ch, char next_ch, int current_n,
               char next_n) {
  int i, j;
  int check_next_ch, check_next_n;
  for (i = 0; i < I; i++) {
    for (j = 0; j < J; j++) {
      if (arr[i][j] == next_n) {
        check_next_n = i;
      }
      if (arr[i][j] == next_ch) {
        check_next_ch = j;
      }
    }
  }
  arr[current_n][current_ch] = ' ';
  arr[check_next_n][check_next_ch] = 'P';
}

void check_for_figure(char arr[I][J], char current_ch, char next_ch,
                      char current_n, char next_n) {
  int i, j;
  int check_current_ch, check_current_n;
  for (i = 0; i < I; i++) {
    for (j = 0; j < J; j++) {
      if (arr[i][j] == current_n) {
        check_current_n = i;
      }
      if (arr[i][j] == current_ch) {
        check_current_ch = j;
      }
    }
  }
  if (arr[check_current_n][check_current_ch] == 'P')
    pawn_move(arr, check_current_ch, next_ch, check_current_n, next_n);
}
