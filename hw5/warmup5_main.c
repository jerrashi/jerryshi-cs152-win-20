#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <png.h>
#include "warmup5.h"
#include "warmup5_provided.h"

int main(int argc,char* argv[])
{
	if(argc >= 3)
	{
		int test = (int)argv[1];
		switch(test)
		{
			case 0: 
				printf("TESTING SAFE_STR_CONCAT: ------\n");
				if((int)argv[2] == 1) //default tests
				{
				        printf("str1 = Bobs\n");
				        printf("str2 = Burgers\n");
				        char str1[] = "Bobs";
				        char str2[] = "Burgers";
				        char *str3 =  safe_str_concat(str1, 
							str2);
				        printf("---str3 = %s \n", str3);
				        printf("str4 = High\n");
				        printf("str5 = Road\n");
				        char str4[] = "High";
				        char str5[] = "Road";
				        char *str6 = safe_str_concat(str4, 
							str5);
				        printf("---str6 = %s \n", str6);
				        printf("str7 = Kesha\n");
				        printf("str8 = Rose\n");
				        char str7[] = "Kesha";
				        char str8[] = "Rose";
				        char *str9 = safe_str_concat(str7, 
							str8);
				        printf("---str9 = %s \n", str9);
				}
				else
				{
					printf("\n%s + %s = %s", argv[2], 
						argv[3], 
					safe_str_concat(argv[2], argv[3]));
					printf("\n---EXPECTED: %s", argv[4]);
				}
				break;
	
			case 1: //write and read test merged for simplicity
				printf("TESTING INT_VECTOR FUNCTIONS: ---\n");
				if((int)argv[2] == 1) //default tests
				{
				        int_vector * p = make_init_array();
				        printf("Old Vector length: %d \n", 
						p->allocated_size);
				        printf("----write_value(p, 1, 50)\n");
				        write_value(p, 1, 50);
				        printf("New Vector length: %d \n", 
						p->allocated_size);
				        printf("New Value p[1] = %d\n", 
						read_value(p,1));
		        		printf("---write_value(p, 15, 20)\n");
		        		write_value(p, 15, 20);
		        		printf("New Value p[15] = %d\n", 
						read_value(p,15));
				        printf("New Vector length: %d \n", 
					p->allocated_size);
					printf("---write_value(p, 50, 25)\n");
				        write_value(p, 50, 25);
				        printf("New Value p[50] = %d\n", 
						read_value(p,50));
				        printf("New Vector length: %d \n", 
						p->allocated_size);
				}
				else
				{
					int_vector * p = make_init_array();
					printf("Old vector length: %d\n", 
						p->allocated_size);
					printf("---write_value(p, %d, %d \n)",
						(int)argv[3], (int)argv[4]);
					write_value(p, (int)argv[3], 
							(int)argv[4]);
					printf("New value p[%d] = %d\n", 
						(int)argv[3], read_value(p,
						(unsigned int)argv[3]));
					printf("New vector length: %d \n",
						p->allocated_size);
					
				}
				break;
			case 2:
				printf("TESTING PIXEL FUNCTIONS: ------\n");
				pixel col;
				col.red = (int)argv[4];
				col.green = (int)argv[5];
				col.blue = (int)argv[6];
				pixel ** pic = make_and_init_image(
						(int)argv[2],
						(int)argv[3], col);
				break;
		}
	}
	
	return 1;
}
