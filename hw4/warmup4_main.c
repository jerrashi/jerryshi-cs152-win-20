#include <stdio.h>
#include <stdlib.h>
#include "hw4_provided.h"
#include "warmup4.h"

int main()
{
	// declare variables
	unsigned int r[ROWS][COLS];
        unsigned int g[ROWS][COLS];
        unsigned int b[ROWS][COLS];

        char str1[] = {'H','o','w','d','y',' ','T','H','E','R','E','!','\0'};
        char str2[] = {'H', 'i', 'g', 'h', ' ', 'R', 'O', 'A', 'D', '\0'};
        char str3[] = {'T', 'o', 'n', 'i', 'g', 'h', 't', '\0'};

        // function test calls
        printf("BEGINNING OF COUNT_VOWELS AND MAKE_LOWERCASE TESTING ----------\n");
        printf("String 1: %s \n", str1);
        printf("----- vowel count: %d \n", count_vowels(&str1[0]));
        make_lowercase(&str1[0]);
        printf("----- after transformation:  %s \n", str1);

        printf("String 2: %s \n", str2);
	printf("----- vowel count: %d \n", count_vowels(&str2[0]));
        make_lowercase(&str2[0]);
        printf("----- after transformation: %s \n", str2);

        printf("String 3: %s \n", str3);
        printf("\n----- vowel count: %d \n", count_vowels(&str3[0]));
        make_lowercase(&str3[0]);
        printf("----- after transformation: %s \n", str3);
/*
	// read in ppm file
	// note that r, g, b, width, length are all out parameters
	// that means we need to declare the variables here and send
	// the locations to the function, as seen below.

	// note that for the warmup, you do not need to read in a png.
	provided_read_png("sample.png",r,g,b,&width,&length);
*/


	// put in arrays
	make_horizontal_stripes(r, g, b, 1, 30, 144, 255, ROWS, COLS);
	// print to html to view
	provided_print_image_to_html("my_horiz_stripes.html",r,g,b,ROWS,COLS);

        // put in arrays
        make_horizontal_stripes(r, g, b, 10, 30, 144, 255, ROWS, COLS);
        // print to html to view
        provided_print_image_to_html("my_horiz_stripes_10.html",r,g,b,ROWS,COLS);


	// put in arrays
	make_checker_board(r, g, b, 5, 30, 144, 255, ROWS, COLS);
	// print to html to view
	provided_print_image_to_html("my_checkboard.html", r, g, b, ROWS, COLS);
        // put in arrays
        make_checker_board(r, g, b, 0, 30, 144, 255, ROWS, COLS);
        // print to html to view
        provided_print_image_to_html("my_checkboard_blank.html", r, g, b, ROWS, COLS);

}
