/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   tokenizer.h                                        :+:    :+:            */
/*                                                     +:+                    */
/*   By: zilisabethpangasch <zilisabethpangasch@      +#+                     */
/*                                                   +#+                      */
/*   Created: 2021/03/05 17:05:42 by zilisabethp   #+#    #+#                 */
/*   Updated: 2021/03/30 16:49:27 by zilisabethp   ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#ifndef TOKENIZER_H
# define TOKENIZER_H
# include <stdbool.h>
# include "hashtable.h"

typedef enum e_tokens
{
	non_special = 0,
	executable
}	t_tokens;

/**
 * @struct t_token
 * Token object, contains parsed input from command line
 *
 * @var t_token::token
 * String with contents of token
 * @var t_token::next
 * Pointer to next token
 */

typedef struct s_token
{
	char				*token;
	t_tokens			type;
	struct s_token		*next;
}	t_token;

/**
 * Tokenizer, parses the input string into tokens.
 *
 * It splits the input up into separate arguments, and parses special directives
 * like environment variables.
 * @param in String to parse, will be freed
 * @param env Environment variables, bucket from t_env::env
 * @return Returns linked lists of token objects
 */
t_token		*tokenizer(char *in, t_bucket *env);

/**
 * Frees the linked list of token objects
 * @param head Pointer to the first object in the linked list.
 */
void		tokenizer_list_free(t_token *head);

/*
 * Internal functions, undocumented for now :)
 */

int			find_next_token(char *in);
// int			find_end_token(char *in);
t_token		*new_token(void);
void		get_token_list(t_token **token_l, char *in, int next_is_exec);
int			env_length(char *in);
char		*strip_token(char *token);
int			iswhitespace(char c);
void		ft_error(char *msg, int bytes);
char		*easyjoin(char *s1, char *s2, char *s3);
void		res_env(char **input, t_bucket *env);
#endif
