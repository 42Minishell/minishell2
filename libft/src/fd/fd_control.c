/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   fd_control.c                                       :+:    :+:            */
/*                                                     +:+                    */
/*   By: tjans <tjans@student.codam.nl>               +#+                     */
/*                                                   +#+                      */
/*   Created: 2020/01/07 16:42:38 by tjans         #+#    #+#                 */
/*   Updated: 2020/01/07 17:17:27 by tjans         ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include <fcntl.h>
#include "libft.h"

t_fdstream	*fd_open(char *path, int oflag)
{
	t_fdstream	*file;
	int			fd;

	fd = open(path, oflag);
	if (!fd)
		return (NULL);
	file = ft_calloc(1, sizeof(t_fdstream));
	if (!file)
	{
		close(fd);
		return (NULL);
	}
	file->fd = fd;
	return (file);
}

t_fdstream	*fd_openfd(int fd)
{
	t_fdstream	*file;

	file = ft_calloc(1, sizeof(t_fdstream));
	if (!file)
		return (NULL);
	file->fd = fd;
	return (file);
}

void	fd_close(t_fdstream *file)
{
	close(file->fd);
}
