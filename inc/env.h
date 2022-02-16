/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   env.h                                              :+:    :+:            */
/*                                                     +:+                    */
/*   By: zgargasc <zgargasc@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2021/12/18 17:27:44 by zgargasc      #+#    #+#                 */
/*   Updated: 2022/02/16 19:09:47 by zgargasc      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

// Created by Tom Jans on 28-02-21.

/**
 * @file
 * Environment variable handling
 */
#ifndef ENV_H
# define ENV_H
# include "hashtable.h"

/**
 * @struct t_env
 * Struct that keeps track of environment variables in a hash table
 *
 * @var t_env::env
 * Hash table containing the environment variables
 * @var t_env::envp
 * Array of C strings containing key=value. Updated with env_update_envp()
 */
typedef struct s_env
{
	t_bucket	*env;
	char		**envp;
}	t_env;

/// Allocate and initialize a env object
t_env	*env_init(void);
/// Free the env object and members
void	env_free(t_env *env);

/**
 * @brief Clears and creates a new envp array at t_env::envp
 *
 * This function refreshes the array of C strings containing environment
 * variables.
 *
 * This is to be called every time after adding environment variables or
 * removing environment variables to keep it in sync with the hash table.
 * @param[in] env env object
 */
void	env_update_envp(t_env *env);
/// Initialize environment variables with hardcoded presets
void	env_populate(t_env *env, char *shell, char **envp);
/// Get current directory and save it in the PWD environment variable
void	env_init_pwd(t_env *env);

/// Our protected malloc function.
void	*ft_malloc(size_t size);

/**
 * Check if binary is in PATH and returns the location if it is.
 * @param[in] env env object
 * @param[in] exec binary to find
 * @return Absolute path if found; otherwise NULL
 */
char	*env_path_lookup(t_env *env, char *exec);
#endif
