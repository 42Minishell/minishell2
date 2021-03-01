/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   listcreate.c                                       :+:    :+:            */
/*                                                     +:+                    */
/*   By: tjans <tjans@student.codam.nl>               +#+                     */
/*                                                   +#+                      */
/*   Created: 2019/11/25 16:40:59 by tjans         #+#    #+#                 */
/*   Updated: 2019/11/25 16:51:23 by tjans         ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include "str/list.h"

t_strlist	*strlist_create(char *str)
{
	t_strlist	*lst;

	lst = malloc(sizeof(t_strlist));
	if (!lst || !str)
		return (NULL);
	lst->str = str;
	lst->next = NULL;
	return (lst);
}
