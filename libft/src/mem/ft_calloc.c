/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   ft_calloc.c                                        :+:    :+:            */
/*                                                     +:+                    */
/*   By: tjans <marvin@codam.nl>                      +#+                     */
/*                                                   +#+                      */
/*   Created: 2019/10/29 15:49:41 by tjans         #+#    #+#                 */
/*   Updated: 2022/02/16 19:14:45 by zgargasc      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include "libft.h"

void	*ft_calloc(size_t count, size_t size)
{
	unsigned char	*ptr;
	size_t			bytes;

	bytes = count * size;
	ptr = ft_malloc(bytes);
	ft_bzero(ptr, bytes);
	return ((void *)ptr);
}
