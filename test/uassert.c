#include <stdio.h>
#include "tests.h"

void	uassert(int condition, char *src)
{
	if (!condition)
		printf("Test failed: %s\n", src);
}
