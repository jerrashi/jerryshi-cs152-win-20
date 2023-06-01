#include <stdio.h>
#include <stdlib.h>
#include "mastermind.h"

/* num_of_digits
 * This helper function finds the number of digits in a given integer.
 * inputs:
 *    int pattern - integer to be counted
 * outputs:
 *    int count - number of digits in integer
 */
unsigned int num_of_digits(unsigned int pattern)
{
	int n = pattern, rv = 0;
	while (n!=0)
	{
		n = n/10;
		++rv;
	}
		return rv;
}

/* extract_digit
 * This function finds the number in the given position (digit) of a given integer
 * (pattern).
 * inputs:
 *    int pattern - integer from which digit is to be extracted
 *    int digit - the position of the integer from which the number is to be extracted
 */
unsigned int extract_digit(unsigned int pattern, unsigned int digit)
{
	int n = pattern, num_digits = num_of_digits(pattern), rv = 0;
	
	if ((digit > num_digits) || (digit <= 0))
	{
		fprintf(stderr, "ERROR (extract_digit): digit position must be in pattern");
		return -1;
	}	
	
	n = pattern;
	for (int i = 0; i <= num_digits - digit; ++i)
	{
		rv = n%10;
		n = n/10;
	}

	printf("%d", rv);	
	return rv;
}

/* num_of_color
 * This function finds the number of instances of the color (expressed as an int)
 * given in a given pattern.
 * inputs:
 *    u int pattern - integer where color will be counted
 *    u int color - color, represented as integer
 * output:
 *   int - count of color in pattern
 */
unsigned int num_of_color(unsigned int pattern, unsigned int color)
{
	int r = 0, rv = 0, n = pattern;
	while (n != 0)	
	{
		r = n%10;
		if (r == color)
		{
			++rv;	
		}
		n = n/10;
	}
		
	return rv;
}

/* count_exact_matches
 * This function finds the number of instances of exact matches (position and color) between
 * user provided guess and pattern.
 * inputs:
 *    u int guess - user provided guess for what pattern is
 *    u int solution - pattern; user does not know this
 * outputs:
 *   int - count of exact matches
 */
unsigned int count_exact_matches(unsigned int guess, unsigned int solution)
{
	int n = solution, g = guess, rv = 0;
	while (n != 0)
	{
		if (n%10 == g%10)
		{
			++rv;
		}
		n = n/10;
		g = g/10;

	}
	return rv;
}

/* count_color_matches
 * This function counts the number of matches by color between guess & pattern.
 * inputs:
 *   u int guess - user provided guess as to what pattern is
 *   u int solution - pattern; user does not know this is
 * outputs:
 *   int - number of color matches between the two
 */
unsigned int count_color_matches(unsigned int guess, unsigned int solution)
{
	int rv = 0, n = solution, g = guess, n_count = 0, g_count = 0;
	for (int i = 0; i <= 6; ++i)
	{
		n_count = num_of_color(n, i);
		g_count = num_of_color(g, i);
		if (n_count >= g_count)
			rv = rv + g_count;
		else
			rv = rv + n_count;
	} 
		
	return rv;
}

/* get_guess_feedback
 * This function counts the number of matches that are exact and in color only.
 * inputs:
 *    u int guess - user provided guess as to what pattern in
 *    u int solution - pattern; user does not know what this is
 * outputs:
 *    int - guess feedback; first digit is the number of exact matches, second digit is
 *    	    color only matches
 */
unsigned int get_guess_feedback(unsigned int guess, unsigned int solution)
{
	int n_exact = count_exact_matches(guess, solution);
	int n_color = count_color_matches(guess, solution);
	int n_color_only = n_color - n_exact;
	if (n_color_only < 0)
		n_color_only = 0;
	int rv = (n_exact * 10) + n_color_only;
	
	return rv;
}


/* test_mastermind
 * This is the test function that has 3+ good test cases for each function in your
 * mastermind program. This verifies that the bits are working so that if you find a
 * bug you can more easily localize it.
 * inputs:
 *   none. Tests are hard coded.
 * outputs:
 *   none. Test results are printed out.
 */
