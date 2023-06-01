#include <stdio.h>
#include <stdlib.h>
#include <math.h>

/* Jerry Shi, jerryshi */
/* CS152, Winter 2020 */
/* hw 1 */

/* convert_length: converts a length in centimeters to inches
 * inputs:
 *   double centimeters - length to be converted
 * outputs:
 *   double - previous length, now in inches
 */
double convert_length(double centimeters)
{
        if (centimeters < 0.0)
	{
		fprintf(stderr, "ERROR (convert_length): Only non-negative numbers "
			"are accepted. Return value set to -1. \n");
		return -1;
	}
	else
	{
		return centimeters * 0.3937;
	}
}

/* test_conv: tests convert_length function
 * inputs:
 *   double input - length to be converted
 *   double expected_output - expected value of length in inches
 * outputs:
 *   statement comparing expected output with output of convert_length
 */
void test_conv(double input, double expected_output)
{
	double output = convert_length(input);
	printf("convert_length(%lf) = %lf, expected %lf \n", input, output, 
		expected_output);
}

/* trapezoid_area: computes the internal area of a given trapezoid
 * inputs:
 *   int height - height of trapezoid
 *   int base1 - length of one base of trapezoid
 *   int base2 - length of other base of trapezoid
 * outputs:
 *   double - internal area of given trapezoid
 */
double trapezoid_area(unsigned int height, unsigned int base1, unsigned int base2)
{
	if ((height == 0) || (base1 == 0) || (base2 == 0))
	{
		fprintf(stderr, "ERROR (trapezoid_area): Only non-zero numbers are "
			"accepted. Return value set to 0. \n");
		return 0;
	}
	else
	{
		double totalbase = base1 + base2;
		double avgbase = totalbase/2.0;
		return avgbase * height;
	}
}

/* test_trap: tests trapezoid_area function
 * inputs:
 *   int height - height of trapezoid
 *   int base1 - length of one base of trapezoid
 *   int base2 - length of other base of trapezoid
 *   double expected_output - expected area of given trapezoid
 * outputs:
 *   prints statement comparing expected output with output of trapezoid_area
 */
void test_trap(unsigned int height, unsigned int base1, unsigned int base2, 
		double expected_output)
{
	double output = trapezoid_area(height, base1, base2);
	printf("trapezoid_area(%d, %d, %d) = %lf, expected %lf \n", height, \
		base1, base2, output, expected_output);
}

/* print_number_triangle: prints a Pascals Triangle utilizing the inputted integer
 * inputs:
 *   int start_num - number to be used to generate Pascals Triangle
 * outputs:
 *   prints Pascals Triangle generated using start_num
 */
void print_number_triangle(unsigned int start_num)
{
	int sum1 = start_num + start_num;
	int sum2 = sum1 + start_num;
	int sum3 = sum2 + start_num;
	int sum4 = sum2 + sum2;
	
	/* digit checking code modelled after
	   https://codeforwin.org/2016/10/c-program-to-count-number-of-digits-in-number.html */
	if (log10(start_num) + 1 > 3)
	{
		printf("ERROR (print_number_triangle): Numbers larger than 3 digits"
			" not supported");
	}
	
	else
	{
		printf("number triangle: %d\n", start_num);
		printf("				%3d\r\n", start_num);
		printf("			%3d		%3d\r\n", start_num, start_num);
		printf("		%3d		%3d		%3d\r\n", start_num, sum1, start_num);
		printf("	%3d		%3d		%3d		%3d\r\n", start_num, sum2, sum2, start_num);
		printf("%3d		%3d		%3d		%3d		%3d\r\n", start_num, sum3, sum4, sum3, start_num);

	}
}

int main()
{
	// testing functions
	printf("TESTING CONVERT_LENGTH FUNCTION:\n");
	test_conv(-100, -1);
	test_conv(0, 0);
	test_conv(0.5, 0.19685);
	test_conv(10, 3.937);
	test_conv(20, 7.874);
	printf("TESTING TRAPEZOID_AREA FUNCTION:\n");
	test_trap(0, 1, 2, 0);
	test_trap(1, 0, 0, 0);
	test_trap(0, 0, 0, 0);
	test_trap(2, 3, 5, 8);
	test_trap(17, 15, 20, 297.5);
	test_trap(23, 20, 23, 494.5);
	test_trap(50, 75, 125, 5000);
	printf("TESTING PRINT_NUMBER_TRIANGLE FUNCTION:\n");
	print_number_triangle(1);
	print_number_triangle(5);
	print_number_triangle(20);
	print_number_triangle(100);
	printf("--------------------END OF TESTING--------------------\n");	

	// declaration of variables
	double centimeters, inches, area;
	int height, base1, base2, init;	

	// CONVERT LENGTH
	// print out user information
	printf("This program converts centimeters to inches.\n");
	
	// get user input
	printf("Enter a measurement in centimeters >");
	scanf("%lf",&centimeters);
	
	// calculate the measurement in inches
	inches = convert_length(centimeters);
	
	// output the result
	printf("%lf cm == %lf in\n", centimeters, inches);


	// TRAPEZOID AREA
	// print out user information
	printf("This program calculates the area of a trapezoid.\n");
	
	// get user input
	printf("Enter the height of the trapezoid >");
	scanf("%d",&height);
	printf("Enter the length of one base of the trapezoid >");
	scanf("%d",&base1);
	printf("Enter the length of the other base of the trapezoid >");
	scanf("%d",&base2);

	// calculate the area
	area = trapezoid_area(height, base1, base2);
	
	// output the result
	printf("This trapezoid with height of %d and bases %d and %d has "
		"an area of %lf\n", height, base1, base2, area);
	

	// PASCALS TRIANGLE
	// print out user information
	printf("This program generates a five row Pascal's Triangle using "
		"the number given.\n");
	
	// get user input
	printf("Enter an integer to generate a triangle with >");
	scanf("%d",&init);
	
	// print Pascals Triangle
	print_number_triangle(init);


	// return success
	return (0);
}
