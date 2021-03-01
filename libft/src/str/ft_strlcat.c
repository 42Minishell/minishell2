/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   strlcat.c                                          :+:    :+:            */
/*                                                     +:+                    */
/*   By: tjans <marvin@codam.nl>                      +#+                     */
/*                                                   +#+                      */
/*   Created: 2019/10/29 11:19:51 by tjans         #+#    #+#                 */
/*   Updated: 2019/11/07 16:16:43 by tjans         ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

size_t	ft_strlcat(char *dst, const char *src, size_t dstsize)
{
	size_t	dst_len;
	size_t	src_len;

	dst_len = ft_strlen(dst);
	src_len = ft_strlen(src);
	if (!dstsize || dstsize < dst_len)
		return (dst_len + src_len - (dst_len - dstsize));
	dstsize -= dst_len;
	ft_strlcpy(dst + dst_len, src, dstsize);
	return (dst_len + src_len);
}
