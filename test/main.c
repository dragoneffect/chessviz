#define CTEST_MAIN

#include "../src/board.h"
#include "../src/board_print_plain.h"
#include "../src/const.h"
#include "../src/conversion.h"
#include "../thirdparty/ctest.h"

CTEST(right_num, Correct) {
  int result = check_for_right_num('2');
  int expected = 1;
  ASSERT_EQUAL(expected, result);
}

CTEST(right_num, Incorrect) {
  int result = check_for_right_num('9');
  int expected = 0;
  ASSERT_EQUAL(expected, result);
}

CTEST(right_char, Correct) {
  int result = check_for_right_char('a');
  int expected = 1;
  ASSERT_EQUAL(expected, result);
}

CTEST(right_char, Incorrect) {
  int result = check_for_right_char('z');
  int expected = 0;
  ASSERT_EQUAL(expected, result);
}

CTEST(turn, Correct) {
  int result = turn(1);
  int expected = 0;
  ASSERT_EQUAL(expected, result);
}

CTEST(cur_ch, Correct) {
  char arr[I][J];
  FILE *file;
  file = fopen("src/board.txt", "r");
  printf("\n\n");
  print_initial_board(arr, file);
  int result = F_current_char(arr, 'a');
  int expected = 1;
  ASSERT_EQUAL(expected, result);
}

CTEST(cur_ch, Incorrect) {
  char arr[I][J];
  FILE *file;
  file = fopen("src/board.txt", "r");
  printf("\n\n");
  print_initial_board(arr, file);
  int result = F_current_char(arr, 'z');
  int expected = 0;
  ASSERT_EQUAL(expected, result);
}

CTEST(Pawn, Correct) {
  char arr[I][J];
  FILE *file;
  file = fopen("src/board.txt", "r");
  printf("\n\n");
  print_initial_board(arr, file);
  int result = pawn_move(1, arr, 5, 6, 'e', '3');
  int expected = 0;
  ASSERT_EQUAL(expected, result);
}

CTEST(Pawn, Incorrect) {
  char arr[I][J];
  FILE *file;
  file = fopen("src/board.txt", "r");
  printf("\n\n");
  print_initial_board(arr, file);
  int result = pawn_move(1, arr, 5, 6, 'e', '5');
  int expected = 0;
  ASSERT_EQUAL(expected, result);
}

CTEST(Knight, Correct) {
  char arr[I][J];
  FILE *file;
  file = fopen("src/board.txt", "r");
  printf("\n\n");
  print_initial_board(arr, file);
  int result =   knight_move(arr, 2, 7, 'c', '3');
  int expected = 1;
  ASSERT_EQUAL(expected, result);
}

CTEST(Knight, Incorrect) {
  char arr[I][J];
  FILE *file;
  file = fopen("src/board.txt", "r");
  printf("\n\n");
  print_initial_board(arr, file);
  int result =   knight_move(arr, 2, 7, 'c', '4');
  int expected = 0;
  ASSERT_EQUAL(expected, result);
}

int main(int argc, const char **argv) { return ctest_main(argc, argv); }
