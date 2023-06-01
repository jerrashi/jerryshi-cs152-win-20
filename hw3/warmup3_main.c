#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "warmup3.h"

int main()
{	
	#ifndef DEBUG
	printf("---------------DEBUG MODE TURNED ON---------------/n");
	// TESTING REMOVE_MAX
	printf("BEGINNING OF REMOVE_MAX TESTING\n");

	int test1length = rand() % 20;
	int test1[test1length];
	for (int count =0; count < test1length; count++) // increasing value array
		test1[count] = count + 1;
	remove_max(test1, test1length);
	
	int test2[4];
	test2[0] = 5;
	test2[1] = 3;
	test2[2] = 4;
	test2[3] = 1;
	remove_max(test2, 4);	
	
	int test3length = rand() % 20;
	int test3[test3length];
	for (int count = 0; count < test3length; count++) // random array
		test3[count] = rand() % 20;
	remove_max(test3, test3length);
        printf("--------------------\n");

	// TESTING INIT_BOARD
	printf("BEGINNING OF INIT_BOARD TESTING\n");
	char board[NUM_ROWS][NUM_COLS];
	init_board(board); 	
	print_board(board);
	printf("--------------------\n");
	
	// TESTING PLACE_PIECE
	printf("BEGINNING OF PLACE_BOARD TESTING\n");
	place_piece(board, 'b', 3, 0);
	print_board(board);
	place_piece(board, 'w', 4, 5);
	print_board(board);
	place_piece(board, 'b', 7, 1);
	print_board(board);
	
	place_piece(board, 'x', 5, 3);
	print_board(board);
	place_piece(board, 'w', 5, 20);
	print_board(board);
	place_piece(board, 'w', 20, 15);
	print_board(board);
	printf("--------------------\n");
	
	// TESTING AREA_AND_PERIMETER
	printf("BEGINNING OF AREA_AND_PERIMETER TESTING\n");
	double area, perimeter;
	
	double height = 20, length = 15;
	area_and_perimeter(height, length, &area, &perimeter);
	printf("Rectangle with a height of %f and length of %f\n", height, length);
	printf("---Output: Area is %f and perimeter is %f\n", area, perimeter);

	height = 5;
	length = 2;
        area_and_perimeter(height, length, &area, &perimeter);
        printf("Rectangle with a height of %f and length of %f\n", height, length);
        printf("---Output: Area is %f and perimeter is %f\n", area, perimeter);

	height = rand() % 20;
	length = rand() % 20;
        area_and_perimeter(height, length, &area, &perimeter);
        printf("Rectangle with a height of %f and length of %f\n", height, length);
        printf("---Output: Area is %f and perimeter is %f\n", area, perimeter);

        // TESTING REMOVE_MAX_IN_OUT
        printf("BEGINNING OF REMOVE_MAX TESTING\n");

        unsigned int iotest1length = rand() % 20;
        int iotest1[iotest1length];
        for (int count =0; count < iotest1length; count++) // ordered array
                test1[count] = count + 1;
        remove_max_in_out(iotest1, &iotest1length);

        int iotest2[4];
	unsigned int iotest2length = 4;
        iotest2[0] = 5;
        iotest2[1] = 3;
        iotest2[2] = 4;
        iotest2[3] = 1;
        remove_max_in_out(iotest2, &iotest2length);

        unsigned int iotest3length = rand() % 20;
        int iotest3[iotest3length];
        for (int count = 0; count < iotest3length; count++) // random array
                iotest3[count] = rand() % 20;
        remove_max_in_out(iotest3, &iotest3length);
        printf("--------------------\n");
	
	#endif
	
	return 0;
}  
