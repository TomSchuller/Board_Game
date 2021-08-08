
/*************** FUNCTION DECLARATIONS ***************
 * This file contains the function declarations of functions that make operations on movesList lists.
*****************************************************/

#ifndef FINAL_PROJECT_MOVESLIST_FUNCTIONS
#define FINAL_PROJECT_MOVESLIST_FUNCTIONS

#include "Final_Project.h"

/****************************
 * make_empty_list()
 * This function makes an empty list.
 ****************************/
movesList* make_empty_list();

/****************************
 * is_empty_list()
 * This function returns 1 if a list is empty or 0 otherwise.
 ****************************/
int is_empty_list(movesList list);

/****************************
 * insert_move_to_tail()
 * This function inserts a new node to end of the list.
 ****************************/
void insert_move_to_tail(movesList* list, Move move);

/****************************
 * insert_move_to_head()
 * This function inserts a new node to beginning of list.
 ****************************/
void insert_move_to_head(movesList* list, Move move);

/****************************
 * remove_node()
 * This function removes a node from the list using its' previous and after linked nodes.
 ****************************/
void remove_node(moveCell* prev, moveCell* after);

/****************************
 * create_node()
 * This function creates a new node.
 ****************************/
moveCell* create_node(Move move, moveCell* next);

/****************************
 * print_list()
 * This function prints a list.
 ****************************/
void print_list(movesList* list);

/****************************
 * free_list()
 * This function frees a list.
 ****************************/
void free_list(movesList* list);

/*****************************
 * display_rec()
 * This function receives a head node of a moves list and checks each move from the starting point.
 * If a move is valid then it is printed, else the move is removed from the list.
 * Variable count counts the amount of valid moves.
*****************************/
int display_rec(moveCell* head, boardPos start, char **board, int count);

/*****************************
 * positions_to_list()
 * This function receives a bordPosArray array and inserts its positions to a movesList list.
*****************************/
movesList *positions_to_list(boardPosArray* array);

#endif
