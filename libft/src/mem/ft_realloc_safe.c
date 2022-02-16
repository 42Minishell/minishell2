/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   ft_realloc_safe.c                                  :+:    :+:            */
/*                                                     +:+                    */
/*   By: tjans <tjans@student.codam.nl>               +#+                     */
/*                                                   +#+                      */
/*   Created: 2020/01/07 16:48:20 by tjans         #+#    #+#                 */
/*   Updated: 2022/02/16 19:00:08 by zgargasc      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include "libft.h"

void	*ft_realloc_safe(void *ptr, size_t old_size, size_t new_size)
{
	size_t	i;
	char	*newptr;

	i = 0;
	if (ptr == NULL)
		return (ft_malloc(new_size));
	newptr = ft_malloc(new_size);
	while (i < old_size)
	{
		newptr[i] = ((char *)ptr)[i];
		i++;
	}
	free(ptr);
	return (newptr);
}
