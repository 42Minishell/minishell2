#include "builtins.h"

int	builtin_exit(int argc, char **argv, t_state *state)
{
	int	exit_no;

	(void)state;
	if (argc < 2)
		exit(0);
	exit_no = ft_atoi(argv[1]);
	while (*argv[1])
	{
		if (!ft_isdigit(*argv[1]))
		{
			printf("%s: numeric argument required\n", *argv);
			exit(2);
		}
		argv[1]++;
	}
	exit(exit_no);
}
