
#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <string.h>
#include <math.h>

#define DEBUG 0


int hamming_distance(uint16_t x, uint16_t y, int n)
{
	int res = 0;

	// erase not useful bits 
	x = (x << (16 - n)) >> (16 - n);
	y = (y << (16 - n)) >> (16 - n);

	// find similar bits
	x ^= y;

	// counts not similar bits
	int i;
	for (i = 0; i < n; i++)
	{
		if (!x) { return res; }

		res++;
		x >>= 1;
	}

	return res;
}

void hamming_codification(uint16_t *alphabet, uint16_t alphabet_size,
	uint16_t word_length, uint8_t distance)
{
	uint16_t i, b, tmp;

	uint16_t word_id = 1;
	uint16_t comb_id = 1;

	uint16_t max_word_id = alphabet_size;
	uint16_t max_comb_id = pow(2, word_length);

	alphabet    = (uint16_t*) malloc(alphabet_size * sizeof(uint16_t));
	alphabet[0] = 0;

	while (word_id < max_word_id && comb_id < max_comb_id)
	{
		b = 1;

		for (i = 0; i < word_id; i++)
		{
			tmp = hamming_distance(comb_id, alphabet[i], word_length);

			if (DEBUG)
			{
				printf("comb %d ; ", comb_id);
				printf("dist %d ; word %d\n", tmp, word_id);
			}

			if (tmp < distance) { b = 0; }
		}

		if (b) { alphabet[word_id] = comb_id; word_id++; }

		comb_id++;
	}

	if (word_id == max_word_id) { printf("done\n"); }
	else { printf("not enough bits\n"); }
}


int main(int argc, char *argv[])
{
	uint16_t *alphabet = NULL;

	if (argc < 3)
	{
		printf("Missing at least one argument.\nPlease provide in this order :\n- alphabet size\n- word length\n- minimal hamming distance between words");
		exit(-1);
	}

	hamming_codification(alphabet, atoi(argv[1]), atoi(argv[2]),
		atoi(argv[3]));

	return 0;	
}
