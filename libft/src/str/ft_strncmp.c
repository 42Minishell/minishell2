/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   strncmp.c                                          :+:    :+:            */
/*                                                     +:+                    */
/*   By: tjans <marvin@codam.nl>                      +#+                     */
/*                                                   +#+                      */
/*   Created: 2019/10/29 13:27:36 by tjans         #+#    #+#                 */
/*   Updated: 2019/11/07 16:16:08 by tjans         ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_strncmp(const char *s1, const char *s2, size_t n)
{
	unsigned const char	*c1;
	unsigned const char	*c2;

	c1 = (unsigned const char *)s1;
	c2 = (unsigned const char *)s2;
	while (n)
	{
		if (*c1 != *c2)
			return (*c1 - *c2);
		if (!*c1 && *c1 == *c2)
			return (0);
		c1++;
		c2++;
		n--;
	}
	return (0);
}
