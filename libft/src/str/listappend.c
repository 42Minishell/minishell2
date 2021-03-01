/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   listappend.c                                       :+:    :+:            */
/*                                                     +:+                    */
/*   By: tjans <tjans@student.codam.nl>               +#+                     */
/*                                                   +#+                      */
/*   Created: 2019/11/25 16:44:24 by tjans         #+#    #+#                 */
/*   Updated: 2019/11/25 16:46:53 by tjans         ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "str/list.h"

int	strlist_append(t_strlist *lst, char *str)
{
	if (!lst)
		return (0);
	while (lst->next)
		lst = lst->next;
	lst->next = strlist_create(str);
	return (lst->next != NULL);
}
