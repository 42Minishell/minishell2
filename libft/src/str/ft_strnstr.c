/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   ft_strnstr.c                                       :+:    :+:            */
/*                                                     +:+                    */
/*   By: tjans <marvin@codam.nl>                      +#+                     */
/*                                                   +#+                      */
/*   Created: 2019/10/29 12:40:14 by tjans         #+#    #+#                 */
/*   Updated: 2021/12/18 17:26:19 by zgargasc      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strnstr(const char *haystack, const char *needle, size_t len)
{
	size_t	haystack_pos;
	size_t	needle_pos;

	haystack_pos = 0;
	if (!*needle)
		return ((char *)haystack);
	while (haystack[haystack_pos] && haystack_pos < len)
	{
		needle_pos = 0;
		while (haystack[haystack_pos + needle_pos] == needle[needle_pos]
			&& haystack_pos + needle_pos < len)
		{
			needle_pos++;
			if (!needle[needle_pos])
				return ((char *)haystack + haystack_pos);
		}
		haystack_pos++;
	}
	return (NULL);
}
