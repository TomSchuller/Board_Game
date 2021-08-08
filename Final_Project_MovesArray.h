
/*************** FUNCTION DECLARATIONS ***************
 * This file contains the function declarations of functions that make operations on movesArray arrays.
*****************************************************/

#ifndef FINAL_PROJECT_MOVESARRAY_FUNCTIONS
#define FINAL_PROJECT_MOVESARRAY_FUNCTIONS

#include "Final_Project.h"

/****************************
 * make_empty_moves_array()
 * This function makes an empty MovesArray array.
 ****************************/
void make_empty_moves_array(movesArray*** moveArray);

/*****************************
* filter_movements()
* Receive as an input a movesArray pointer, a char pointer array, and two ints for row and col.
* The function will use a helper functions to check if the moves inside the array are legal or not
* And will use a helper function to remove the illegal moves in the movesArray we got.
*****************************/
void filter_movements(movesArray *moves, char **board, unsigned int row, unsigned int col);

/*****************************
* remove_illegal_movement()
* Receive as an input a movesArray pointer, and unsigned int of the specific movement which is illegal.
* The function will remove the unsigned int moves it got in the movesArray we received.
*****************************/
void remove_illegal_movement(movesArray *moves, unsigned int k_move);

/*****************************
* create_moves()
* This function copies a given movesArray array to a new one and returns it.
*****************************/
movesArray **create_moves(movesArray **moves);

/*****************************
* free_moves()
* Receive as an input a movesArray
* The function will use a helper function to create the pathtree.
* Returns the pathTree.
*****************************/
void free_moves(movesArray **moves);

#endif