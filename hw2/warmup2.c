#include <stdlib.h>
#include <stdio.h>
#include "warmup2.h"

/* print_asterisk_letter
 * input: char letter - the letter to print out
 * output: nothing returned, just printed to the screen.
 * Given a character, print the corresponding upper-case letter of the 
 * alphabet using asterisks. The letter can be anything from 'N' to 'R'. 
 */
void print_asterisk_letter(char letter)
{ 
	if ((letter == 'S') || (letter == 's'))
                {
                        printf(" ****\n");
                        printf("*    \n");
                        printf(" *** \n");
                        printf("    *\n");
                        printf("**** \n");
                }
        else if ((letter == 'T') || (letter == 't'))
                {
                        printf("*****\r\n");
                        printf("  *  \r\n");
                        printf("  *  \r\n");
                        printf("  *  \r\n");
                        printf("  *  \r\n");
                }
        else if ((letter == 'U') || (letter == 'u'))
                {
                        printf("*   *\r\n");
                        printf("*   *\r\n");
                        printf("*   *\r\n");
                        printf("*   *\r\n");
                        printf(" *** \r\n");
                }
        else if ((letter == 'V') || (letter == 'v'))
                {
                        printf("*   *\r\n");
                        printf("*   *\r\n");
                        printf("*   *\r\n");
                        printf(" * * \r\n");
                        printf("  *  \r\n");
                }
        else
                {
                        fprintf(stderr, "ERROR (print_asterik_letter): Only "
                                "acceptable input is S, T, U, or V.\r\n");
                }
}

/* draw_hourglass_rec_helper
 * draws a hourglass with asterisks. implemented recursively.
 * inputs:
 *   uint height - the number of rows to print of the wedge
 *   uint row 	 - the current row that is being printed
 *   uint offset - amount of spaces that should be to the left of this hourglass
 * outputs:
 *   nothing returned, just printed to the screen
 */

void draw_hourglass_rec_helper(unsigned int height, unsigned int row, unsigned int offset)
{ 
	if (row <= height)
	{
		int asterisks = abs(height/2 - row) * 2 + 1;
		for (int i = 1; i <= offset; ++i)
		{
			printf(" ");
		}
		for (int j = 1; j <= asterisks; ++j)
		{
			printf("*");
		}
		printf("\n");
		if (row + 1 > height/2)
		{
			draw_hourglass_rec_helper(height, row + 1, offset - 1);
		}
		else
		{
			draw_hourglass_rec_helper(height, row + 1, offset + 1);
		}
	}
	else
	{
		return;
	}
}

/* draw_hourglass_rec
 * draws a hourglass with asterisks. implemented recursively.
 * inputs:
 *   uint height - the number of rows to print of the wedge
 * outputs:
 *   nothing returned, just printed to the screen
 */

void draw_hourglass_rec(unsigned int height)
{ 
	draw_hourglass_rec_helper(height, 0, 0);
	fprintf(stderr,"error draw_hourglass_rec: not yet implemented\n");
}

/* draw_hourglass_iter
 * draws a hourglass with asterisks. Implemented iteratively.
 * inputs:
 *   uint height - the number of rows to print of the wedge
 * outputs:
 *   nothing returned, just printed to the screen
 */

void draw_hourglass_iter(unsigned int height)
{ 
	//modelled after https://www.programiz.com/c-programming/examples/pyramid-pattern
	int i = height/2, asterisks = 1, space = 1, k = 1;
	
	for (i = height/2; i >= 1; --i)
	{
		for (space = 1; space <= height/2 - i; ++space)
		{
 			printf(" ");
		}
		for (asterisks = 1; asterisks <= i * 2 + 1; ++asterisks)
		{
			printf("*");
		}
		printf("\n");
	}	

	// middle of pyramid for odd # of rows, centered asterisk
	if (height % 2 != 0)
	{
		for (k = 1; k <= space + 1; ++k)
		{
			printf(" ");
		}
		printf("*\n");
	}	

	// bottom half, pyramid shape
	for (i = 1; i <= height/2; ++i)
	{
		for (space = 1; space <= height/2 - i; ++space)
		{
			printf(" ");
		}
		for (asterisks = 1; asterisks <= i * 2 + 1; ++asterisks)
		{
			printf("*");
		}
		printf("\n");
	}
}
