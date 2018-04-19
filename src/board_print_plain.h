#ifndef BOARD_PRINT_PLAIN_H
#define BOARD_PRINT_PLAIN_H

#include "const.h"
#include <stdio.h>

void print_initial_board(char arr[I][J], FILE *board_file);
void print_board(char arr[I][J], FILE *notes_file);

#endif
