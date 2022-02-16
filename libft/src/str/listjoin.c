/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   listjoin.c                                         :+:    :+:            */
/*                                                     +:+                    */
/*   By: tjans <tjans@student.codam.nl>               +#+                     */
/*                                                   +#+                      */
/*   Created: 2019/11/25 16:53:53 by tjans         #+#    #+#                 */
/*   Updated: 2022/02/16 19:16:56 by zgargasc      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include "libft.h"

char	*strlist_join(t_strlist *lst)
{
	char	*str;
	size_t	str_len;

	str_len = strlist_len(lst) + 1;
	str = ft_malloc(sizeof(char) * str_len);
	ft_strlcpy(str, lst->str, str_len);
	while (lst->next)
	{
		lst = lst->next;
		ft_strlcat(str, lst->str, str_len);
	}
	return (str);
}
