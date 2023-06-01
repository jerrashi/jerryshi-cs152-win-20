#ifndef CHECKERS_H
#define CHECKERS_H

#define NUM_ROWS 8
#define NUM_COLS 8

/* print_board
 * prints the contents of the checkerboard.
 * The pieces are 'b', 'w', the kinged ones
 * are 'B'and 'W', and empty spaces are '*'
 * inputs:
 *    char board[NUM_ROWS][NUM_COLS] - an NUM_ROWSxNUM_COLS board
 * outputs:
 *    none. prints the results.
 */
void print_board( char board[NUM_ROWS][NUM_COLS] );

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
void init_board(char board[NUM_ROWS][NUM_COLS]);

/* place_piece
 * Checkes to see if a given position is within board bounds and unoccupied.
 * If position is valid, piece is placed there.
 * inputs:
 *    char board - chess board with NUM_ROWS rows and NUM_COLS columns
 *    char player - player whose piece might be placed
 *    u int row - row of proposed position
 *    u int col - column of proposed position
 * outputs:
 *    one - piece successfully placed
 *    zero - piece was not placed
 */
unsigned int place_piece(char board[NUM_ROWS][NUM_COLS], char player, 
			unsigned int row, unsigned int col);

/* player_won
 * Checks to see if a player has won.
 * inputs:
 *      char board - array of NUM_ROWS rows and NUM_COLS columns, represents
 *                      a checkerboard
 *      char player - can be b or B to represent black, w or W to represent
 *                      white
 * outputs:
 *      one - player has won
 *      zero - player has not won
 */
int player_won(char board[NUM_ROWS][NUM_COLS], char player);

/* do_move
 * Checks to see if a move is valid.
 * inputs:
 *      player - piece to be moved (lowercase b for black, uppercase B for king
 *              and same with w for white)
 *      startrow - initial row of piece
 *      startcol - initial column of piece
 *      endrow - prospective column for piece to be moved to
 *      endcol - prospective column for piece to be moved to
 *      board - Two Dimensional array with NUM_ROWS rows and NUM_COLS columns
 * outputs:
 *      u int one - piece successfully moved
 *      u int two - piece successfully moved and jumped over another piece,
 *                      earning another move
 *      u int zero - piece was not moved
 *      board array is not outputted but changes to it in this function stay
 */
unsigned int do_move(char player, unsigned int startrow, unsigned int startcol, 
			unsigned int endrow, unsigned int endcol, 
			char board[NUM_ROWS][NUM_COLS]);
/* computer_move
 * Takes a board and player as input, performs first possible move, and records
 * the move.
 * inputs:
 *      char board - array of NUM_ROWS rows and NUM_COLS columns that
 *                      represents a checkerboard
 *      char player - can be b or B (to represent black) or w or W (to
 *                      represent white)
 *      u int *row - location of an u int variable to store row of move
 *      u int *col - location of an u int variable to store column of move
 * outputs:
 *      zero - no move possible
 *      one - move was performed
 *      *row, *col, and board are not returned but any changes in function stay
 */
int computer_move(char board[NUM_ROWS][NUM_COLS], char player, 
		unsigned int *row, unsigned int *col);
/* test_checkers
 * tests previous functions
 * inputs:
 * 	none
 * outputs:
 * 	none
 */
void test_checkers();
#endif
