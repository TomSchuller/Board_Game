
/*************** FUNCTION DEFINITIONS ***************
 * This file contains the function definitions of functions that make operations on pathTree trees.
*****************************************************/

#include "Final_Project_Trees.h"
#include "Final_Project_Board.h"
#include "Final_Project_MovesList.h"
#include "Final_Project_MovesArray.h"

treeNode* findAllPossiblePathsHelper(boardPos start, movesArray **moves, char **board) {
	treeNode *current;
	int i = start[0] - 'A';
	int j = start[1] - '1';
	unsigned int k;
	movesArray cur_moves;
	treeNodeListCell **rootp; // pointer to a treeNode pointer
	treeNodeListCell *children;
	movesArray **temp; // the move array we can ran over
	temp = create_moves(moves);
	// update the moves
	validMoves(temp, board);
	// moves of the specific boardPos
	cur_moves = temp[i][j];
	//create the node itself
	current = (treeNode *)malloc(sizeof(treeNode));
	checkAlloc(current);

	current->position[0] = start[0];
	current->position[1] = start[1];
	board[i][j] = '*'; //update the board for the next
	rootp = &current->next_possible_positions;
	for (k = 0; k < cur_moves.size; k++) {
		boardPos new = { 0 };
		children = (treeNodeListCell *)malloc(sizeof(treeNodeListCell));
		checkAlloc(children);

		new[0] = current->position[0] + temp[i][j].moves[k].rows;
		new[1] = current->position[1] + temp[i][j].moves[k].cols;

		children->node = findAllPossiblePathsHelper(new, moves, board);
		*rootp = children;
		rootp = &(children->next);
	}
	*rootp = NULL; // the last node
	board[i][j] = ' '; //update the board back to not change it
	free_moves(temp);

	return current;
}

void find_full_path(treeNode* head, char** board, movesList* list, int index) {
	int row, col;
	Move move;
	row = letter_to_row(head->position[0]);
	col = num_to_col(head->position[1]);
	board[row][col] = (char)(index + 48);
	// We've reached a leaf, meaning end of path.
	if (head->next_possible_positions == NULL) {
		// If board is full, it is a full path, so we ass the current position to the list.
		if (board_is_full(board)) {
			move.rows = (char)(row + 48);
			move.cols = (char)(col + 48);
			insert_move_to_head(list, move);
		}
		// Else we clear the position from the board.
		else board[row][col] = ' ';
	}
	else {
		// Go through path.
		find_full_path(head->next_possible_positions->node, board, list, index + 1);
		// If board is full, we've reached a full path, so we enter the previous positions.
		if (board_is_full(board)) {
			move.rows = (char)(row + 48);
			move.cols = (char)(col + 48);
			insert_move_to_head(list, move);
		}
		else {
			// Else we clear all the positions of path that we confirmed is not full.
			board[row][col] = ' ';
			// If a father has more children we check to see if they lead to a full path.
			if (head->next_possible_positions->next != NULL && !board_is_full(board)) {
				find_full_path(head->next_possible_positions->next->node, board, list, index + 1);
			}
		}
	}
}