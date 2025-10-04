#include <stdio.h>

int
main (void)
{
	int a = 5;
	while (a > 1)
		--a;
	const char* s = "hello, world!";
	printf ("%s\n", s);
	return a;
}
