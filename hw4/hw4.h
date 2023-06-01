#ifndef HW4_H
#define HW4_H

#define ROWS 50
#define COLS 50

/* hide_image
 * Takes three sets of three arrays as input. Each set represents an image
 * to be hidden, a reference image, and the result of hiding the latter in the
 * former, respectively. Each array represents red, green, and blue values,
 * respectively. Hiding process is very simple: if hidden image value is
 * greater than 128, then resulting image must be even.
 * inputs:
 *      ref_r, ref_g, ref_b - arrays representing reference image
 *      hid_r, hid_g, hid_b - arrays representing hidden image
 *      res_r, res_g, res_b - arrays representing "output" resulting image
 * outputs:
 *      none, but res_r, res_g, and res_b arrays are populated with values
 */
void hide_image(
	unsigned int ref_r[ROWS][COLS], 
	unsigned int ref_g[ROWS][COLS], 
	unsigned int ref_b[ROWS][COLS], 
	unsigned int hid_r[ROWS][COLS], 
	unsigned int hid_g[ROWS][COLS], 
	unsigned int hid_b[ROWS][COLS], 
	unsigned int res_r[ROWS][COLS], 
	unsigned int res_g[ROWS][COLS], 
	unsigned int res_b[ROWS][COLS], 
	unsigned int height, unsigned int width);

/* extract_image
 * Takes a set of three arrays as input. Each array represents the reg, blue,
 * green values of a pixel in the input image. The extraction rules are very
 * simple: if the corresponding pixel value in the input image is even, the
 * pixel in hidden image will be at full value. If the value is odd, the pixel
 * will be at empty value.
 * inputs:
 *      ref_r, ref_g, ref_b - arrays representing reference image
 *      hid_r, hid_g, hid_b - arrays representing hidden image
 * outputs:
 *      none, but hid_r, hid_g, and hid_b arrays are populated with values
 */
void extract_image(
	unsigned int res_r[ROWS][COLS], 
	unsigned int res_g[ROWS][COLS], 
	unsigned int res_b[ROWS][COLS], 
	unsigned int hid_r[ROWS][COLS], 
	unsigned int hid_g[ROWS][COLS], 
	unsigned int hid_b[ROWS][COLS], 
	unsigned int height, unsigned int width);

/* encode
 * Takes two files as input (reference and hidden). The hidden image is encoded
 * into the reference image, creating the encoded image called enc_filename.
 * inputs:
 *      char *ref_filename - pointer to reference photo filename
 *      char *hid_filename - pointer to hidden photo filename
 *      char *enc_filename - pointer to resulting filename of encoded image
 * outputs:
 *      none, but encoded image file is created
 */
void encode(char *ref_filename, char *hid_filename, char *enc_filename);

/* decode
 * Takes encoded file as input and extracts hidden image from it.
 * inputs:
 *      char *enc_filename - pointer to filename of encoded image
 *      char *hid_filename - pointer to name of resulting hidden image
 * outputs:
 *      none, but hidden image file is created
 */
void decode(char *enc_filename, char *hid_filename);
#endif
