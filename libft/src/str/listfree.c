/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   listfree.c                                         :+:    :+:            */
/*                                                     +:+                    */
/*   By: tjans <tjans@student.codam.nl>               +#+                     */
/*                                                   +#+                      */
/*   Created: 2019/11/25 17:02:41 by tjans         #+#    #+#                 */
/*   Updated: 2019/11/25 19:13:27 by tjans         ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include "str/list.h"

void	strlist_free(t_strlist **lst)
{
	t_strlist	*next;

	next = (*lst)->next;
	if (next)
		strlist_free(&next);
	free((*lst)->str);
	free(*lst);
	*lst = NULL;
}
