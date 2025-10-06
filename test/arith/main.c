#include <stdlib.h>
	
int
main (void)
{
	volatile int a = 8, b = 16;
	volatile short
		c = a + b,
		d = a - b,
		e = a / b,
		f = a << b,
		g = a >> b,
		h = a | b,
		i = a & b,
		j = a ^ b,
		k = a % b,
		l = a * b;
	return EXIT_SUCCESS;
}
