/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   ft_split.c                                         :+:    :+:            */
/*                                                     +:+                    */
/*   By: tjans <marvin@codam.nl>                      +#+                     */
/*                                                   +#+                      */
/*   Created: 2019/10/29 20:25:40 by tjans         #+#    #+#                 */
/*   Updated: 2022/02/16 19:16:25 by zgargasc      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include "libft.h"

static size_t	calc_arr_size(char const *s, char c)
{
	size_t	cnt;

	cnt = 1;
	while (*s)
	{
		if (*s == c)
		{
			while (*s && *s == c)
				s++;
			if (s)
				cnt++;
		}
		s++;
	}
	return (cnt);
}

static char	*get_next_str(char const **s, char c)
{
	char	*str;
	char	*newstr;
	size_t	ns_len;
	size_t	ns_pos;

	str = (char *)*s;
	ns_len = 0;
	while (str[ns_len] && str[ns_len] != c)
		ns_len++;
	ns_pos = 0;
	newstr = ft_malloc(sizeof(char) * ns_len + 1);
	while (ns_pos < ns_len)
	{
		newstr[ns_pos] = *str;
		str++;
		ns_pos++;
	}
	newstr[ns_pos] = '\0';
	while (*str && *str == c)
		str++;
	*s = str;
	return (newstr);
}

static void	clean_mem(char ***arr)
{
	size_t	index;

	index = 0;
	while ((*arr)[index])
	{
		free((*arr)[index]);
		index++;
	}
	free(*arr);
}

char	**ft_split(char const *s, char c)
{
	char	**arr;
	size_t	arr_size;
	size_t	arr_index;

	if (!s)
		return (NULL);
	while (*s == c && *s)
		s++;
	arr_index = 0;
	arr_size = calc_arr_size(s, c);
	arr = ft_malloc(sizeof(char *) * (arr_size + 1));
	while (arr_index < arr_size && *s)
	{
		arr[arr_index] = get_next_str(&s, c);
		if (arr[arr_index] == NULL)
		{
			clean_mem(&arr);
			return (NULL);
		}
		arr_index++;
	}
	arr[arr_index] = (char *) NULL;
	return (arr);
}
