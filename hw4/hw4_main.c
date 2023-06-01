#include <stdio.h>
#include <stdlib.h>
#include "hw4_provided.h"
#include "hw4.h"

int main()
{
	//ecode test cases
	encode("happyface.png","uchicago.png","encode_test_1.png");
	encode("uchicago.png", "happyface.png", "encode_test_2.png");
	encode("horiz_stripes.png", "checkerboard.png", "encode_test_3.png");
	encode("checkerboard.png", "horiz_stripes.png", "encode_test_4.png");

	//decode test cases
        decode("encode_test_1.png", "decode_test_1.png");
	decode("encode_test_2.png", "decode_test_2.png");
	decode("encode_test_3.png", "decode_test_3.png");
	decode("encode_test_4.png", "decode_test_4.png");
	
	return 1;
}

