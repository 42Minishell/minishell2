// Created by Tom Jans on 27-02-21.

/**
 * @file
 * Minishell header, state and other unsorted functions
 */
#ifndef MINISHELL_H
# define MINISHELL_H
# include <stdio.h>
# include <unistd.h>
# include <sys/stat.h>
# include <errno.h>
# include "config.h"
# include "hashtable.h"
# include "env.h"
# include "libft.h"

/**
 * @struct t_state
 * Global state of the shell
 *
 * This keeps track of stuff like environment variables
 * @var t_state::env
 * Environment variables are stored here
 * @var t_state::sin
 * This is a GNL-Like "stream" for the standard input
 */
typedef struct s_state
{
	t_env		*env;
	t_fdstream	*sin;
}	t_state;

/// Allocate and initialize a state object
void	state_init(t_state *state, char **argv);
/// Free the state object and members
void	state_free(t_state *state);

/**
 * Show a prompt and take user input
 * @warning
 * Currently it also handles _env and returns an empty string.
 * This is behaviour that does not belong here, and is purely for POC reasons
 * @param[in] state The application state
 * @return C string of user input, or NULL on failure
 */
char	*prompt(t_state *state);

/**
 * Resolves path to binary.
 *
 * Lookup happens in this order to allow overriding by end-user:
 * 1. Check if the input is an absolute or relative path
 *    This is the case when the input starts with ./ or /
 * 2. Iterate through the PATH environment variable from left to right
 *    and stat every directory to check if the binary is located there.
 *    If found return it
 * 3. Check if it is an internal function, if so return the internal one
 * 4. If not found return NULL
 * @param[in] env Environment variables
 * @param[in] exec C String containing path or binary to look up
 * @return C string to path of executable, or NULL when not found
 * When NULL is returned do check the errno for exact reason.
 */
char	*path_resolve(t_env *env, char *exec);
#endif
