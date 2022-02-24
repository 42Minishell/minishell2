/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   tokenizer.h                                        :+:    :+:            */
/*                                                     +:+                    */
/*   By: tjans <tnjans@outlook.de>                    +#+                     */
/*                                                   +#+                      */
/*   Created: 2021/03/05 17:05:42 by zilisabethp   #+#    #+#                 */
/*   Updated: 2022/02/22 18:13:42 by zgargasc      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

/**
 * @file
 * Functions for the tokenizer and data structures for tokens
 */

#ifndef TOKENIZER_H
# define TOKENIZER_H
# include <stdbool.h>
# include "hashtable.h"

# define POS 0
# define BUF 1

struct	s_state;
struct	s_env;

/**
 * @brief Type of the token, used for setting up redirections
 *
 * @warning
 * All the types after and including redirect_to_pipe assume the token for
 * it is 2 characters, if it is only one insert it before redirect_to_pipe
 */
typedef enum e_token_type
{
	non_special = 0,
	executable,
	redirect_to_overwrite,
	redirect_to_append,
	redirect_from_file,
	redirect_from_file_and_unlink,
	redirect_to_pipe,
	read_until_delimiter
}			t_token_type;

/**
 * @brief Type for the builtin function
 */
typedef int (\
		*t_builtin_function)\
		(int argc, char **argv, struct s_state *state, int ipc[2]);

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

/**
 * @struct t_token
 * Token object, contains parsed input from command line
 *
 * @var t_token::token
 * String with contents of token
 * @var t_token::type
 * Type of the token
 * @var t_token::next
 * Pointer to next token
 * @var t_token::result_type
 * Type of the resolver result
 * @var t_token::result
 * Content of the resolver result
 * @var t_token::pipe_fd
 * File descriptors for the pipes if token contains a pipe
 * @var t_token::ipc_fd
 * File descriptors for IPC pipes, if the token is a builtin
 * @var t_token::pid
 * When executed the pid of the process contained in the token is stored here
 */
typedef struct s_token
{
	char					*token;
	t_token_type			type;
	struct s_token			*next;
	struct s_token			*prev;

	t_resolve_result_type	result_type;
	t_resolve_result		result;

	int						pipe_fd[2];
	int						ipc_fd[2];
	pid_t					pid;
}	t_token;

typedef int (\
		*t_lexer_action)\
		(t_token **dst, char **in, struct s_state *state);

typedef struct s_lexer_state
{
	char			token;
	t_lexer_action	action;
}				t_lexer_action_lookup;

typedef enum e_literal_mode
{
	DEFAULT,
	DOUBLEQUOTE,
	SINGLEQUOTE
}				t_literal_mode;

/**
 * @brief Tokenizer, parses the input string into tokens.
 *
 * It splits the input up into separate arguments, and parses special directives
 * like environment variables.
 * @param in String to parse, will be freed
 * @param env Environment variables, bucket from t_env::env
 * @return Returns linked lists of token objects
 */
t_token			*tokenizer(char *in, struct s_state *state);
int				is_special_character(char c);
t_token			*create_token(t_token **dst);
t_token			*free_token_list(t_token *head);
char			*copy_str_until_special_char(char **in, struct s_state *state);
t_token			*token_create_empty(t_token *next, t_token *prev);
void			reallocate_string(char **s, size_t *buf_size);
int				insert_env_into_string(char **in, char **s, size_t *posbuf, \
	struct s_state *state);
int				lexer_action_whitespace(t_token **dst, char **in, \
	struct s_state *state);
int				lexer_action_non_special(t_token **dst, char **in, \
	struct s_state *state);
int				lexer_action_redirection_right(t_token **dst, char **in, \
	struct s_state *state);
int				lexer_action_redirection_left(t_token **dst, char **in, \
	struct s_state *state);
int				lexer_action_pipe(t_token **dst, char **in, \
	struct s_state *state);

/// Our protected malloc function.
void			*ft_malloc(size_t size);
#endif
