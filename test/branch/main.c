#include <stdlib.h>

int
main (void)
{
	volatile int a = 1;
	if (a > 2)
		a = 3;
	else
		a = 4;
	return EXIT_SUCCESS;
}
