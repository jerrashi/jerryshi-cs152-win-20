#ifndef WARMUP3_H
#define WARMUP3_H

#define NUM_ROWS 8
#define NUM_COLS 8

void print_board( char board[NUM_ROWS][NUM_COLS] );

int remove_max( int array[], unsigned int length );

void init_board( char board[NUM_ROWS][NUM_COLS] );

unsigned int place_piece(char board[NUM_ROWS][NUM_COLS], char player, 
			unsigned int row, unsigned int col);

void area_and_perimeter(double height, double length, double *area, 
			double *perimeter);

int remove_max_in_out(int array[], unsigned int *length);

#endif