void test_mastermind()
{
	printf("-------------TESTING-------------\n");

	printf("----------extract_digit----------\n");
	int output = 0;
	output = extract_digit(3413, 2);
	printf("extract_digit(3413, 2) = %d, EXPECTED = 2\n", output);
	output = extract_digit(5615, 4);
	printf("extract_digit(5615, 4) = %d, EXPECTED = 5\n", output);
	output = extract_digit(5650, 6);
	printf("extra_digit(5650, 6) = %d; EXPECTED = -1\n", output);

	printf("-----------num_of_color-----------\n");
	output = num_of_color(3413, 1);
	printf("num_of_color(3413, 1) = %d, EXPECTED = 1\n", output);
	output = num_of_color(3413, 2);
	printf("num_of_color(3413, 2) = %d, EXPECTED = 0\n", output);
	output = num_of_color(3413, 3);
	printf("num_of_color(3413, 3) = %d, EXPECTED = 2\n", output);
	output = num_of_color(3413, 4);
	printf("num_of_color(3413, 4) = %d, EXPECTED = 1\n", output);	

	printf("--------count_exact_matches--------\n");
	output = count_exact_matches(3413, 2315);
	printf("count_exact_matches(3413, 2315) = %d, EXPECTED = 1\n", output);
	output = count_exact_matches(3413, 1234);
	printf("count_exact_matches(3413, 1234) = %d, EXPECTED = 0\n", output);	
	output = count_exact_matches(3413, 3003);
	printf("count_exact_matches(3413, 3003) = %d, EXPECTED = 2\n", output);

	printf("--------count_color_matches--------\n");
	output = count_color_matches(3413, 2315);
	printf("count_color_matches(3413, 2315) = %d, EXPECTED = 2\n", output);
	output = count_color_matches(3413, 4562);
	printf("count_color_matches(3413, 4562) = %d, EXPECTED = 1\n", output);
	output = count_color_matches(3413, 1113);
	printf("count_color_matches(3413, 1113) = %d, EXPECTED = 2\n", output);

        printf("---------get_guess_feedback-------\n");
	output = get_guess_feedback(3413, 2315);
	printf("get_guess_feedback(3413, 2315) = %d, EXPECTED = 11\n", output);
	output = get_guess_feedback(3413, 3123);
	printf("get_guess_feedback(3413, 3123) = %d, EXPECTED = 21\n", output);
        output = get_guess_feedback(3413, 1234);
        printf("get_guess_feedback(3413, 1234) = %d, EXPECTED = 03\n", output);

}

/* print_mastermind_instructions
 * This prints out user instructions to play mastermind.
 * inputs:
 *   none
 * outputs:
 *   none. Insructions are printed to screen.
 */
void print_mastermind_instructions()
{
	printf("Welcome to mastermind. I am thinking of a 4-number\n");
	printf("sequence. All four numbers are between 1 and 6.\n");
	printf("You have 12 guesses to guess it correctly.\n");
	printf("Each time you guess, I'll tell two things.\n");
	printf("1. How many numbers are correct and in the correct position.\n");
	printf("2. How many other numbers are correct but in the wrong position.\n");
	printf("Let's get started!!!\n");
}

/* get_new_code
 * Generates a 4-digit number, with each digit a number from 1 to 6, inclusive.
 * inputs:
 *   none
 * outputs:
 *   unsigned int - 4-digit number with each digit from 1 to 6
 */
unsigned int get_new_code()
{
	int i;
	int result = 0;
	for (i = 0; i < 4; i++)
	{
		result = result * 10;
		result = result + ((rand() % 6) + 1);
	}
	return result;
}


/* play_mastermind
 * This is the game loop to play mastermind. All print statements are provided so that you 
 * have consistent messages for grading purposes. An example of how to do error checking is 
 * provided so you can model that.
 * inputs:
 *  none. Users play interactively
 * outputs:
 *  none. Everything is printed.
 */
void play_mastermind()
{

	unsigned int guess_num = 0;
	unsigned int solution = 0;
	unsigned int guess = 0;
	unsigned int feedback = 0;
	unsigned int guess_incorrect = 0;

	print_mastermind_instructions();
	solution = get_new_code();
	// print so that we can tell whether yours matches ours. Don't remove
	printf("solution: %u\n", solution);

	for (guess_num = 0; guess_num < 12; ++guess_num)
	{
		// get guess from user and verify that it is valid
		do
		{
			guess_incorrect = 0;
			printf("---Guess %d - ",guess_num);
			printf("Input your 4-digit guess: ");
			scanf("%u",&guess);
			
			int n = guess;
			while (n != 0)
			{
				int r = n%10;
				if ((r < 1) || (r >6) || 
					(num_of_digits(guess) != 4))
				{
					printf("%u is an invalid guess. Make "
						"sure your guess is 4-digits, "
						"each digit between 1-6.\n",
						guess);
					guess_incorrect = 1;
					break;
				}
				n = n/10;
			}
		} while(guess_incorrect == 1);

		feedback = get_guess_feedback(guess, solution);
		
		// report feedback to user
		printf("FEEDBACK:\n");
		printf("%u correct placement, correct color,\n",
			feedback / 10);
		printf("%u incorrect placement, correct color\n",
			feedback % 10);
	
		// user guessed correctly
		if (feedback / 10 == 4)
		{
			printf("Congratulations! Your guess of %u was correct!"
				"\n", guess);
			return;
		}
		else
		{
			printf("Not quite - you still have %u guesses left!\n",
				11 - guess_num);
		}
	}

	// only print this out if they ran out of guesses didn't win.
	printf("Sorry, you did not guess it! The solution was %u\n",solution);
}

