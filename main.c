#include <stdio.h>

const int I = 9;  //количество строк
const int J = 18; //количество столбцов

//для вычисления столбца, в котором содержится буква текущей позиции
int F_current_char(char arr[I][J], char current_ch);
//для вычисления строки, где находится цифра текущей позиции
int F_current_number(char arr[I][J], char current_n);
//для вычисления столбца, в котором содержится буква следующего хода
int F_next_char(char arr[I][J], char next_ch);
//для вычисления строки, в котором находится цифра следующего хода
int F_next_number(char arr[I][J], char next_n);
int check_for_figure(char arr[I][J], char current_ch, char current_n,
                     char next_ch, char next_n);
int pawn_move(char arr[I][J], int current_ch, int current_n, char next_ch,
              char next_n);
int check_for_right_char(char ch);
int check_for_right_num(char ch);
//проверка хода
int check_for_right_move(char first_char, char first_num, char last_char,
                         char last_num);
int is_it_first_move(char arr[I][J], int current_ch, int current_n);

int main() {
  FILE *file; //файл с изначальным состоянием доски
  FILE *notes; //файл, куда записываются ходы
  char arr_b[I][J]; //массив, содержащий в себе элементы доски

  int i, j;

  int choice = -1;
  /*cur_ch - переменная, в которой хранится буква, содержащаяся в текущей
  позиции фигуры (e из e2)
  next_ch - переменная, в которой хранится буква следующего предполагаемого хода
  (h из h5)
  cur_n - переменная, в которой хранится цифра текущей позиции фигуры, которой
  планируется осуществить ход (6 из c6)
  next_n - переменная, в которой хранится цифра предполагаемого хода (3 из f3)
  */
  char cur_ch, next_ch, cur_n, next_n;

  file = fopen("board.txt", "r");
  notes = fopen("notes.txt", "w+");
  //посимвольно считываем данные доски из текстового файла в двумерный массив
  for (i = 0; i < I; i++) {
    for (j = 0; j < J; j++) {
      arr_b[i][j] = getc(file);
      putchar(arr_b[i][j]);
    }
  }

  printf("\nHow many moves do you want to make?\n");
  scanf("\n%d", &choice);

  while (choice != 0) {

    printf("\n\nMake your move:\n");
    scanf("\n%c%c - %c%c", &cur_ch, &cur_n, &next_ch, &next_n);

    printf("\nYour move is: %c%c - %c%c\n\n", cur_ch, cur_n, next_ch, next_n);

    check_for_figure(arr_b, cur_ch, cur_n, next_ch, next_n);
    //записываем позицию доски в файл и выводим ее на экран
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

int is_it_first_move(char arr[I][J], int current_ch, int current_n) {
  //если это белая пешка, то проверка осуществлена успешно
  if (current_n == 6) {
    if (arr[current_n][current_ch] == 'P') {
      return 1;
    } else {
      return 0;
    }
  }
  //если это черная пешка, то проверка успешна
  else if (current_n == 1) {
    if (arr[current_n][current_ch] == 'p') {
      return 1;
    } else {
      return 0;
    }
  } else {
    return 0;
  }
  return 0;
}

int pawn_move(char arr[I][J], int current_ch, int current_n, char next_ch,
              char next_n) {
  int check_next_ch, check_next_n;
  check_next_n = F_next_number(arr, next_n);
  check_next_ch = F_next_char(arr, next_ch);
  //если движение осуществляется снизу вверх (белые)
  if (current_n - check_next_n > 0) {
    //если разница в две клетки, то проверяем, первый ли это ход, и если да, то
    //делаем ход
    if (current_n - check_next_n == 2) {
      if (is_it_first_move(arr, current_ch, current_n)) {
        if (arr[current_n][current_ch] == 'P') {
          arr[current_n][current_ch] = ' ';
          arr[check_next_n][check_next_ch] = 'P';
          return 1;
        } else {
          return 0;
        }
      } else {
        return 0;
      }
    }
    //если разница в одну клетку, то делаем проверку, белые ли это и если да, то
    //делаем ход
    else if (current_n - check_next_n == 1) {
      if (arr[current_n][current_ch] == 'P') {
        arr[current_n][current_ch] = ' ';
        arr[check_next_n][check_next_ch] = 'P';
        return 1;
      } else {
        return 0;
      }
    }
  }
  //реализация движения для черных (если ход осуществляется сверху вниз)
  else if (current_n - check_next_n < 0) {
    //если разница в две клетки, и если ход первый, а также если это
    //действительно черные, то делаем ход
    if (check_next_n - current_n == 2) {
      if (is_it_first_move(arr, current_ch, current_n)) {
        if (arr[current_n][current_ch] == 'p') {
          arr[current_n][current_ch] = ' ';
          arr[check_next_n][check_next_ch] = 'p';
          return 1;
        } else {
          return 0;
        }
      } else {
        return 0;
      }
    } else if (check_next_n - current_n == 1) {
      if (arr[current_n][current_ch] == 'p') {
        arr[current_n][current_ch] = ' ';
        arr[check_next_n][check_next_ch] = 'p';
        return 1;
      } else {
        return 0;
      }
    }
  }
  return 0;
}

int check_for_figure(char arr[I][J], char current_ch, char current_n,
                     char next_ch, char next_n) {
  //переменные для вычисления позиции фигуры в массиве
  int check_current_ch, check_current_n;
  //находим положение фигуры в массиве
  check_current_ch = F_current_char(arr, current_ch);
  check_current_n = F_current_number(arr, current_n);
  //если фигура - пешка, то дальнейшие события будет обрабатывать функция
  //хода пешки
  if (arr[check_current_n][check_current_ch] == 'P') {
    if (pawn_move(arr, check_current_ch, check_current_n, next_ch, next_n))
      return 1;
    else {
      printf("\nWrong move. Try again\n");
      return 0;
    }
  } else if (arr[check_current_n][check_current_ch] == 'p') {
    if (pawn_move(arr, check_current_ch, check_current_n, next_ch, next_n))
      return 1;
    else {
      printf("\nWrong move. Try again\n");
      return 0;
    }
  }
  return 0;
}

int F_current_char(char arr[I][J], char current_ch) {
  int i, j;
  for (i = 0; i < I; i++) {
    for (j = 0; j < J; j++) {
      if (arr[i][j] == current_ch)
        return j;
    }
  }
  return 0;
}

int F_current_number(char arr[I][J], char current_n) {
  int i, j;
  for (i = 0; i < I; i++) {
    for (j = 0; j < J; j++) {
      if (arr[i][j] == current_n)
        return i;
    }
  }
  return 0;
}

int F_next_char(char arr[I][J], char next_ch) {
  int i, j;
  for (i = 0; i < I; i++) {
    for (j = 0; j < J; j++) {
      if (arr[i][j] == next_ch)
        return j;
    }
  }
  return 0;
}

int F_next_number(char arr[I][J], char next_n) {
  int i, j;
  for (i = 0; i < I; i++) {
    for (j = 0; j < J; j++) {
      if (arr[i][j] == next_n)
        return i;
    }
  }
  return 0;
}

int check_for_right_char(char ch) {
  const char *Letters = "abcdefgh";
  int i;
  for (i = 0; i < 8; i++) {
    if (ch == Letters[i])
      return 1;
  }
  return 0;
}

int check_for_right_num(char ch) {
  const char *Figures = "12345678";
  int i;
  for (i = 0; i < 8; i++) {
    if (ch == Figures[i])
      return 1;
  }
  return 0;
}

int check_for_right_move(char first_char, char first_num, char last_char,
                         char last_num) {
  if (check_for_right_char(first_char))
    if (check_for_right_num(first_num))
      if (check_for_right_char(last_char))
        if (check_for_right_num(last_num))
          return 1;
  return 0;
}
