/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   ft_strjoin.c                                       :+:    :+:            */
/*                                                     +:+                    */
/*   By: tjans <marvin@codam.nl>                      +#+                     */
/*                                                   +#+                      */
/*   Created: 2019/10/29 18:49:00 by tjans         #+#    #+#                 */
/*   Updated: 2022/02/16 19:16:35 by zgargasc      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include "libft.h"

char	*ft_strjoin(char const *s1, char const *s2)
{
	size_t	str_size;
	char	*jstr;

	if (!s1 || !s2)
		return (NULL);
	str_size = ft_strlen(s1);
	str_size += ft_strlen(s2);
	str_size++;
	jstr = ft_malloc(sizeof(char) * str_size);
	ft_strlcpy(jstr, s1, str_size);
	ft_strlcat(jstr, s2, str_size);
	return (jstr);
}
