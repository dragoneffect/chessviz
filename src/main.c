#include "board.h"
#include "board_print_plain.h"
#include "const.h"
#include "conversion.h"

int main() {
  //файл с изначальным состоянием доски
  FILE *file;
  //файл, куда записываются ходы
  FILE *notes;
  //массив, содержащий в себе элементы доски
  char arr_b[I][J];
  // choice, choice2 - флаги
  int choice = -1;
  //int choice2 = -1;
  // result - переменная, хранящая в себе количество ходов
  int result = -1;
  /*в переменной flag хранится значение очередности хода. если значение равно 1,
  то ходят белые, если 0 - то черные */
  int flag = 1;
  //открываем нужные файлы
  file = fopen("src/board.txt", "r");
  notes = fopen("build/notes.txt", "w+");
  //если удалось открыть файл с доской
  if (file) {
    //если удалось открыть файл с записями
    if (notes) {
      print_initial_board(arr_b, file);
      //закрываем файл доски, нам он уже больше не нужен
      fclose(file);
      do {
        //ввод количества ходов
        result = read(choice, "How many moves do you want to make?");
        if (!result) {
          printf("Please, try again\n");
        }
      } while (!result);
      //пока ходы не закончились
      while (result != 0) {
        //делаем ход
        result = make_a_move(result, arr_b, flag, notes);
        //записываем позицию доски в файл и выводим ее на экран
        print_board(arr_b, notes);
        //переключаем очередность движения
        flag = turn(flag);
      }
    } else {
      printf("\nCannot open file: notes.txt");
    }
  } else {
    printf("\nCannot open file: board.txt");
  }
  fclose(notes);
  return 0;
}
