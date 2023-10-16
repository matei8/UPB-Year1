#include <stdio.h>

extern long get_rand();

int main(void)
{
	long ret;
	ret = get_rand();
	printf("%ld\n", ret);

	return 0;
}