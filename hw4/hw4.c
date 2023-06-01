#include <stdio.h>
#include <stdlib.h>
#include "hw4.h"
#include "hw4_provided.h"

/* hide_image
 * Takes three sets of three arrays as input. Each set represents an image
 * to be hidden, a reference image, and the result of hiding the latter in the
 * former, respectively. Each array represents red, green, and blue values,
 * respectively. Hiding process is very simple: if hidden image value is
 * greater than 128, then resulting image must be even.
 * inputs:
 * 	ref_r, ref_g, ref_b - arrays representing reference image
 * 	hid_r, hid_g, hid_b - arrays representing hidden image
 * 	res_r, res_g, res_b - arrays representing "output" resulting image
 * outputs:
 * 	none, but res_r, res_g, and res_b arrays are populated with values
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
	unsigned int height, unsigned int width)
{
	if ((height > ROWS) || (width > COLS))
	{
		fprintf(stderr, "HIDE_IMAGE ERROR: height and/or width values "
			"are too big.");
		return;
	}

	int row, col; //variable declaration

	for (row = 0; row < ROWS; row++) //iterate through all rows
	{
		for (col = 0; col < COLS; col++) //and all cols
		{
			// red array
			res_r[row][col] = ref_r[row][col];
			// hidden img >= 128 and ref img is even
			if ((hid_r[row][col]>=128) && (ref_r[row][col]%2==0))
			{
				res_r[row][col] = ref_r[row][col] + 1;
			}
			// hidden img < 128 and ref img is odd
			if ((hid_r[row][col]<128) && (ref_r[row][col]%2!=0))
			{
				res_r[row][col] = ref_r[row][col] - 1;
			}

                        // green array
                        res_g[row][col] = ref_g[row][col];
                        // hidden img >= 128 and ref img is even
                        if ((hid_g[row][col]>=128) && (ref_g[row][col]%2==0))
                        {
                                res_g[row][col] = ref_g[row][col] + 1;
                        }
                        // hidden img < 128 and ref img is odd
                        if ((hid_g[row][col]<128) && (ref_g[row][col]%2!=0))
                        {
                                res_g[row][col] = ref_g[row][col] - 1;
                        }

                        // blue array
                        res_b[row][col] = ref_b[row][col];
                        // hidden img >= 128 and ref img is even
                        if ((hid_b[row][col]>=128) && (ref_b[row][col]%2==0))
                        {
                                res_b[row][col] = ref_b[row][col] + 1;
                        }
                        // hidden img < 128 and ref img is odd
                        if ((hid_b[row][col]<128) && (ref_b[row][col]%2!=0))
                        {
				res_b[row][col] = ref_b[row][col] - 1;
                        }

		}
	}	
}


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
	unsigned int height, unsigned int width)
{
        int row, col; //variable declaration

        for (row = 0; row < ROWS; row++) //iterate through all rows
        {
                for (col = 0; col < COLS; col++) //and all cols
                {
                        // red array
                        if (res_r[row][col] % 2 == 0) //res value is even
                        {
				hid_r[row][col] = 0;
			}
			if (res_r[row][col] % 2 != 0) // or odd
                        {
				hid_r[row][col] = 255;
                        }

                        // green array
			if (res_g[row][col] % 2 == 0) // res value is even
			{
				hid_r[row][col] = 0;
			}
                        if (res_r[row][col] % 2 != 0) // or odd
                        {
				hid_g[row][col] = 255;
                        }
                        
			// blue array
			if (res_b[row][col] % 2 == 0) // res value is even
			{
				hid_b[row][col] = 0;
			}
			if (res_b[row][col] % 2 != 0) // ref img is odd
                        {
                                hid_b[row][col] = 255;
                        }

                }
        }
}

/* encode
 * Takes two files as input (reference and hidden). The hidden image is encoded
 * into the reference image, creating the encoded image called enc_filename.
 * inputs:
 * 	char *ref_filename - pointer to reference photo filename
 * 	char *hid_filename - pointer to hidden photo filename
 * 	char *enc_filename - pointer to resulting filename of encoded image
 * outputs:
 * 	none, but encoded image file is created
 */
void encode(char *ref_filename, char *hid_filename, char *enc_filename)
{
	unsigned int image_width = COLS, image_height = ROWS; // variable declaration

	//reading in reference image
	unsigned int ref_r[ROWS][COLS], ref_g[ROWS][COLS], ref_b[ROWS][COLS];
	provided_read_png(ref_filename, ref_r, ref_g, ref_b, &image_width, 
			  &image_height);

	//reading in hidden image
        unsigned int hid_r[ROWS][COLS], hid_g[ROWS][COLS], hid_b[ROWS][COLS];
        provided_read_png(hid_filename, hid_r, hid_g, hid_b, &image_width,
			  &image_height);

	//encoding process
        unsigned int res_r[ROWS][COLS], res_g[ROWS][COLS], res_b[ROWS][COLS];
	hide_image(ref_r, ref_g, ref_b, hid_r, hid_g, hid_b, res_r, res_g, 
		   res_b, image_height, image_width);

	//writing file process
	provided_write_png(enc_filename, res_r, res_g, res_b, image_width,
			   image_height);
}

/* decode
 * Takes encoded file as input and extracts hidden image from it.
 * inputs:
 * 	char *enc_filename - pointer to filename of encoded image
 * 	char *hid_filename - pointer to name of resulting hidden image
 * outputs:
 * 	none, but hidden image file is created
 */
void decode(char *enc_filename, char *hid_filename)
{
        unsigned int image_width = COLS, image_height = ROWS; // variable declaration

        //reading in encoded image
        unsigned int enc_r[ROWS][COLS], enc_g[ROWS][COLS], enc_b[ROWS][COLS];
        provided_read_png(enc_filename, enc_r, enc_g, enc_b, &image_width, 
			  &image_height);

        //decoding process
        unsigned int hid_r[ROWS][COLS], hid_g[ROWS][COLS], hid_b[ROWS][COLS];
	extract_image(enc_r, enc_g, enc_b, hid_r, hid_g, hid_b, image_height,
			image_width);

	//writing file process
        provided_write_png(hid_filename, hid_r, hid_g, hid_b, image_width,
                           image_height);

}
