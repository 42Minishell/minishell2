/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   tokenizer.h                                        :+:    :+:            */
/*                                                     +:+                    */
/*   By: zilisabethpangasch <zilisabethpangasch@      +#+                     */
/*                                                   +#+                      */
/*   Created: 2021/03/05 17:05:42 by zilisabethp   #+#    #+#                 */
/*   Updated: 2021/03/05 17:08:57 by zilisabethp   ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#ifndef TOKENIZER_H
# define TOKENIZER_H
#include <stdbool.h>
#include "minishell.h"

typedef struct 	s_token
{
	char				*token;
	struct s_token		*next;
}				t_token;


typedef enum	e_tokens
{
	non_special = 0, 
}				t_tokens;

int		iswhitespace(char c);
void	ft_error(char *msg, int bytes);
t_token	*tokenizer(char *in, t_bucket *env);
char	*easyjoin(char *s1, char *s2, char *s3);
void res_env(char **input, t_bucket *env);
#endif
