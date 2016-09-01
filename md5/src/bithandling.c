
#include "bithandling.h"


// apply n-bits left rotation on uint32_t x
uint32_t leftrotate32(uint32_t x, int n)
{
	uint32_t l,r;

	l = x << n;
	r = x >> ((sizeof(x) << 3) - n);

	return l | r;
}

// swap bits x and y on uint64_t n
uint32_t swap32(uint32_t n, int x, int y)
{
	if (x > y) { int tmp = x; x = y; y = tmp; }

	uint32_t mask_x = (uint32_t) 1 << ((sizeof(n) << 3) - x);
	uint32_t mask_y = (uint32_t) 1 << ((sizeof(n) << 3) - y);

	mask_x &= n;
	mask_y &= n;

	n &= ~mask_x & ~mask_y;

	mask_x >>= (y - x);
	mask_y <<= (y - x);

	n |= mask_x | mask_y;
	return n;
}

// reverse endianness
uint32_t reverse_endian32(uint32_t n)
{
	int size = sizeof(n) << 3;
	int mid  = size / 2;

	for (int i = 1; i < mid; i += 2)
	{
		n = swap32(n, i, size - i);
		n = swap32(n, i + 1, size - i + 1);
	}

	return n;
}

