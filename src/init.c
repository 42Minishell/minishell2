// Created by Tom Jans on 01-03-21.

#include "minishell.h"

void	env_populate(t_env *env, char *shell)
{
	if (POPULATE_ENV)
	{
		bucket_add(env->env, "PATH", "/usr/local/bin:/usr/bin:/bin");
		bucket_add(env->env, "TERM", "xterm-color");
		bucket_add(env->env, "SHELL", shell);
	}
	env_update_envp(env);
}

void	env_init_pwd(t_env *env)
{
	char	pwd[255];

	getcwd(pwd, 255);
	bucket_add(env->env, "PWD", pwd);
	env_update_envp(env);
}

void	state_init(t_state *state, char **argv)
{
	state->env = env_init();
	env_populate(state->env, *argv);
	env_init_pwd(state->env);
	state->sin = fd_openfd(0);
}

void	state_free(t_state *state)
{
	env_free(state->env);
	fd_close(state->sin);
	free(state->sin);
}
