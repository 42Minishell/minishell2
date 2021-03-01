/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   memccpy.c                                          :+:    :+:            */
/*                                                     +:+                    */
/*   By: tjans <marvin@codam.nl>                      +#+                     */
/*                                                   +#+                      */
/*   Created: 2019/10/28 17:02:51 by tjans         #+#    #+#                 */
/*   Updated: 2019/11/07 16:15:04 by tjans         ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memccpy(void *dst, const void *src, int c, size_t n)
{
	unsigned char	*csrc;
	unsigned char	*cdst;
	unsigned char	cc;

	cc = (unsigned char)c;
	csrc = (unsigned char*)src;
	cdst = (unsigned char*)dst;
	while (n)
	{
		*cdst = *csrc;
		if (*cdst == cc)
			return (cdst + 1);
		csrc++;
		cdst++;
		n--;
	}
	return (NULL);
}
