// Created by Tom Jans on 27-02-21.

/**
 * @file
 * Minishell header, state and other unsorted functions
 */

/**
 * \mainpage Minishell project
 * Welcome to the generated HTML Documentation of minishell<br />
 * View the docs through the top menu!, glhf.
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
# include "tokenizer.h"
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

/// Interface for builtin functions
typedef int				(*t_builtin_function) \
	(int argc, char **argv, t_state *state);

/**
 * @brief Type of result written by path_resolve()
 */
typedef enum e_resolve_result_type
{
	NOTFOUND,
	EXTERNAL_BINARY,
	BUILTIN
}	t_resolve_result_type;

/**
 * @brief union containing the result of path_resolve()
 */

typedef union u_resolve_result
{
	char				*path;
	t_builtin_function	builtin;
}	t_resolve_result;

/// Allocate and initialize a state object
void					state_init(t_state *state, char **argv);
/// Free the state object and members
void					state_free(t_state *state);

/**
 * Show a prompt and take user input
 * @param[in] state The application state
 * @return C string of user input, or NULL on failure
 */
char					*prompt(t_state *state);

/**
 * Execute binary
 * @param state State object of current minishell instance
 * @param path Absolute path to binary
 * @param args Arguments for the binary, in token form
 */
void	exec(t_state *state, char *path, t_token *args);

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
 * @param[out] result union to write result to
 * @return Type of result found, or NOTFOUND/NULL if nothing is found
 */
t_resolve_result_type	path_resolve(t_env *env, char *exec,
							t_resolve_result *result);
#endif
