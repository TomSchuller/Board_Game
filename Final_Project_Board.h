
/*************** FUNCTION DECLARATIONS ***************
 * This file contains the function declarations of functions that make operations on char** boards.
*****************************************************/

#ifndef FINAL_PROJECT_BOARD_FUNCTIONS
#define FINAL_PROJECT_BOARD_FUNCTIONS

#include "Final_Project.h"

/****************************
 * make_empty_board()
 * This function makes an empty board.
 ****************************/
void make_empty_board(char*** board);

/****************************
 * display_board()
 * This function receives a board and prints it.
 * Note that the maximum size of the board is given.
 ****************************/
void display_board(char** board);

/****************************
 * print_row_margin()
 * This function is used by display_board().
 * It prints a row margin.
 ****************************/
void print_row_margin();

/****************************
 * is_valid_move()
 * This function returns 1 if the position is a valid position on a board or 0 otherwise.
 ****************************/
bool is_valid_move(char** board, int unsigned row, int unsigned col);

/****************************
 * is_out_of_bounds()
 * This function returns 1 if the position is out of the game's frame or 0 otherwise.
 ****************************/
bool is_out_of_bounds(unsigned int row, unsigned int col);

/****************************
 * letter_to_row()
 * This function returns the integer value of the row letter.
 ****************************/
int letter_to_row(char row);

/****************************
 * num_to_col()
 * This function returns the integer value of column number.
 ****************************/
int num_to_col(char num);

/*****************************
* board_is_full()
* This function returns 1 if the board is full and 0 if not.
*****************************/
int board_is_full(char** board);

/*****************************
* copy_board()
* This functions copies a char** board.
*****************************/
void copy_board(char** dest, char** source);

/*****************************
* freeBoard()
* This functions frees a board.
*****************************/
void freeBoard(char** board);

/*****************************
* is_route()
* This function returns true if the boardPos arr represent a legal a route else false.
*****************************/
bool is_route(boardPos *arr, int size, movesArray **moves);

/*****************************
* count_stars()
* This function returns the number of boarsPos that hold stars in the board.
*****************************/
int count_stars(char** board);

#endif