#ifndef WARMUP5_H
#define WARMUP5_H

/* safe_str_concat
 * Allocates a brand new string that will hold both str1 and str2. Then copies
 * both strings over, str1 at the front and str2 at the back. Returns a
 * pointer to that new string.
 * inputs:
 *      str1 - string
 *      str2 - string
 * outputs:
 *      pointer to new string of str1+str2
 */
char *safe_str_concat(char *str1, char *str2);


typedef struct {
	unsigned int allocated_size;
	int *array;
} int_vector;

/* make_init_array
 * Creates an object of data type int_vector
 * inputs:
 *      none
 * outputs:
 *      int_vector * - pointer to location of int_vector
 */
int_vector* make_init_array();

/* write_value
 * Takes input value and tries to insert it into the int_vector referenced
 * at position index. If index surpasses the size of int_vector array, a new
 * array is created and existing data is copied over before the value is
 * inserted.
 * intputs:
 * 	vector - pointer to int_vector to be changed
 * 	index - position for value to be inserted
 * 	value - value to be inserted
 * outputs:
 * 	none
 */
void write_value(int_vector *vector, unsigned int index, int value);

/* read_value
 * Returns value at position index of array of int_vector. If index is
 * greater than array size, return value is zero.
 * inputs:
 *      vector - int_vector to be read from
 *      index - position to be read from
 * returns:
 *      int - value at position in array of int_vector
 */
int read_value(int_vector *vector, unsigned int index);

#endif
