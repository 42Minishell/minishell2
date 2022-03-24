/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   minishell.h                                        :+:    :+:            */
/*                                                     +:+                    */
/*   By: zgargasc <zgargasc@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2021/12/18 17:27:47 by zgargasc      #+#    #+#                 */
/*   Updated: 2022/03/02 20:04:11 by zgargasc      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

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
# include <readline/readline.h>
# include <readline/history.h>
# include <errno.h>
# include "config.h"
# include "hashtable.h"
# include "env.h"
# include "tokenizer.h"
# include "libft.h"

/**
 * @struct t_state
 * @brief Global state of the shell
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
	int			ret;
}	t_state;

/// Allocate and initialize a state object
void					state_init(t_state *state, char **argv, char **envp);
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
void					exec(t_state *state, t_token *args);

/**
 * Executes a builtin
 * @param state State object of current minishell instance
 * @param token Token from the tokenizer, used to execute the function pointer
 * @param argv Arguments, same as in exec
 */
void					exec_builtin(t_state *state, t_token *token, \
	char **argv);

/**
 * @brief Resolves path to binary.
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

/// Iterates path_resolve() for every token in list
int						path_resolve_token_list(t_env *env, t_token *tokens);

/// Setups interactive signals, for when no childs are being executed
void					setup_int_signals(void);

/// Setups non-interactive signals, to send signals to the child process
void					setup_nonint_signals(void);

/**
 * @brief Initializes pipes and IPC
 *
 * This function iterates through the token list, searches all tokens with the
 * type t_token_type::redirect_to_pipe and creates a pipe for them and stores
 * the file descriptors in t_token::pipe_fd.
 *
 * If the function finds a builtin token it will open a pipe for IPC too and
 * store the file descriptors in t_token::ipc_fd
 * @param token Head of the token list
 * @return Non-zero on failure, 0 on success
 */
int						pipes_init(t_token *token);

// functions to monitor the child exit status,
// manage zombies and set the exit status.

pid_t					exit_status_child(pid_t new_status, _Bool get, \
						_Bool non_stat);
void					wait_children(void);

void					ft_error(char *s, size_t len);

/// Struct for pids of children
typedef struct s_pid_list
{
	pid_t				pid;
	struct s_pid_list	*next;
}				t_pid_list;

extern t_pid_list		*g_pid;

/// Wrapper function for the fork, to save all PIDs
pid_t					fork_wrapper(void);

/// Frees the g_pid list, and sets it to NULL
void					free_pid_list(void);

/// util function for exec, executes the child.
void					exec_child(t_token *cur_token, \
						t_state *state, t_token *pipe_);

/// sets up the io handling for the child.
void					io_setup_child(t_token *cur_token, t_token *next_token);
#endif
