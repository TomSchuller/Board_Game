
/*************** FUNCTION DEFINITIONS ***************
 * This file contains the function definitions of functions that make operations on movesArray arrays.
*****************************************************/

#include "Final_Project_MovesArray.h"
#include "Final_Project_Board.h"

movesArray **create_moves(movesArray **moves) {
	movesArray **res;
	int i, j;
	res = (movesArray **)malloc(sizeof(movesArray *) * N);
	checkAlloc(res);
	for (i = 0; i < N; ++i) {
		res[i] = (movesArray *)malloc(sizeof(movesArray) * M);
		checkAlloc(res[i]);
		for (j = 0; j < M; ++j) {
			res[i][j].size = moves[i][j].size;
			res[i][j].moves = (Move *)malloc(sizeof(Move) * moves[i][j].size);
			checkAlloc(res[i][j].moves);
			memcpy(res[i][j].moves, moves[i][j].moves, sizeof(Move) * moves[i][j].size);
		}
	}
	return res;
}

void free_moves(movesArray **moves) {
	int i, j;
	for (i = 0; i < N; ++i) {
		for (j = 0; j < M; ++j) {
			free(moves[i][j].moves);
		}
		free(moves[i]);
	}
	free(moves);
}

void remove_illegal_movement(movesArray *moves, unsigned int k_move) {
	unsigned int i;

	for (i = 0; i < moves->size - 1; i++)
		if (i >= k_move)
		{
			moves->moves[i] = moves->moves[i + 1];
		}
	moves->size--;
}

void filter_movements(movesArray *moves, char **board, unsigned int row, unsigned int col) {
	unsigned int i, check_row, check_col;
	for (i = 0; i < moves->size; i++)
	{
		check_row = moves->moves[i].rows + row;
		check_col = moves->moves[i].cols + col;
		if (is_out_of_bounds(check_row, check_col) || !is_valid_move(board, check_row, check_col) || board[row][col] == '*')
		{
			remove_illegal_movement(moves, i);
			i--; // check again after delete
		}
		// else - good
	}
}