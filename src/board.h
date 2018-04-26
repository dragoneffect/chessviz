#ifndef BOARD_H
#define BOARD_H

#include "const.h"
#include "conversion.h"
#include <assert.h>
#include <errno.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int read(int value, const char *input);
int make_a_move(int param, char arr[I][J], int color, FILE *notes_file);
int check_for_right_move(char first_char, char first_num, char last_char, char last_num);
int check_for_right_char(char ch);
int check_for_right_num(char ch);
int check_for_figure(char op, char arr[I][J], char current_ch, char current_n, char next_ch, char next_n, int color);
int turn(int white_or_black);
int pawn_move(char arr[I][J], int current_ch, int current_n, char next_ch, char next_n, int color);
int is_it_first_move(char arr[I][J], int current_ch, int current_n);
int rook_move(char arr[I][J], int current_ch, int current_n, char next_ch, char next_n);
int bishop_move(char arr[I][J], int current_ch, int current_n, char next_ch, char next_n);
int queen_move(char arr[I][J], int current_ch, int current_n, char next_ch, char next_n);
int king_move(char arr[I][J], int current_ch, int current_n, char next_ch, char next_n);
int take_or_move(char op, char arr[I][J], char next_ch, char next_n);
int knight_move(char arr[I][J], int current_ch, int current_n, char next_ch, char next_n);

#endif
