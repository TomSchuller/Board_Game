
/*************** FUNCTION DEFINITIONS ***************
 * This file contains the function definitions of functions that make operations on movesList lists.
*****************************************************/

#include "Final_Project_MovesList.h"
#include "Final_Project_Board.h"

movesList* make_empty_list() {
	movesList* list = (movesList*)malloc(sizeof(movesList));
	checkAlloc(list);
	Move move;
	move.rows = '*';
	move.cols = '*';
	list->head = create_node(move, NULL);
	list->tail = create_node(move, NULL);
	list->head->next = list->tail;
	list->tail->prev = list->head;
	return list;
}

int is_empty_list(movesList list) {
	return (list.head->next == list.tail);
}

void insert_move_to_tail(movesList* list, Move move) {
	moveCell* newNode, *temp;
	newNode = create_node(move, NULL);

	if (is_empty_list(*list)) {
		list->head->next = newNode;
		newNode->prev = list->head;
		newNode->next = list->tail;
		list->tail->prev = newNode;
	}
	else {
		temp = list->tail->prev;
		temp->next = newNode;
		newNode->prev = temp;
		newNode->next = list->tail;
		list->tail->prev = newNode;
	}
}

void insert_move_to_head(movesList* list, Move move) {
	moveCell* newNode, *temp;
	newNode = create_node(move, NULL);

	if (is_empty_list(*list)) {
		list->head->next = newNode;
		newNode->prev = list->head;
		newNode->next = list->tail;
		list->tail->prev = newNode;
	}
	else {
		temp = list->head->next;
		newNode->next = temp;
		temp->prev = newNode;
		list->head->next = newNode;
		newNode->prev = list->head;
	}
}

void remove_node(moveCell* prev, moveCell* after) {
	moveCell* toDelete = prev->next;
	prev->next = after;
	after->prev = prev;
	free(toDelete);
}

moveCell* create_node(Move move, moveCell* next) {
	moveCell* newNode;
	newNode = (moveCell*)malloc(sizeof(moveCell));
	checkAlloc(newNode);
	newNode->move = move;
	newNode->next = next;
	return newNode;
}

void print_list(movesList* list) {
	moveCell* temp = list->head->next;

	while (temp != list->tail) {
		printf("Row: %c, Col: %c\n", (temp->move.rows /*+ 17*/), temp->move.cols /*+ 1*/);
		temp = temp->next;
	}
}
void free_list(movesList* list) {
	moveCell *node, *temp;

	if (is_empty_list(*list)) {
		free(list->head);
		free(list->tail);
		return;
	}
	else {
		node = list->head;
		while (node->next != NULL) {
			temp = node;
			node = node->next;
			free(temp);
		}
		free(node);
	}
}

int display_rec(moveCell* head, boardPos start, char **board, int count) {
	unsigned int row, col;
	char rowCh, colCh;
	boardPos newPos;
	moveCell* temp;
	if (head->next == NULL) {
		return count;
	}
	else {
		// Get position.
		rowCh = head->move.rows;
		colCh = head->move.cols;
		newPos[0] = (char)(start[0] + (char)rowCh);
		newPos[1] = (char)(start[1] + (char)colCh);
		row = letter_to_row(newPos[0]);
		col = num_to_col(newPos[1]);
		// Check if valid. If not remove the node.
		if (!is_out_of_bounds(row, col) && is_valid_move(board, row, col)) {
			count++;
			board[row][col] = (char)(count + 48);
			head = head->next;
			strcpy(start, newPos);
		}
		else {
			temp = head->next;
			remove_node(head->prev, temp);
			head = temp;
		}
	}
	return display_rec(head, start, board, count);
}

movesList* positions_to_list(boardPosArray* array) {
	unsigned int size = array->size;
	Move move, prev_move, temp;
	movesList* list;
	list = make_empty_list();

	prev_move.rows = (char)(array->positions[0][0] - 'A');
	prev_move.cols = (char)(array->positions[0][1] - '1');

	for (int i = 1; i < (int)size; i++) {
		// Make move.
		temp.rows = ((char)(array->positions[i][0] - 'A'));
		temp.cols = ((char)(array->positions[i][1] - '1'));

		move.rows = (temp.rows - prev_move.rows);
		move.cols = (temp.cols - prev_move.cols);

		prev_move.rows = temp.rows;
		prev_move.cols = temp.cols;
		// Insert to tail.
		insert_move_to_tail(list, move);
	}
	return list;
}