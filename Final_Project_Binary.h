
/*************** FUNCTION DECLARATIONS ***************
 * This file contains the function declarations of functions that make operations on bits.
*****************************************************/

#ifndef FINAL_PROJECT_BINARY_FUNCTIONS
#define FINAL_PROJECT_BINARY_FUNCTIONS

#include "Final_Project.h"

/**********
 * position_to_short()
 * This function compresses all possible positions of a boardPos cell to an array and returns it.
 **********/
unsigned char* position_to_short(boardPosArray* pos, unsigned int size, unsigned int* numberOfElements);

/****************************
 * split_bits()
 * This function splits bits into current and next bytes.
 ****************************/
void split_bits(unsigned char* dest, int* index, unsigned char position, int bitCounter);

/****************************
 * get_Decoded_Data()
 * This function decode the bytes to a boardPos arr.
 ****************************/
void get_Decoded_Data(BYTE *data, boardPos *arr, int *pos, int option);

/****************************
 * createMask()
 * This function creates mask to find specific bytes, and return it.
 ****************************/
BYTE createMask(int numOfBits, int startBit);

/****************************
 * get_boardPos_arr()
 * This function read from a binary file, decode the bytes with an helper function and push them to a boardPos arr.
 ****************************/
void get_boardPos_arr(boardPos *arr, int size, FILE *fp);

#endif