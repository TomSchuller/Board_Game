
/*************** FUNCTION DEFINITIONS ***************
 * This file contains the function definitions of functions that make operations on char** boards.
*****************************************************/

#include "Final_Project_Board.h"

void make_empty_board(char*** board) {
	char** boardP = (char**)malloc(sizeof(char*)*N);
	checkAlloc(boardP);
	for (int i = 0; i < N; i++) {
		boardP[i] = (char*)malloc(M);
		checkAlloc(boardP[i]);
	}
	for (int i = 0; i < N; i++) {
		for (int j = 0; j < M; j++) {
			boardP[i][j] = ' ';
		}
	}
	*board = boardP;
}

void display_board(char** board) {
	char letter = 'A';
	int num = 1;
	int pos;
	// Print first row
	print_row_margin();
	printf("\n");
	for (int i = 0; i <= M; i++) {
		if (i == 0) printf("|   |");
		else printf("  %d  |", num++);
	}
	// Print rest of board.
	printf("\n");
	for (int i = 0; i < N; i++) {
		print_row_margin();
		printf("\n");
		for (int j = 0; j <= M; j++) {
			if (j == 0) printf("| %c |", letter++);
			else {
				pos = board[i][j - 1];
				if (pos >= 48) {
					pos -= 48;
					if (pos >= 10) printf("  %d |", pos);
					else printf("  %d  |", pos);
				}
				else printf("  %c  |", pos);
			}
		}
		printf("\n");
	}
	print_row_margin();
}

void print_row_margin() {
	for (int i = 0; i < M; i++) {
		if (i == 0) printf("+---");
		if (i == M - 1) printf("+-----+");
		else printf("+-----");
	}
}

bool is_valid_move(char** board, int unsigned row, int unsigned col) {
	return (board[row][col] == ' ');
}

bool is_out_of_bounds(unsigned int row, unsigned int col) {
	return (row < 0 || row >= N || col < 0 || col >= M);
}

int letter_to_row(char row) {
	return (int)(row - 'A');
}

int num_to_col(char num) {
	return (int)(num - '1');
}

int board_is_full(char** board) {
	for (int i = 0; i < N; i++) {
		for (int j = 0; j < M; j++) {
			if (board[i][j] == ' ') return 0;
		}
	}
	return 1;
}

void copy_board(char** dest, char** source) {
	for (int i = 0; i < N; i++) {
		strcpy(dest[i], source[i]);
	}
}

void freeBoard(char** board) {
	for (int i = 0; i < N; i++) {
		free(board[i]);
	}
	free(board);
}

bool is_route(boardPos *arr, int size, movesArray **moves)
{
	bool flag = false;
	boardPos place, next_place, possible_move;
	int i, j;
	int row, col;
	int size_of_moves;

	for (i = 0; i < (size - 1); i++) // going 1 less because next place
	{
		place[0] = arr[i][0];
		place[1] = arr[i][1];

		next_place[0] = arr[i + 1][0]; // going 1 too far, therfor size-1
		next_place[1] = arr[i + 1][1];
		row = letter_to_row(place[0]);
		col = num_to_col(place[1]);
		size_of_moves = (int)moves[row][col].size;

		for (j = 0; j < size_of_moves && !(flag); j++)
		{
			possible_move[0] = place[0] + moves[row][col].moves[j].rows; // change to numbers
			possible_move[1] = place[1] + moves[row][col].moves[j].cols;

			if (next_place[0] == possible_move[0])
				if (next_place[1] == possible_move[1])
					flag = true; // we found the next move in the course
		}

		if (!flag) // we didn't find the next move therfor need to return false
			return (flag);
		flag = false; // next element
	}

	return true; //!flag
}

int count_stars(char** board) {
	int count = 0;
	for (int i = 0; i < N; i++) {
		for (int j = 0; j < M; j++) {
			if (board[i][j] == '*')
				count++;
		}
	}
	return count;
}