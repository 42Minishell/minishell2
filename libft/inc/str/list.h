/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   list.h                                             :+:    :+:            */
/*                                                     +:+                    */
/*   By: tjans <tjans@student.codam.nl>               +#+                     */
/*                                                   +#+                      */
/*   Created: 2019/11/25 16:24:17 by tjans         #+#    #+#                 */
/*   Updated: 2019/11/25 18:29:18 by tjans         ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#ifndef LIST_H
# define LIST_H
# include <stddef.h>

typedef struct s_strlist
{
	char				*str;
	struct s_strlist	*next;
}				t_strlist;

t_strlist		*strlist_create(char *str);
int				strlist_append(t_strlist *lst, char *str);
size_t			strlist_len(t_strlist *lst);
char			*strlist_join(t_strlist *lst);
void			strlist_free(t_strlist **lst);
#endif
