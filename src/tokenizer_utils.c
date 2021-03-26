/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   utils.c                                            :+:    :+:            */
/*                                                     +:+                    */
/*   By: zilisabethpangasch <zilisabethpangasch@      +#+                     */
/*                                                   +#+                      */
/*   Created: 2021/03/05 17:11:52 by zilisabethp   #+#    #+#                 */
/*   Updated: 2021/03/05 17:12:32 by zilisabethp   ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	*easyjoin(char *s1, char *s2, char *s3)
{
	char	*dest;
	char	*dest_triple;

	dest = ft_strjoin(s1, s2);
	free(s1);
	free(s2);
	if (s3)
	{
		dest_triple = ft_strjoin(dest, s3);
		free(s3);
		free(dest);
		return (dest_triple);
	}
	return (dest);
}

void	ft_error(char *msg, int bytes)
{
	char	newline;

	newline = '\n';
	write(1, msg, bytes);
	write(1, &newline, 1);
	exit(1);
}

int	iswhitespace(char c)
{
	if ((c >= 9 && c <= 13) || c == 32)
		return (1);
	return (0);
}

int	env_length(char *in)
{
	int		i;

	i = 0;
	while (in[i] && !iswhitespace(in[i]) && in[i] != '\n')
		i++;
	return (i);
}
