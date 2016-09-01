
#include "io.h"


// return size of file expressed in bytes
long size(char *filename)
{
	FILE *file = NULL;
	long size  = 0;

	file = fopen(filename,"ab");

	if (file)
	{
		size = ftell(file);
		fclose(file);
	}

	return size;
}

// parse file content into uint32_t array
/*
	warning:
		files are ended with '\n' before EOF (at least with gedit)
		this '\n' will be treated as a character of the string to parse
*/
void read(char *filename, uint32_t *content)
{
	FILE* file = NULL;
	file       = fopen(filename, "r");

	if (file != NULL)
	{
		char c = fgetc(file);
		int  i = 0;

		while (c != EOF)
		{
			/*
				As integer in C are big-endianed, we have to reverse every
				uint32_t so that it will be worked out correctly afterwards.
				Or not ?
			*/
			switch (i % 4)
			{
				case 0:
					content[i / 4]  = (uint32_t) c;
					break;
				case 1:
					content[i / 4] |= (uint32_t) c << 8;
					break;
				case 2:
					content[i / 4] |= (uint32_t) c << 16;
					break;
				default:
					content[i / 4] |= (uint32_t) c << 24;
					break;
			}

			c = fgetc(file);
			i++;
		}

		fclose(file);
	}
}

// print hexa values of uint32_t array (debug purpose)
void print(uint32_t *array, long length)
{
	for (long i = 0; i < length; i++) { printf("%x\n", array[i]); }
}


