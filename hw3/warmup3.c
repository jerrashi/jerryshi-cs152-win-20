#include <stdio.h>
#include <stdlib.h>
#include "warmup3.h"
#include <limits.h>

/* print_board
 * prints the contents of the checkerboard.
 * The pieces are 'b', 'w', the kinged ones
 * are 'B'and 'W', and empty spaces are '*'
 * inputs:
 *    char board[NUM_ROWS][NUM_COLS] - an NUM_ROWSxNUM_COLS board
 * outputs:
 *    none. prints the results.
 */
void print_board( char board[NUM_ROWS][NUM_COLS] )
{
        unsigned int i, j;
        printf("   ");
        for(j=0;j<NUM_COLS;j++)
        {
                printf("%u ",j);
        }
        printf("\n");
        for(i=0;i<NUM_ROWS;i++)
        {
                printf("%u: ",i);
                for(j=0;j<NUM_COLS;j++)
                {
                        printf("%c ",board[i][j]);
                }
                printf("\n");
        }
}

/* init_board
 * initializes the contents of the checkerboard.
 * The blue pieces occupy rows 0 to ((NUM_ROWS/2) - 2), and
 * the white pieces occupy rows ((NUM_ROWS/2) + 1) to NUM_ROWS-1
 * An 8x8 board looks like this:
   * b * b * b * b
   b * b * b * b *
   * b * b * b * b
   * * * * * * * *
   * * * * * * * *
   w * w * w * w *
   * w * w * w * w
   w * w * w * w *
 * inputs:
 *    char board[NUM_ROWS][NUM_COLS] - an NUM_ROWSxNUM_COLS board
 * outputs:
 *    none. prints the results.
 */
void init_board(char board[NUM_ROWS][NUM_COLS])
{
	int row = 0, col = 0, blue_max = ((NUM_ROWS/2) - 2);
	int white_min = ((NUM_ROWS/2) + 1);
	while (row <= blue_max) // fill in blue side
	{
		for (col = 0; col < NUM_COLS; col++)
		{
			if ((row + col) % 2 == 0)
			{
				board[row][col] = '*';
			}
			else
			{
				board[row][col] = 'b';
			}
		}
		row++;
	}

	while (row < white_min) // fill in middle of board
	{
		for (col = 0; col < NUM_COLS; col++)
			board[row][col] = '*';
		row++;
	}

	while (row < NUM_ROWS) // fill in white side
	{
		for (col = 0; col < NUM_COLS; col++)
		{
			if ((row + col) % 2 ==0)
			{
				board[row][col] = '*';
			}
			else
			{
				board[row][col] = 'w';
			}
		}
		row++;
	}
}

/* place_piece
 * Checkes to see if a given position is within board bounds and unoccupied.
 * If position is valid, piece is placed there.
 * inputs:
 *    char board - chess board with NUM_ROWS rows and NUM_COLS columns
 *    char player - player whose piece might be placed
 *    u int row - row of proposed position
 *    u int col - column of proposed position
 * outputs:
 *    1 - piece successfully placed
 *    0 - piece was not placed
 */
unsigned int place_piece(char board[NUM_ROWS][NUM_COLS], char player, 
			unsigned int row, unsigned int col)
{
	if ((player == 'b') || (player == 'w'))
	{
		if ((row < NUM_ROWS) && (col < NUM_COLS) && 
			board[row][col] == '*')
		{
			board[row][col] = player;
			return 1;
		}
	}
	return 0;
}

/* area_and_perimeter
 * Takes a rectangle of given height and length and calculates the area and perimeter.
 * inputs:
 *    double height - height of rectangle
 *    double width - width of rectangle
 *    double *area - pointer that will point to area of rectangle
 *    double *perimeter - pointer that will point to area of rectangle
 * outputs:
 *    none
 */
void area_and_perimeter(double height, double length, double *area, 
			double *perimeter)
{
	if ((height <= 0) || (length <= 0))
		printf("AREA_AND_PERIMETER ERROR: only positive values" 
			"supported\n");
	double a = height * length;
	*area = a;
	double p = (2 * height) + (2 * length);
	*perimeter = p;
}

/* remove_max
 * Removes maximum value from array.
 * inputs:
 *    int array[] - an array to be processed
 *    int length - length of array
 * outputs:
 *    int max - maximum value of array
 *    original array is not returned but remains altered
 */
int remove_max(int array[], unsigned int length)
{
	int max = 0, count, ifcount;
	for (count = 0; count < length; count++) //finding maximum value
	{
		if (array[count] > max)
			max = array[count];
	}

        #ifndef DEBUG
        printf("This array has a maximum value of %d\n", max);
	printf("and has the following values: (before transformation)\n");
	for (count = 0; count < length; count++) //print out values of array
	{
		printf("Array[%d] = %d\n", count, array[count]);
	}
        #endif
	
	for (count = 0; count < length; count++) //iterate through array
	{
		if (array[count] == max) // remove max value from array
		{
			for (ifcount = count; ifcount + 1 < length; ifcount++)
			{
				array[ifcount] = array[ifcount + 1];
			}
		}
	}

	#ifndef DEBUG
	printf("After transformation, the array has the following values:\n");
	for (count = 0; count < length; count++) //print out array
        {
                printf("Array[%d] = %d\n", count, array[count]);
        }
	printf("-----\n");
	#endif

	return max;
}

/* remove_max_in_out
 * Removes occurence(s) of the maximum value of an array and updates array length.
 * intputs:
 *    int array[] - an array to be processed
 *    u int *length - address of location holding the length
 * outputs:
 *    int max - maximum value of array
 *    original array and length are not returned but are altered
 */
int remove_max_in_out(int array[], unsigned int *length)
{
        int new_length = *length, max = 0, count, ifcount;
        for (count = 0; count < *length; count++) //finding maximum value
        {
                if (array[count] > max)
                        max = array[count];
        }

        #ifndef DEBUG
        printf("This array has a maximum value of %d\n", max);
        printf("and has the following values: (before transformation)\n");
        for (count = 0; count < *length; count++) //print out values of array
        {
                printf("Array[%d] = %d\n", count, array[count]);
        }
        #endif

        for (count = 0; count < *length; count++) //iterate through array
        {
                if (array[count] == max) // remove max value from array
                {
                        for (ifcount = count; ifcount + 1 < *length; ifcount++)
                        {
                                array[ifcount] = array[ifcount + 1];
                        }
			new_length--;
                }
        }
	
	*length = new_length;

        #ifndef DEBUG
        printf("After transformation, the array has the following values:\n");
        for (count = 0; count < *length; count++) //printing out the array
        {
                printf("Array[%d] = %d\n", count, array[count]);
        }
	printf("and has a new length of %d\n", *length);
        printf("-----\n");
        #endif

        return max;
}
