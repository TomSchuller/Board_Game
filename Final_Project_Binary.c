
/*************** FUNCTION DEFINITIONS ***************
 * This file contains the function definitions of functions that make operations on bits.
*****************************************************/

#include "Final_Project_Binary.h"
#include "Final_Project_Board.h"

unsigned char* position_to_short(boardPosArray* pos, unsigned int size, unsigned int* numberOfElements) {
	unsigned char* positionLine, shiftRow, shiftCol;
	int bitCounter = 5, posLineIndex = 0;
	// 16 for two bytes for number of positions, (row, col) each has 3 bits.
	// Divide by 8 (number of bits in one byte).
	unsigned numOfBytes = (16 + (3 * size * 2)) / 8;
	// Dismiss the byte for the number of positions.
	*numberOfElements = (numOfBytes - 1);
	// Initialize array to all zeros // 0000 0000
	positionLine = (unsigned char*)calloc(*numberOfElements, sizeof(unsigned char));
	checkAlloc(positionLine);

	// Go through each position.
	for (int i = 0; i < (int)size; i++) {
		// Set bits of row.
		shiftRow = letter_to_row(pos->positions[i][0]);
		// If the bitCounter reached end of byte.
		if (bitCounter <= 0) {
			// Split the bits into current and next byte and get the new index.
			split_bits(positionLine, &posLineIndex, shiftRow, bitCounter);
			bitCounter += 5;
		}
		// Else shift the row bitCounter's amount of bits to the left and insert to current byte.
		else {
			shiftRow = shiftRow << bitCounter;
			positionLine[posLineIndex] = positionLine[posLineIndex] ^ shiftRow;
			bitCounter -= 3;
		}
		// Set bits of column.
		shiftCol = num_to_col(pos->positions[i][1]);
		// If the bitCounter reached end of byte.
		if (bitCounter <= 0) {
			// Split the bits into current and next byte and get the new index.
			split_bits(positionLine, &posLineIndex, shiftCol, bitCounter);
			bitCounter += 5;
		}
		// Else shift the row bitCounter's amount of bits to the left and insert to current byte.
		else {
			shiftCol = shiftCol << bitCounter;
			positionLine[posLineIndex] = positionLine[posLineIndex] ^ shiftCol;
			bitCounter -= 3;
		}
	}
	// Return the array.
	return positionLine;
}

void split_bits(unsigned char* dest, int* index, unsigned char position, int bitCounter) {
	unsigned char splitBits1, splitBits2, mask;
	// How many bits for previous char.
	splitBits1 = bitCounter * -1;
	// How many for next char.
	splitBits2 = bitCounter + 8;
	// Make mask for previous char.
	mask = position >> splitBits1;
	// Insert data into position.
	(dest[*index]) = (dest[*index]) ^ mask;
	// Move to next char.
	*index = *index + 1;
	// Make mask for current char.
	mask = position << splitBits2;
	// Insert data into position.
	dest[*index] = dest[*index] ^ mask;
}

void get_boardPos_arr(boardPos *arr, int size, FILE *fp)
{
	BYTE position[3]; // read max 3 bits at a time
	int counter = 0;

	while (counter < size)
	{
		if ((size - counter) > 3) // read regular
		{
			fread(position, sizeof(BYTE), 3, fp);
			get_Decoded_Data(position, arr, &counter, 4); // i is the pos in the array  
		}
		else // need to divide by situations: 1 pos (6 bytes), 2 pos (12 bytes), 3 pos (18 bytes)
		{
			if (((size - counter) % 4) == 1) // only 1 pos (6 bytes)
			{
				fread(position, sizeof(BYTE), 1, fp);
				get_Decoded_Data(position, arr, &counter, 1);
			}
			else if (((size - counter) % 4) == 2) // only 2 pos (12 bytes)
			{
				fread(position, sizeof(BYTE), 2, fp);
				get_Decoded_Data(position, arr, &counter, 2);
			}
			else // only 3 pos (18 bytes)
			{
				fread(position, sizeof(BYTE), 3, fp);
				get_Decoded_Data(position, arr, &counter, 3);
			}
		}
	}	// while
}

void get_Decoded_Data(BYTE *data, boardPos *arr, int *pos, int option) // 4 pos at a time, each pos is 6 bytes and 3 bit therfor 24 bytes
{
	// we can calculate the mask:
	BYTE mask1 = 0xE0;	//11100000  byte 1 (most significant byte - the left most one)
	BYTE mask2 = 0x1C;	//00011100  byte 1
	BYTE mask3a = 0x03, mask3b = 0x80;	//0000001110000000 bytes 1+2 
	BYTE mask4 = 0x70;	//01110000  byte 2
	BYTE mask5 = createMask(3, 1);	//00001110  byte 2
	BYTE mask6a = createMask(1, 0);
	BYTE mask6b = createMask(2, 6);	//00000001 11000000 bytes 2+3
	BYTE mask7 = createMask(3, 3);	//00111000  byte 3 (least significant byte)
	BYTE mask8 = createMask(3, 0);	//00000111	byte 3 

	arr[*pos][0] = (((data[0] & mask1) >> 5) + 'A');  //should be B1 but its C2
	arr[*pos][1] = (((data[0] & mask2) >> 2) + '1');
	(*pos)++; // finished the 1 pos

	if (option > 1)
	{
		arr[*pos][0] = ((((data[0] & mask3a) << 1) | ((data[1] & mask3b) >> 7)) + 'A');
		arr[*pos][1] = (((data[1] & mask4) >> 4) + '1');
		(*pos)++; // finished the 2 pos
	}

	if (option > 2)
	{
		arr[*pos][0] = (((data[1] & mask5) >> 1) + 'A');
		arr[*pos][1] = ((((data[1] & mask6a) << 2) | ((data[2] & mask6b) >> 6)) + '1');
		(*pos)++; // finished the 3 pos
	}

	if (option > 3)
	{
		arr[*pos][0] = (((data[2] & mask7) >> 3) + 'A');
		arr[*pos][1] = ((data[2] & mask8) + '1');
		(*pos)++;// finished the 4 pos
	}

}

BYTE createMask(int numOfBits, int startBit)
{
	int i;
	BYTE mask = 0;

	for (i = 0; i < numOfBits; i++)
	{
		mask <<= 1; // the same as writemask = mask << 1
		mask |= 1;
	}

	return (mask <<= startBit);
}