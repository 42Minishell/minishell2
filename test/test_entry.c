#include "minishell.h"
#include "tests.h"

int	main(void)
{
	printf("Minishell testing program.\n");
	test_env();
	test_hashtable();
	test_tokenizer();
	printf("All tests ran.\n");
	return (0);
}
