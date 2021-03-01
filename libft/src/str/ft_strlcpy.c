/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   strlcpy.c                                          :+:    :+:            */
/*                                                     +:+                    */
/*   By: tjans <marvin@codam.nl>                      +#+                     */
/*                                                   +#+                      */
/*   Created: 2019/10/29 10:43:11 by tjans         #+#    #+#                 */
/*   Updated: 2019/11/07 16:16:39 by tjans         ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

size_t	ft_strlcpy(char *dst, const char *src, size_t dstsize)
{
	size_t	src_size;

	src_size = 0;
	if (!src)
		return (0);
	if (!dstsize)
		return (ft_strlen(src));
	while (dstsize - 1 && src[src_size])
	{
		*dst = src[src_size];
		dstsize--;
		src_size++;
		dst++;
	}
	while (src[src_size])
		src_size++;
	*dst = '\0';
	return (src_size);
}
