
/*************** FUNCTION DEFINITIONS ***************
 * This file contains the function definitions of the Project's sections
 * and a general function, checkAlloc().
*****************************************************/
#include "Final_Project.h"
#include "Final_Project_Board.h"
#include "Final_Project_MovesArray.h"
#include "Final_Project_MovesList.h"
#include "Final_Project_Trees.h"
#include "Final_Project_Binary.h"

boardPosArray ** validMoves(movesArray **moves, char **board) {
	boardPosArray **res = (boardPosArray **)malloc(N * sizeof(boardPosArray *));
	checkAlloc(res);
	unsigned int i, j, k;

	for (i = 0; i < N; i++)
	{
		res[i] = (boardPosArray *)malloc(M * sizeof(boardPosArray));
		checkAlloc(res[i]);
		for (j = 0; j < M; j++)
		{
			// filter the illegal moves
			filter_movements(&moves[i][j], board, i, j);
			res[i][j].positions = (boardPos *)malloc(moves[i][j].size * sizeof(boardPos));
			checkAlloc(res[i][j].positions);
			// insert each position it's possible movements position
			res[i][j].size = moves[i][j].size;
			for (k = 0; k < moves[i][j].size; k++)
			{
				res[i][j].positions[k][0] = i + moves[i][j].moves[k].rows + 'A';
				res[i][j].positions[k][1] = j + moves[i][j].moves[k].cols + '1';
			}
		}
	}

	return res;
}

int display(movesList *moves_list, boardPos start, char **board, int size) {
	// Make an copy of board to write on and display.
	char** boardP;
	make_empty_board(&boardP);
	copy_board(boardP, board);
	int row, col;
	row = letter_to_row(start[0]);
	col = num_to_col(start[1]);
	// Insert starting position.
	boardP[row][col] = '#';
	// Enter the path to the board.
	int count = display_rec(moves_list->head->next, start, boardP, 0);
	// Display the board.
	display_board(boardP);
	freeBoard(boardP);
	return (size - count);
}

pathTree findAllPossiblePaths(boardPos start, movesArray **moves, char **board) {
	pathTree tree;
	tree.head = findAllPossiblePathsHelper(start, moves, board);
	return tree;
}

movesList *findPathCoveringAllBoard(boardPos start, movesArray **moves, char **board) {
	Move move;
	move.rows = (char)(start[0] - 'A');
	move.cols = (char)(start[1] - '0');
	movesList *path;
	pathTree tree;
	// Make a tree of all possible paths.
	tree = findAllPossiblePaths(start, moves, board);
	// Create and initialize a board to write on.
	char** boardP;
	make_empty_board(&boardP);
	copy_board(boardP, board);
	// Initialize list.
	path = make_empty_list();
	// Find full path.
	find_full_path(tree.head, boardP, path, 0);
	if (board_is_full(boardP)) {
		freeBoard(boardP);
		return path;
	}
	else {
		free_list(path);
		freeBoard(boardP);
		return NULL;
	}
}

void saveListToBinFile(char *file_name, boardPosArray *pos_arr) {
	FILE *positions;
	char *bin_file_name;
	unsigned char *shortPosition;
	unsigned int numberOfElements;
	short int size = (short int)pos_arr->size;
	if (size > 0) {
		bin_file_name = (char *)malloc(strlen(file_name) + 1);
		checkAlloc(bin_file_name);
		strcpy(bin_file_name, file_name);
		strcat(bin_file_name, ".bin");
		positions = fopen(bin_file_name, "wb");
		checkAlloc(positions);
		// Write amount of positions.
		fwrite(&size, sizeof(short int), 1, positions);
		// Compress the positions of the current cell.
		shortPosition = position_to_short(pos_arr, size, &numberOfElements);
		// Write to binary file.
		fwrite(shortPosition, sizeof(unsigned char *), numberOfElements, positions);
		// Close file.
		fclose(positions);
	}
}

int checkAndDisplayPathFromFile(char *file_name, movesArray **moves, char **board) {
	FILE *fp;
	boardPosArray board_pos_arr;
	short int size_of_elements;
	char** boardP; // Make new board to keep the original board
	movesList* path;
	int illegal_moves, size, stars, board_size;

	fp = fopen(file_name, "rb");
	if (fp == NULL) //check file, if the folder doesn't exists, return -1
		return (-1);

	fread(&(size_of_elements), sizeof(short int), 1, fp);
	board_pos_arr.size = (unsigned int)size_of_elements;
	board_pos_arr.positions = (boardPos *)malloc(board_pos_arr.size * sizeof(boardPos));
	checkAlloc(board_pos_arr.positions);

	get_boardPos_arr(board_pos_arr.positions, (int)board_pos_arr.size, fp);
	fclose(fp);

	// check if the board pos are a route
	if (!(is_route(board_pos_arr.positions, (int)board_pos_arr.size, moves)))
		return 1;

	// if im here the func is a route. 
	make_empty_board(&boardP);
	copy_board(boardP, board);
	path = positions_to_list(&board_pos_arr); // Make path from pos_arr i send the address

   // print board, and get the illegal moves
	illegal_moves = display(path, board_pos_arr.positions[0], boardP, board_pos_arr.size); //---- display the path on the board
	stars = count_stars(boardP);
	size = board_pos_arr.size - illegal_moves + stars + 1; // for starting point
	board_size = N * M;

	if (size == board_size)
	{
		free(boardP);
		return 2; // if the board is full return 2
	}
	else
	{
		free(boardP);
		return 3; //  else return 3
	}
}

void checkAlloc(void  *memp)
{
	if (memp == NULL)
	{
		printf("Allocation Failed!\n");
		exit(1);
	}
}