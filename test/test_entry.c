#include "minishell.h"
#include "tests.h"

int	main(void)
{
	printf("Minishell testing program.\n");
	test_env();
	test_hashtable();
	printf("All tests ran.\n");
	return (0);
}
