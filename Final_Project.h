
/*************************************
 * Name: Ofek Shavit
 * I.D: 207330671
 * Name: Tom Schuller
 * I.D: 205928146
 * Date: 23/06/2020
 * Advanced Programming Final Project - Board Game
 * This program contains functions that make operations for a board game.
 *************************************/

#ifndef FINAL_PROJECT
#define FINAL_PROJECT

#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>


 /*************** GAME SETTINGS ***************/

#define N  // rows
#define M  // cols

/*************** STRUCT DECLARATIONS ***************/

typedef char boardPos[2];

typedef struct boardPosArray {
	unsigned int size;
	boardPos *positions;
}boardPosArray;

typedef struct move {
	char rows, cols;
} Move;

typedef struct _moveCell {
	Move move;
	struct _moveCell *next, *prev;
} moveCell;

typedef struct _movesList {
	moveCell * head;
	moveCell * tail;
} movesList;

typedef struct movesArray {
	unsigned int size;
	Move *moves;
}movesArray;

typedef struct _treeNodeListCell treeNodeListCell;

typedef struct _treeNode {
	boardPos position;
	treeNodeListCell *next_possible_positions;
} treeNode;

typedef struct _treeNodeListCell {
	treeNode * node;
	struct _treeNodeListCell * next;
} treeNodeListCell;

typedef struct _pathTree {
	treeNode * head;
} pathTree;

typedef unsigned char BYTE;


/*************** FUNCTION DECLARATIONS ***************/

/***************************
* Section 1: validMoves()
* Receive as an input a two-dimensional array type movesArray, it's size is the game board size,
* Each cell holds all the optional moves from the cell itself.
* And a two-dimensional array type char, it's size is the game board size, each cell holds ' '- movable or '*' - can't go
* The function will remove form the each cell in moves the illegal moves.
* Illegal moves are: out of the board frame or to a cell which hold '*'
* The function will create a two-dimensional array type boardPosArray, it's size is the game board size,
* Each cell holds an array of all the legal moves from the cell itself.
* Returns the array.
***************************/
boardPosArray ** validMoves(movesArray **moves, char **board);

/***************************
 * Section 2: display()
 * This function wraps display_rec().
 * Receives a moves list, a starting position, a game board and size of the moves list.
****************************/
int display(movesList *moves_list, boardPos start, char **board, int size);

/***************************
 * Section 3: findAllPossiblePaths()
 * Receive as an input a boardPos of the start cell, two-dimensional array type movesArray, it's size is the game board size, each cell holds all the optional moves from the cell itself.
 * And a two-dimensional array type char, it's size is the game board size, each cell holds ' '- movable or '*' - can't go
 * The function will use a helper function to create the pathTree.
 * Returns the pathTree.
****************************/
pathTree findAllPossiblePaths(boardPos start, movesArray **moves, char **board);

/****************************
 * Section 4: findPathCoveringAllBoard()
 * This function receives a starting position, a movesArray and a board and finds a path that covers the entire board.
 * If such path exists the function returns the linked list of that path and if not the function returns NULL.
 ****************************/
movesList *findPathCoveringAllBoard(boardPos start, movesArray **moves, char **board);

/****************************
 * Section 5: saveListToBinFile()
 * This function receives a file name and a boardPos array.
 * This function saves all possible positions from each position in the array in a binary file.
 * This function uses position_to_short() to get each compressed positions of each cell.
 ****************************/
void saveListToBinFile(char *file_name, boardPosArray *pos_arr);

/****************************
 * Section 6: checkAndDisplayPathFromFile()
 * This function receives a file name and a boardPos array.
 * This function saves all possible positions from each position in the array in a binary file.
 * This function uses position_to_short() to get each compressed positions of each cell.
 ****************************/
int checkAndDisplayPathFromFile(char *file_name, movesArray **moves, char **board);

/*************** GENERAL FUNCTION DECLARATION ***************/

/****************************
 * checkAlloc()
 * A function that check if allocation of memory succeeded.
 * If not - it prints an error and exit 1 program.
 ****************************/
void checkAlloc(void  *memp);

#endif