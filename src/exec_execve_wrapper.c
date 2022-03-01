//
// Created by docvi on 3/1/22.
//

#include "minishell.h"

void	chad_execve(char *exec, char **argv, char **envp)
{
	if (execve(exec, argv, envp))
	{
		printf("Error: %s\n", strerror(errno));
		exit(errno);
	}
}