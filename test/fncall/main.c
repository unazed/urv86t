#include <stdlib.h>
	
int
function (int a)
{
	return a << 1;
}
	
int
main (void)
{
	volatile int a = 5;
	volatile int b = function (a);
	return EXIT_SUCCESS;
}
