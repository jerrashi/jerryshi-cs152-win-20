#include <stdio.h>
#include <stdlib.h>
#include "warmup4.h"
#include "hw4_provided.h"

/* count_vowels
 * search through str and count the number of vowels.
 * input: char *str - a string
 * output: int - the number of vowels in the string str
 */
int count_vowels(char *str)
{
        int count = 0;
        while(*str != '\0')
        {
                if ((*str=='a') || (*str=='e') || (*str=='i') || (*str=='o')
		 || (*str=='u') || (*str=='A') || (*str=='E') || (*str=='I')
		 || (*str=='O') || (*str=='U'))
                        count++;
		str++;
        }
        return count;
}

/* make_lowercase
 * modify str such that all alphabetic characters are lower case
 * input: char *str - a string
 * output: no return value - str is out parameter
 */
void make_lowercase(char *str)
{
        int diff = 'A' - 'a';
        while(*str != '\0')
        {
                if ((*str >= 'A') && (*str <= 'Z'))
                        *str = (char)(((unsigned int)*str) - diff);
                str++;
        }
}

/* make_horizonta_stripes
 *   This produces an image stored in the red, green, and blue 2-d arrays.
 *   The image contains black and colored stripes. All stripes are 
 *   stripe_height. The stripe colors are indicated by stripe_color.
 *   The top stripe is colored. The image is heightxwidth.
 * inputs: 
 *   unsigned int red[ROWS][COLS],  - red component of resulting image pixels
 *   unsigned int green[ROWS][COLS], - green component of resulting image pixels
 *   unsigned int blue[ROWS][COLS],  - blue component of resulting image pixels
 *   unsigned int stripe_height,  - height of a single stripe
 *   unsigned int stripe_red,  - red component of stripe pixel
 *   unsigned int stripe_green,  - green component of stripe pixel
 *   unsigned int stripe_blue,  - blue component of stripe pixel
 *   unsigned int width,  - width of resulting image
 *   unsigned int height); - height of resulting image
 * 
 */
void make_horizontal_stripes( 
	unsigned int red[ROWS][COLS], 
	unsigned int green[ROWS][COLS], 
	unsigned int blue[ROWS][COLS], 
	unsigned int stripe_height, 
	unsigned int stripe_red, 
	unsigned int stripe_green, 
	unsigned int stripe_blue, 
	unsigned int width, 
	unsigned int height)
{
	int col = 0, row = 0, count;

	if ((width > COLS) || (height > ROWS)) //error checking
	{
		fprintf(stderr, "MAKE_HORIZONTAL_STRIPES ERROR: height or "
				"width value(s) larger than rgb arrays.");
		return;
	}

	if (stripe_height == 0) // return completely black picture
	{
		for (row = 0; row < height; row++)
		{
			for (col = 0; col < width; col++)
			{
				red[row][col] = 0;
				green[row][col] = 0;
                                blue[row][col] = 0;
			}
		}
		return;
	}


	while (row < height) // iterating through all rows
	{
		//first make a colored stripe
		for(count = 0; count < stripe_height; count++)
		{
			for(col = 0; col < width; col++)
			{
				red[count + row][col] = stripe_red;
				green[count + row][col] = stripe_green;
				blue[count + row][col] = stripe_blue;
			}
                }
		//update row counter
		row += stripe_height;
		//now make a black stripe
                for(count = 0; count < stripe_height; count++)
                {
                        for(col = 0; col < width; col++)
                        {
                                red[count + row][col] = 0;
                                green[count + row][col] = 0;
                                blue[count + row][col] = 0;
                        }
                }
		//update row counter
		row += stripe_height;
	}
}

/* make_checker_board
 *   This produces an image stored in the red, green, and blue 2-d arrays.
 *   The image contains white and colored squares. All squares are 
 *   square_width x square_width. The square colors are indicated by 
 *   square_color. The image is heightxwidth. The top-left square is colored.
 * inputs: 
 *   unsigned int red[ROWS][COLS],  - red component of resulting image pixels
 *   unsigned int green[ROWS][COLS], - green component of resulting image pixels
 *   unsigned int blue[ROWS][COLS],  - blue component of resulting image pixels
 *   unsigned int square_height,  - height of a single square
 *   unsigned int square_red,  - red component of square pixel
 *   unsigned int square_green,  - green component of square pixel
 *   unsigned int square_blue,  - blue component of square pixel
 *   unsigned int width,  - width of resulting image
 *   unsigned int height); - height of resulting image
 * 
 */
void make_checker_board( 
        unsigned int red[ROWS][COLS],
        unsigned int green[ROWS][COLS],
        unsigned int blue[ROWS][COLS],
        unsigned int square_width,
        unsigned int square_red,
        unsigned int square_green,
        unsigned int square_blue,
        unsigned int width,
        unsigned int height)
{
        unsigned int row, col;
	int alternating = -1;

        if ((width > COLS) || (height > ROWS)) //error checking
        {
                fprintf(stderr, "MAKE_CHECKERBOARD ERROR: height or width "
				"value(s) bigger than rgb arrays.");
                return;
        }

        if (square_width == 0) // return white board
        {
                for (row = 0; row < height; row++)
                {
                        for (col = 0; col < width; col++)
                        {
                                red[row][col] = 255;
                                green[row][col] = 255;
                                blue[row][col] = 255;
                        }
                }
                return;
        }


	printf("%d", height);

        for (row = 0; row < height; row++) // iterating through all rows
        {
		printf("\nrow: %d", row);

		if (row%square_width == 0) // alternating alternates pattern
		{
			alternating *= -1;
		}

		for (col = 0; col < width; col++) // iterating through columns
		{
			//board alternates color every other column
			if ((col/square_width) % 2 == 0)
			{
				//and also alternates color every other row
				if (alternating == 1)
				{
					red[row][col] = square_red;
        	                       	green[row][col] = square_green;
                	                blue[row][col] = square_blue;
					printf(" * ");
				}
			
				else
				{
					red[row][col] = 255;
					green[row][col] = 255;
					blue[row][col] = 255;
					printf("   ");
				}
			}

			//board alternates color every other column
			else
			{
				//and also alternates color every other column
				if (alternating == 1)
				{
					red[row][col] = 255;
					green[row][col] = 255;
					blue[row][col] = 255;
					printf("   ");
				}
				
				else
				{
					red[row][col] = square_red;
					green[row][col] = square_green;
					blue[row][col] = square_blue;
					printf(" * ");
				}
			}
		}
        }
}
