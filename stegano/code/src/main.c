
#include <stdlib.h>
#include <stdio.h>


void p(void)
{
	int z = 0;

	z--; z++; z++; z--;
	z--; z++; z++; z--;
	z--; z++; z++; z--;
	z--; z++; z++; z--;
}

int decode()
{
	int res = 0;

	void (*pf)();
	pf = p;

	unsigned char *pc = (unsigned char*) pf;

	int i = 11; // useless data offset
	while (pc[i] != 0xC3)
	{
		// variable --
		if (pc[i] == 0x83 && pc[i+1] == 0x6d)
		{
			res <<= 1;
			printf("0 ");
		}
		// variable ++
		else if (pc[i] == 0x83 && pc[i+1] == 0x45)
		{
			res <<= 1; res |= 0x01;
			printf("1 ");
		}

		i += 4; // useless data offset
	}

	printf("\n");
	return res;
}


int main(void)
{
	decode();

	return 0;
}
