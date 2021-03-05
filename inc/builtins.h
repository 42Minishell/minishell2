// Created by Tom Jans on 05-03-21.

/**
 * @file
 * @brief Header containing builtin functions
 * 
 * Builtins function just like any other C program being executed.
 * 
 * The interface for builtin functions contain argc, argv like usual.
 * The biggest difference is that they also get passed the state object
 * so they can adjust the state of the terminal which is needed for
 * stuff like setting environment variables.
 */

#ifndef BUILTINS_H
# define BUILTINS_H
# include <stdlib.h>
# include "minishell.h"

/**
 * @struct t_function_lookup
 * key->function entries for find_builtin_func()
 * 
 * In builtins.c there s a static function to get the table containing
 * all builtins.
 */
typedef struct s_function_lookup
{
	char	*exec;
	void	*func_ptr;
}	t_function_lookup;

/**
 * @brief Function to lookup builtin function
 * @param[in] exec Name to lookup in the table
 * @return Pointer to function or NULL if not found
 */
void	*find_builtin_func(char *exec);

/// Unset environment variable
int		builtin_unset(int argc, char **argv, t_state *state);

#endif