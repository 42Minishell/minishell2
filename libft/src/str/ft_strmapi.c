/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   strmapi.c                                          :+:    :+:            */
/*                                                     +:+                    */
/*   By: tjans <marvin@codam.nl>                      +#+                     */
/*                                                   +#+                      */
/*   Created: 2019/10/30 12:49:48 by tjans         #+#    #+#                 */
/*   Updated: 2019/11/04 14:15:36 by tjans         ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include "libft.h"

char	*ft_strmapi(char const *s, char (*f)(unsigned int, char))
{
	unsigned int	i;
	char			*new_s;

	i = 0;
	if (!s || !f)
		return (NULL);
	new_s = ft_strdup(s);
	if (!new_s)
		return (NULL);
	while (s[i])
	{
		new_s[i] = (*f)(i, s[i]);
		i++;
	}
	return (new_s);
}
