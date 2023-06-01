#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <png.h>
#include "warmup5.h"
#include "warmup5_provided.h"

/* safe_str_concat
 * Allocates a brand new string that will hold both str1 and str2. Then copies 
 * both strings over, str1 at the front and str2 at the back. Returns a 
 * pointer to that new string.
 * inputs:
 * 	str1 - string
 * 	str2 - string
 * outputs:
 * 	pointer to new string of str1+str2
 */
char *safe_str_concat(char *str1, char *str2)
{
	int str1_length = (int)strlen(str1);
	int str2_length = (int)strlen(str2);
	int count, str3_length = str1_length + str2_length;

	char *str3 = malloc(sizeof(char[str3_length]));

	for(count = 0; count < str1_length; count++)
	{
		str3[count] = str1[count];
	}

	for(count = str1_length; count < str3_length; count++)
	{
		str3[count] = str2[count - str1_length];
	}

	str3[str3_length] = '\0'; 

	return str3;
}

/* make_init_array
 * Creates an object of data type int_vector
 * inputs:
 * 	none
 * outputs:
 * 	int_vector * - pointer to location of int_vector
 */
int_vector * make_init_array()
{
	int_vector * iv = (int_vector *)malloc(sizeof(int(int_vector)));
	iv->allocated_size = 0;
	iv->array = NULL;
	return iv;
}

/* write_value
 * Takes input value and tries to insert it into the int_vector referenced
 * at position index. If index surpasses the size of int_vector array, a new
 * array is created and existing data is copied over before the value is
 * inserted.
 * intputs:
 *      vector - pointer to int_vector to be changed
 *      index - position for value to be inserted
 *      value - value to be inserted
 * outputs:
 *      none
 */
void write_value(int_vector *vector, unsigned int index, int value)
{
	if (index >= vector->allocated_size) //index > existing array size
	{
		int i, new_size;
		if ((index+1 <= 16) && ((vector->allocated_size) * 2 <= 16))
			new_size = 16;
		else if (index + 1 > (vector->allocated_size) * 2)
			new_size = index + 1;
		else
			new_size = (vector->allocated_size) * 2;
		
		int * new_array;
		new_array = (int *)malloc(sizeof(int[new_size]));
		if (vector->allocated_size > 0) //copy over existing array
		{
			for (i = 0; i < vector->allocated_size; i++)
			{
				new_array[i] = vector->array[i];
			}
		}
		new_array[index] = value;
		free(vector->array);
		vector->array = new_array;
		vector->allocated_size = new_size;
	}

	else
	{
		vector->array[index] = value;
	}
}

/* read_value
 * Returns value at position index of array of int_vector. If index is
 * greater than array size, return value is zero.
 * inputs:
 * 	vector - int_vector to be read from
 * 	index - position to be read from
 * returns:
 * 	int - value at position in array of int_vector
 */
int read_value(int_vector *vector, unsigned int index)
{
	if (index >= vector->allocated_size)
		return 0;
	else
		return vector->array[index];
}

// ADD FUNCTION HEADER
pixel** make_and_init_image(int height, int width, pixel color)
{
	pixel** pic;
	pic = (pixel**)malloc(sizeof(pixel*)*height);
	int i, j;
	for(i=0; i<height; i++)
	{
		pic[i] = (pixel*)malloc(sizeof(pixel)*width);
		for (j = 0; j<width; j++)
		{
			pic[i][j].red = color.red;
			pic[i][j].green = color.green;
			pic[i][j].blue = color.blue;
		}
	}
	return pic;
}
