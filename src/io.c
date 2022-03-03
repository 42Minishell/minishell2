/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   io.c                                               :+:    :+:            */
/*                                                     +:+                    */
/*   By: zinobias <zinobias@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2021/12/18 17:11:08 by zinobias      #+#    #+#                 */
/*   Updated: 2021/12/18 17:19:49 by zgargasc      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include <fcntl.h>
#include <unistd.h>
#include "io.h"

static int	setup_redir_to_overwrite(t_token *redir)
{
	int	fd;

	fd = open(redir->token, O_CREAT | O_WRONLY | O_TRUNC, 0666);
	if (fd < 0)
		return (0);
	if (dup2(fd, 1) == -1)
		return (0);
	return (1);
}

static int	setup_redir_to_append(t_token *redir)
{
	int	fd;

	fd = open(redir->token, O_CREAT | O_WRONLY | O_APPEND, 0666);
	if (fd < 0)
		return (0);
	if (dup2(fd, 1) == -1)
		return (0);
	return (1);
}

static int	setup_redir_from_file(t_token *redir)
{
	int	fd;

	fd = open(redir->token, O_RDONLY);
	if (fd < 0)
		return (0);
	if (dup2(fd, 0) == -1)
		return (0);
	return (1);
}

static int	setup_redir(t_token *head)
{
	int	res;

	res = 1;
	if (head->type == redirect_to_overwrite)
		res = setup_redir_to_overwrite(head);
	if (head->type == redirect_to_append)
		res = setup_redir_to_append(head);
	if (head->type == redirect_from_file || \
		head->type == redirect_from_file_and_unlink)
		res = setup_redir_from_file(head);
	return (res);
}

int	io_setup(t_token *head)
{
	int		res;
	t_token	*iterator;

	res = 1;
	iterator = head;
	while (iterator->prev && iterator->prev->type != redirect_to_pipe && \
		iterator->prev->type != executable)
	{
		res = setup_redir(iterator);
		iterator = iterator->prev;
	}
	iterator = head->next;
	while (iterator && iterator->type != executable && iterator->type != \
		redirect_to_pipe)
	{
		res = setup_redir(head);
		head = head->next;
	}
	return (res);
}
