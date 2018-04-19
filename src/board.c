#include "board.h"

int read(int value, const char *input) {
  //функция для правильного чтения ввода
  size_t length = 0;
  char *end = NULL;
  char buf[BUFFER_SIZE] = "";
  //проверка параметров
  assert(value);
  assert(input);
  //приглашение на выводим
  printf("%s ", input);
  fflush(stdout);
  //чтение в буфер
  if (!fgets(buf, sizeof(buf), stdin)) {
    return 0;
  }
  //удаление символа перевода строки
  length = strlen(buf);
  if (buf[length - 1] == '\n') {
    buf[--length] = '\0';
    //перевод из строки в число
    errno = 0;
    value = strtod(buf, &end);
    //обработка ошибок
    if (length == 0) {
      fprintf(stderr, "Error: empty input\n");
      return 0;
    }
    if (errno != 0 || *end != '\0') {
      fprintf(stderr, "Error: incorrect value\n");
      fprintf(stderr, "\t%s\n", buf);
      fprintf(stderr, "\t%*c\n", (int)(end - buf) + 1, '^');
      return 0;
    }
  } else {
    //строка прочитана не полностью, пропуск остатка строки
    scanf("%*[^\n]");
    scanf("%*c");
    fprintf(stderr, "Error: do not enter more than %d characters\n",
            BUFFER_SIZE - 2);
    return 0;
  }
  return value;
}

int make_a_move(int param, char arr[I][J], int color, FILE *notes_file) {
  //функция, которая осуществляет ввод значения хода
  //флаги
  int choice = -1;
  int choice2 = -1;
  /*cur_ch - переменная, в которой хранится буква, содержащаяся в текущей
  позиции фигуры (e из e2)
  next_ch - переменная, в которой хранится буква следующего предполагаемого хода
  (h из h5)
  cur_n - переменная, в которой хранится цифра текущей позиции фигуры, которой
  планируется осуществить ход (6 из c6)
  next_n - переменная, в которой хранится цифра предполагаемого хода (3 из f3)
  */
  char cur_ch, next_ch, cur_n, next_n;
  printf("\n\nMake your move:\n");
  scanf("\n%c%c - %c%c", &cur_ch, &cur_n, &next_ch, &next_n);
  printf("\nYour move is: %c%c - %c%c\n\n", cur_ch, cur_n, next_ch, next_n);
  do {
    choice = check_for_right_move(cur_ch, cur_n, next_ch, next_n);
    choice2 = check_for_figure(arr, cur_ch, cur_n, next_ch, next_n, color);
    if (!choice || !choice2) {
      printf("Wrong move. Try again:\n");
      scanf("\n%c%c - %c%c", &cur_ch, &cur_n, &next_ch, &next_n);
    }
  } while (!choice || !choice2);
  param--;
  return param;
}

int check_for_right_move(char first_char, char first_num, char last_char,
                         char last_num) {
  //проверка хода
  if (check_for_right_char(first_char)) {
    if (check_for_right_num(first_num)) {
      if (check_for_right_char(last_char)) {
        if (check_for_right_num(last_num)) {
          return 1;
        }
      }
    }
  }
  return 0;
}

int check_for_right_char(char ch) {
  const char *Letters = "abcdefgh";
  int i;
  for (i = 0; i < 8; i++) {
    if (ch == Letters[i]) {
      return 1;
    }
  }
  return 0;
}

int check_for_right_num(char ch) {
  const char *Figures = "12345678";
  int i;
  for (i = 0; i < 8; i++) {
    if (ch == Figures[i]) {
      return 1;
    }
  }
  return 0;
}

int check_for_figure(char arr[I][J], char current_ch, char current_n,
                     char next_ch, char next_n, int color) {
  //переменные для вычисления позиции фигуры в массиве
  int check_current_ch, check_current_n;
  //находим положение фигуры в массиве
  check_current_ch = F_current_char(arr, current_ch);
  check_current_n = F_current_number(arr, current_n);
  //если это белая фигура
  if (color == 1) {
    //если это пешка
    if (arr[check_current_n][check_current_ch] == 'P') {
      if (pawn_move(arr, check_current_ch, check_current_n, next_ch, next_n)) {
        return 1;
      } else {
        return 0;
      }
    } else {
      return 0;
    }
  }
  //если это черная фигура
  else if (color == 0) {
    //если это пешка
    if (arr[check_current_n][check_current_ch] == 'p') {
      //проверка на очередность хода
      if (pawn_move(arr, check_current_ch, check_current_n, next_ch, next_n)) {
        return 1;
      } else {
        return 0;
      }
    } else {
      return 0;
    }
  }
  return 0;
}

int turn(int white_or_black) {
  //переключает очередность хода
  if (white_or_black == 1) {
    white_or_black--;
    return white_or_black;
  } else {
    white_or_black++;
    return white_or_black;
  }
}

int pawn_move(char arr[I][J], int current_ch, int current_n, char next_ch,
              char next_n) {
  int check_next_ch, check_next_n;
  check_next_n = F_next_number(arr, next_n);
  check_next_ch = F_next_char(arr, next_ch);
  //если движение осуществляется снизу вверх (белые)
  if (current_n - check_next_n > 0) {
    /*если разница в две клетки, то проверяем, первый ли это ход, и если да, то
    делаем ход */
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
    /*если разница в одну клетку, то делаем проверку, белые ли это и если да, то
    делаем ход */
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
    /*если разница в две клетки, и если ход первый, а также если это
    действительно черные, то делаем ход */
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
