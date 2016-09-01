
#include "md5.h"


int main(int argc, char *argv[])
{
	if (argc < 2)	{ printf("missing input file argument\n"); exit(-1); }

	long     length   = 0;
	uint32_t *message = init(argv[1], &length);

	// print(message, length);

	char *digest = hash(message, length);
	printf("%s\n", digest);

	return 0;
}

uint32_t* init(char *filename, long *size_array)
{
	long size_message = size(filename);

	// work final array's size out
	/*
		array's size must be a multiple of 16 (groups of 64 bytes) and must
		contain at least the message, one byte 1000 0000 and 8 bytes for
		message's size
	*/
	if ((size_message + 9) % 64)
		*size_array = (((size_message + 9) / 64) + 1) * 16;
	else
		*size_array =  ((size_message + 9) / 64) * 16;

	// parse message into uint32 array
	uint32_t *content = (uint32_t*) malloc(*size_array * sizeof(uint32_t));
	read(filename, content);

	// add byte 1000 0000 right after message
	/*
		as we do not want to add char 0x00 to the message, we have to find the
		message's last character and set the following byte to 1000 0000 (which
		is 0x80 in hexadecimal representation)
	*/
	long i = size_message / 4;

	/*
		As integer in C are big-endianed, we have to reverse every
		uint32_t so that it will be worked out correctly afterwards.
		Or not ?
	*/
	switch (size_message % 4)
	{
		case 0:
			content[i] = 0x80;
			break;
		case 1:
			content[i] |= 0x80 << 8;
			break;
		case 2:
			content[i] |= 0x80 << 16;
			break;
		default:
			content[i] |= 0x80 << 24;
			break;
	}

	// fill array with bytes 0000 0000
	i++;

	while (i < *size_array - 2)
	{
		content[i] = 0x00 << 24;
		i++;
	}

	// add message's size
	content[i] = (uint32_t)  ((uint64_t) (size_message << 3));   i++;
	content[i] = (uint32_t) (((uint64_t) (size_message << 3)) >> 16);

	return content;
}

// hash message into a MD5 string
/*
	TODO manage endianness : all worked out numbers should be little-endian
		expressed
*/
char* hash(uint32_t *message, long size_message)
{
	uint32_t r[64] = {
		7, 12, 17, 22,  7, 12, 17, 22,  7, 12, 17, 22,  7, 12, 17, 22,
		5,  9, 14, 20,  5,  9, 14, 20,  5,  9, 14, 20,  5,  9, 14, 20,
		4, 11, 16, 23,  4, 11, 16, 23,  4, 11, 16, 23,  4, 11, 16, 23,
		6, 10, 15, 21,  6, 10, 15, 21,  6, 10, 15, 21,  6, 10, 15, 21 };

	uint32_t k[64] = {
		0xd76aa478, 0xe8c7b756, 0x242070db, 0xc1bdceee,
		0xf57c0faf, 0x4787c62a, 0xa8304613, 0xfd469501,
		0x698098d8, 0x8b44f7af, 0xffff5bb1, 0x895cd7be,
		0x6b901122, 0xfd987193, 0xa679438e, 0x49b40821,
		0xf61e2562, 0xc040b340, 0x265e5a51, 0xe9b6c7aa,
		0xd62f105d, 0x02441453, 0xd8a1e681, 0xe7d3fbc8,
		0x21e1cde6, 0xc33707d6, 0xf4d50d87, 0x455a14ed,
		0xa9e3e905, 0xfcefa3f8, 0x676f02d9, 0x8d2a4c8a,
		0xfffa3942, 0x8771f681, 0x6d9d6122, 0xfde5380c,
		0xa4beea44, 0x4bdecfa9, 0xf6bb4b60, 0xbebfbc70,
		0x289b7ec6, 0xeaa127fa, 0xd4ef3085, 0x04881d05,
		0xd9d4d039, 0xe6db99e5, 0x1fa27cf8, 0xc4ac5665,
		0xf4292244, 0x432aff97, 0xab9423a7, 0xfc93a039,
		0x655b59c3, 0x8f0ccc92, 0xffeff47d, 0x85845dd1,
		0x6fa87e4f, 0xfe2ce6e0, 0xa3014314, 0x4e0811a1,
		0xf7537e82, 0xbd3af235, 0x2ad7d2bb, 0xeb86d391
	};

	uint32_t h0 = 0x67452301;
	uint32_t h1 = 0xefcdab89;
	uint32_t h2 = 0x98badcfe;
	uint32_t h3 = 0x10325476;

	long nloops = size_message / 16;

	for (long i = 0; i < nloops; i++)
	{
		long offset = i * 16;

		uint32_t a = h0;
		uint32_t b = h1;
		uint32_t c = h2;
		uint32_t d = h3;
		uint32_t f = 0;
		uint32_t g = 0;

		for (int j = 0; j < 64; j++)
		{
			uint32_t tmp  = 0;
			uint32_t tmp2 = 0;

			if (j < 16)
			{
				f = (b & c) | ((~b) & d);
				g = j;
			}
			else if (j < 32)
			{
				f = (d & b) | ((~d) & c);
				g = (5 * j + 1) % 16;
			}
			else if (j < 48)
			{
				f = b ^ c ^ d;
				g = (3 * j + 5) % 16;
			}
			else
			{
				f = c ^ (b | (~d));
				g = (7 * j) % 16;
			}

			tmp  = d;
			d    = c;
			c    = b;

			/*
				left rotation will not get the same result if the number is
				little or big endianed, so that we have to reverse it before and
				after rotation.
				Or not ?
			*/
			tmp2 = a + f + k[j] + message[g + offset];
			tmp2 = reverse_endian32(tmp2);
			tmp2 = leftrotate32(tmp2, r[j]);
			tmp2 = reverse_endian32(tmp2);

			b    = b + tmp2;
			a    = tmp;
		}

		h0 += a;
		h1 += b;
		h2 += c;
		h3 += d;
	}

	h0 = reverse_endian32(h0);
	h1 = reverse_endian32(h1);
	h2 = reverse_endian32(h2);
	h3 = reverse_endian32(h3);

	char *digest = (char*) malloc(32 * sizeof(char));
	sprintf(digest, "%x%x%x%x", h0, h1, h2, h3);

	return digest;
}

