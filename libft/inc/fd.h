/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   fd.h                                               :+:    :+:            */
/*                                                     +:+                    */
/*   By: tjans <tjans@student.codam.nl>               +#+                     */
/*                                                   +#+                      */
/*   Created: 2020/01/07 16:25:26 by tjans         #+#    #+#                 */
/*   Updated: 2020/01/07 17:16:33 by tjans         ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#ifndef FD_H
# define FD_H
# include <unistd.h>

typedef struct s_fdstream
{
	int		fd;
	char	buffer[512];
	ssize_t	b_read;
	ssize_t	b_pos;
}				t_fdstream;

t_fdstream		*fd_open(char *path, int oflag);
t_fdstream		*fd_openfd(int fd);
int				fd_readline(t_fdstream *file, char **line);
void			fd_close(t_fdstream *file);

#endif
