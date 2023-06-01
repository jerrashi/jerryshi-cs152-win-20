#include <stdio.h>
#include <stdlib.h>
#include "checkers.h"

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
 *  * initializes the contents of the checkerboard.
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
 *    zero - piece successfully placed
 *    one - piece was not placed
 */
unsigned int place_piece(char board[NUM_ROWS][NUM_COLS], char player, 
			unsigned int row, unsigned int col)
{
        if ((player == 'b') || (player == 'B') || (player == 'W') || 
		(player == 'w'))
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

/* player_won
 * Checks to see if a player has won.
 * inputs:
 * 	char board - array of NUM_ROWS rows and NUM_COLS columns, represents
 * 			a checkerboard
 * 	char player - can be b or B to represent black, w or W to represent
 * 			white
 * outputs:
 * 	one - player has won
 * 	zero - player has not won
 */
int player_won(char board[NUM_ROWS][NUM_COLS], char player)
{
	char opponent, opponentking;
	if ((player == 'b') || (player == 'B'))
	{	
		opponent = 'w';
		opponentking = 'W';
	}
	else if ((player == 'w') || (player == 'W'))
	{
		opponent = 'b';
		opponentking = 'B';
	}
	else
		fprintf(stderr, "PLAYER_WON ERROR: player input not valid");
		return 0;

	int rowcount, colcount, opponentcount = 0;
	for (rowcount = 0; rowcount < NUM_ROWS; rowcount++)
	{
		for (colcount = 0; colcount < NUM_COLS; colcount++)
		{
			if ((board[rowcount][colcount] == opponentking) ||
				(board[rowcount][colcount] = opponent))
				opponentcount++;
		}
	}
	
	if (opponentcount == 0)
	{
		printf("PLAYER_WON MESSAGE: OPPONENT HAS NO PIECES");
		return 1;
	}

	unsigned int row, col;
	if (computer_move(board, opponent, &row, &col) == 0)
	{
		printf("PLAYER_WON MESSAGE: OPPONENT HAS NO VALID MOVES");
		return 1;
	}
	
	return 0;
}

/* do_move
 * Checks to see if a move is valid.
 * inputs:
 * 	player - piece to be moved (lowercase b for black, uppercase B for king
 * 		and same with w for white)
 * 	startrow - initial row of piece
 * 	startcol - initial column of piece
 * 	endrow - prospective column for piece to be moved to
 * 	endcol - prospective column for piece to be moved to
 * 	board - Two Dimensional array with NUM_ROWS rows and NUM_COLS columns
 * outputs:
 * 	u int one - piece successfully moved
 * 	u int two - piece successfully moved and jumped over another piece,
 * 			earning another move
 * 	u int zero - piece was not moved
 * 	board array is not outputted but changes to it in this function stay
 */
unsigned int do_move(char player, unsigned int startrow, unsigned int startcol, 
			unsigned int endrow, unsigned int endcol, 
			char board[NUM_ROWS][NUM_COLS])
{
	// basic validity checks
	if ((endrow >= NUM_ROWS) || (endcol >= NUM_COLS)) //spot not in bounds
		fprintf(stderr, "DO_MOVE ERROR: end location is not on board\n");
		
	if (board[endrow][endcol] != '*') // spot already occupied
	{	
		fprintf(stderr, "DO_MOVE ERROR: end location is already "
			"occupied\n");
		return 0;
	}

	if ((player != 'b') && (player != 'B') && (player != 'w') && 
		(player != 'W')) //verify player is valid input
	{
		fprintf(stderr, "DO_MOVE ERROR: please input valid player char");
		return 0;
	}

	if (player != board[startrow][startcol])
	{
		fprintf(stderr, "DO_MOVE ERROR: Player input does not match "
				"player in startrow, startcol position\n");
		return 0;
	}

	int iendrow = endrow, iendcol = endcol, istartrow = startrow, 
		istartcol = startcol;

	// player attempts to move up/down the board by one spot
	if ((abs(iendrow - istartrow) == 1) && (abs(iendcol - istartcol) == 1))
	{
		if ((player == 'b') && (endrow == startcol - 1))
		{	
			fprintf(stderr, "DO_MOVE ERROR: black piece can not "
				"move backward\n");
		}	
		else if ((player == 'w') && (endrow == startcol + 1))
		{
			fprintf(stderr, "DO_MOVE ERROR: white piece can not "
				"move forward\n");
		}
		else
		{
			board[endrow][endcol] = player;
			board[startrow][startcol] = '*';
			return 1;
		} 
	}	

	// player attempts to skip over another piece
	else if ((abs(iendcol - istartcol) == 2) && 
		(abs(iendcol - istartcol) == 2)) 
	{	
		if ((player == 'b') && (endrow == startcol - 2))
		{
			fprintf(stderr, "DO_MOVE ERROR: black piece can not "
			"move backward\n");
		}
		else if ((player == 'w') && (endrow == startcol + 2))
		{
			fprintf(stderr, "DO_MOVE ERROR: white piece can not "
			"move forward\n");
		}
		else
		{
			int midrow = (startrow + endrow) / 2;
			int midcol = (startcol + endcol) / 2;
			if (board[midrow][midcol] == '*')
			{
				fprintf(stderr, "DO_MOVE ERROR: no jumping "
					"over empty spot\n");
				return 0;
			}
			else if (((player == 'b')&&((board[midrow][midcol] ==
			 'b')||(board[midrow][midcol] == 'B'))) ||
			((player == 'w')&&((board[midrow][midcol] == 'w')||
			(board[midrow][midcol] == 'W'))))
			{
				fprintf(stderr, "DO_MOVE ERROR: non-king "
					"piece can not jump teammates\n");
				return 0;
			}
			else
			{
				board[midrow][midcol] = '*';
				board[startrow][startcol] = '*';
				board[endrow][endcol] = player;
				return 2;
			}
		}	
	}

	fprintf(stderr, "DO_MOVE ERROR: unidentified error occured\n");	
		
	return 0;
}


/* computer_move
 * Takes a board and player as input, performs first possible move, and records
 * the move.
 * inputs:
 * 	char board - array of NUM_ROWS rows and NUM_COLS columns that 
 * 			represents a checkerboard
 * 	char player - can be b or B (to represent black) or w or W (to 
 * 			represent white)
 * 	u int *row - location of an u int variable to store row of move
 * 	u int *col - location of an u int variable to store column of move
 * outputs:
 * 	zero - no move possible
 * 	one - move was performed
 * 	*row, *col, and board are not returned but any changes in function stay
 */
int computer_move(char board[NUM_ROWS][NUM_COLS], char player, 
		unsigned int *row, unsigned int *col)
{
	//verify player input
	if ((player != 'b') && (player != 'B') && (player != 'w') && 
		(player != 'W'))
	{
		fprintf(stderr, "COMPUTER_MOVE ERROR: player input not valid\n");
		return 0;
	}
	
	char piece;

	//iterate through entire board
	int rowcount, colcount;
	for (rowcount = 0; rowcount < NUM_ROWS; rowcount++)
	{
		for (colcount = 0; colcount < NUM_COLS; colcount++)
		{
			piece = board[rowcount][colcount];
			if (((player=='b') &&  ((piece=='b')||(piece=='B')))
				|| ((player=='w')&&(piece=='W')))
			// try to move down one spot normally or move down
			// two spots by jumping for black pieces or white kings
			{
				if ((colcount + 1 < NUM_COLS) && (rowcount + 1
					< NUM_ROWS))
				{
					if (do_move(piece, rowcount, colcount, 
						rowcount + 1, colcount + 1, 
						board) == 1)
					{
					*row = rowcount + 1;
					*col = colcount + 1;
					return 1;
					}
				}
				if (((int)colcount - 1 >= 0) && (rowcount + 1
					< NUM_ROWS))
				{
					if (do_move(piece, rowcount, colcount,
						rowcount + 1, colcount - 1, 
						board) == 1)
					{
						*row = rowcount + 1;
						*col = colcount - 1;
						return 1;
					}
				}
				if ((colcount + 2 < NUM_COLS) && (rowcount + 2
					< NUM_ROWS))
				{
					if (do_move(piece, rowcount, colcount, 
						rowcount + 2, colcount + 2, 
						board) == 2)
					{
						*row = rowcount + 2;
						*col = colcount + 2;
						return 1;
					}
				}
				if (((int)colcount - 2 >= 0) && (rowcount + 2
					< NUM_ROWS))
				{
					if (do_move(piece, rowcount, colcount, 
						rowcount + 2, colcount - 2, 
						board) == 2) 
					{
						*row = rowcount + 2;
						*col = colcount - 2;
						return 1;
					}
				}
			}

                        if (((player=='w') &&  ((piece=='w')||(piece=='W')))
                                || ((player=='b')&&(piece=='B')))
			// try to move up one spot normally or move down
			// two spots by jumping for white pieces or black kings
                        {
                                if ((colcount + 1 < NUM_COLS) && ((int)rowcount
					 - 1 >= 0))
                                {
                                        if (do_move(piece, rowcount, colcount,
                                                rowcount - 1, colcount + 1,
                                                board) == 1)
                                        {
                                        *row = rowcount - 1;
                                        *col = colcount + 1;
                                        return 1;
                                        }
                                }
                                if (((int)colcount - 1 >= 0) && ((int)rowcount
					 - 1 >= 0))
                                {
                                        if (do_move(piece, rowcount, colcount,
                                                rowcount - 1, colcount - 1,
                                                board) == 1)
                                        {
                                                *row = rowcount - 1;
                                                *col = colcount - 1;
                                                return 1;
                                        }
                                }
                                if ((colcount + 2 < NUM_COLS) && ((int)rowcount
					 - 2 >= 0))
                                {
                                        if (do_move(piece, rowcount, colcount,
                                                rowcount - 2, colcount + 2,
                                                board) == 2)
                                        {
                                                *row = rowcount - 2;
                                                *col = colcount + 2;
                                                return 1;
                                        }
                                }
                                if (((int)colcount - 2 >= 0) && ((int)rowcount
					 - 2 >= 0))
                                {
                                        if (do_move(piece, rowcount, colcount,
                                                rowcount - 2, colcount - 2,
                                                board) == 2)
                                        {
                                                *row = rowcount - 2;
                                                *col = colcount - 2;
                                                return 1;
                                        }
                                }
                        }
		}
	}
	fprintf(stderr, "COMPUTER_MOVE ERROR: no valid moves\n");
	return 0;
}

/* test_checkers
 * Tests previous functions.
 * inputs:
 * 	none
 * outputs:
 * 	none
 */
void test_checkers()
{
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
	
	// TESTING DO_MOVE
	printf("BEGINNING OF DO_MOVE TESTING\n");
	init_board(board);
	print_board(board);
	printf("---- BAD MOVE 1\n");
	do_move('b', 2, 1, 1, 1, board);
	printf("---- BAD MOVE 2\n");
        do_move('b', 2, 1, 3, 1, board);
	printf("--- BAD MOVE 3\n");
	do_move('b', 2, 1, 4, 3, board);
        printf("---- BAD MOVE 4\n");
        do_move('b', 12, 1, 1, 1, board);
        printf("---- BAD MOVE 5\n");
        do_move('b', 2, 1, 1, 3, board);

        printf("---- VALID MOVE 1\n");
        do_move('b', 2, 1, 3, 0, board);
        print_board(board);

        printf("---- VALID MOVE 2\n");
        do_move('b', 3, 0, 4, 1, board);
        print_board(board);

        printf("---- VALID MOVE 3\n");
        do_move('w', 5, 0, 3, 2, board);
        print_board(board);

        printf("---- VALID MOVE 4\n");
        do_move('b', 2, 3, 4, 1, board);
        print_board(board);
        printf("--------------------\n");


	// TESTING COMPUTER_MOVE AND PLAYER_WON
	printf("BEGINNING OF COMPUTER_MOVE TESTING\n");
	unsigned int cmtest, row, col;
	for (cmtest = 0; cmtest < 30; cmtest++)
	{
		printf("---- COMPUTER MOVE %d WHITE \n", cmtest);
		computer_move(board, 'w', &row, &col);
		print_board(board);
		player_won(board, 'w');
                printf("---- COMPUTER MOVE %d BLACK \n", cmtest);
                computer_move(board, 'b', &row, &col);
                print_board(board);
		player_won(board,'b');
	}
}


/* play_checkers
 * This function runs a game of checkers using previously written functions.
 * Inputs:
 *    none
 * Outputs:
 *    none
 */
void play_checkers()
{

	char board[8][8] = { {'*','*','*','*','*','*','*','*'},
                             {'*','*','*','*','*','*','*','*'},
                             {'*','*','*','*','*','*','*','*'},
                             {'*','*','*','*','*','*','*','*'},
                             {'*','*','*','*','*','*','*','*'},
                             {'*','*','*','*','*','*','*','*'},
                             {'*','*','*','*','*','*','*','*'},
                             {'*','*','*','*','*','*','*','*'}  };
        init_board(board);
	int winner = 0;
	char player_turn = 'B';
	while (winner == 0)
	{
		unsigned int sr, sc, er, ec;
		unsigned int response;
		
		// obtain the player's move
		do {
			printf("Player %c, in what row (0-7) is the piece you"
				" are moving located? ",player_turn);
			scanf("%u",&sr);
			if (sr >= NUM_ROWS)
				printf("That is not a valid row. Try again.\n");
		} while (sr >= NUM_ROWS);
		do {
			printf("Player %c, in what column (0-7) is the piece"
				" you are moving located? ",player_turn);
			scanf("%u",&sc);
			if (sc >= NUM_COLS)
				printf("That is not a valid column. Try again.\n");
		} while (sc >= NUM_COLS);
		do {
			printf("Player %c, to what row (0-7) do you want to"
				" move it? ",player_turn);
			scanf("%u",&er);
			if (er >= NUM_ROWS)
				printf("That is not a valid row. Try again.\n");
		} while (er >= NUM_ROWS);
		do {
			printf("Player %c, to what column (0-7) do you want to"
				" move it? ",player_turn);
			scanf("%u",&ec);
			if (ec >= NUM_COLS)
				printf("That is not a valid column. Try again.\n");
		} while (ec >= NUM_COLS);

		// attempt to do the move
		response = do_move(player_turn, sr, sc, er, ec, board);

                // invalid move
                if (response == 0)
                {
                        printf("That is not a valid move. Try again.\n");
                }       
                // valid move, switch to other player
                else if (response == 1)
                {
                        winner = player_won(board, player_turn);
                        if (winner == 0)
                        {
                                printf("Valid move. Next player's turn\n");
                                player_turn = (player_turn == 'B'?'W':'B');
                        }       
                        else
                                printf("Congratulations! Player %c won!\n",player_turn);
                }               
                // captured opponent's piece - gets another turn
                else // if (response == 2)
                {
                        winner = player_won(board, player_turn);
                        if (winner == 0)
                        {
				
				char again;
                                printf("You jumped your opponent!\n");
                                do { 
                                        printf("Would you like to move again?\n");
                                        printf("Enter y for yes or n for no: \n");
                                        scanf(" %c\n",&again);
                                        if (again == 'n')
                                        {                
                                                player_turn = (player_turn == 'B'?'W':'B');
                                        }       
                                        else if (again != 'y')
                                        {
                                                printf("Invalid response.\n");
                                        }       
                                } while (!((again == 'n') || (again == 'y')));
                        }       
                        else
                                printf("Congratulations! Player %c won!\n",player_turn);
                }   

	} // end of while no winner
}
