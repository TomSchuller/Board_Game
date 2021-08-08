
/*************** FUNCTION DECLARATIONS ***************
 * This file contains the function declarations of functions that make operations on pathTree trees.
*****************************************************/

#ifndef FINAL_PROJECT_TREES_FUNCTIONS
#define FINAL_PROJECT_TREES_FUNCTIONS

#include "Final_Project.h"

/***************************
 * findAllPossiblePathsHelper()
 * Receive as an input a boardPos of the start cell, two-dimensional array type movesArray,
 * it's size is the game board size, each cell holds all the optional moves from the cell itself.
 * And a two-dimensional array type char, it's size is the game board size, each cell holds ' '- movable or '*' - can't go
 * The function will remove form the each cell in moves the illegal moves.
 * Illegal moves are : out of the board frame or to a cell which hold '*'
 * The function will create a treeNode node with the start node data.
 * The function will create another board that it will run over to update the boardPos we have been at.
 * The function will use a pointer to a treeNode pointer to connect it's sons and brothers in recursive.
***************************/
treeNode* findAllPossiblePathsHelper(boardPos start, movesArray **moves, char **board);

/***************************
 * find_full_path()
 * This function finds a full path in a given tree and inserts the path to a given list.
 * The function inserts positions of a certain path to a given board and checks each iteration
 * if the board is full. If not it checks other paths until end of tree.
****************************/
void find_full_path(treeNode* head, char** board, movesList* list, int index);

#endif