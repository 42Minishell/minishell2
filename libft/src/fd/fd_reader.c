/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   fd_reader.c                                        :+:    :+:            */
/*                                                     +:+                    */
/*   By: tjans <tjans@student.codam.nl>               +#+                     */
/*                                                   +#+                      */
/*   Created: 2020/01/07 16:20:35 by tjans         #+#    #+#                 */
/*   Updated: 2020/01/07 17:31:03 by tjans         ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include "libft.h"

static int	read_buffer(t_fdstream *file)
{
	if (file->b_pos < file->b_read && file->b_read != 0)
		return (1);
	file->b_read = read(file->fd, file->buffer, 512);
	if (file->b_read > 0)
		file->b_pos = 0;
	return (file->b_read > 0);
}

static int	extend_lb(char **line, size_t *lb_size)
{
	*line = ft_realloc_safe(*line, *lb_size, *lb_size * 2);
	*lb_size = *lb_size * 2;
	return (*line != NULL);
}

static int	find_line(t_fdstream *file, char **line)
{
	size_t	lb_size;
	size_t	i;

	lb_size = 512;
	i = 0;
	if (file->b_pos >= file->b_read && file->b_read > 0)
		read_buffer(file);
	while (file->b_pos < file->b_read)
	{
		if (file->buffer[file->b_pos] == '\n')
		{
			(*line)[i] = '\0';
			file->b_pos++;
			return (1);
		}
		(*line)[i] = file->buffer[file->b_pos];
		i++;
		file->b_pos++;
		if (i >= lb_size && !extend_lb(line, &lb_size))
			return (-1);
		if (file->b_read != 0 && file->b_pos == file->b_read)
			read_buffer(file);
	}
	(*line)[i] = '\0';
	return (0);
}

int	fd_readline(t_fdstream *file, char **line)
{
	int	ret;

	ret = 0;
	*line = ft_calloc(1, 512);
	if (!*line)
		return (-1);
	read_buffer(file);
	ret = find_line(file, line);
	if (file->b_read < 0)
	{
		ret = -1;
		free(*line);
	}
	return (ret);
}
