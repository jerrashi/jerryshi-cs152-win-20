#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "warmup2.h"  // note this new include file!!!


/* Principle 2: Design a good set of test cases
 * they check the base case (0), right above the base case (1), well
 * above the base case (5, 8), and error conditions (-1, -5).
 * -1, 0, 1 are the boundary test cases - base, base+1, base-1.
 */
int main()
{


	print_asterisk_letter('S');
	print_asterisk_letter('T');
	print_asterisk_letter('U');
	print_asterisk_letter('V');
	print_asterisk_letter('s');
	print_asterisk_letter('t');
	print_asterisk_letter('u');
	print_asterisk_letter('v');
	print_asterisk_letter('A');
	print_asterisk_letter(20);
	print_asterisk_letter(-100);
	
	//draw_hourglass_rec(10);
	//draw_hourglass_rec(0);
	//draw_hourglass_rec(-20);

	draw_hourglass_iter(10);
	draw_hourglass_iter(0);
	draw_hourglass_iter(-20);
	
	return 0;
}
