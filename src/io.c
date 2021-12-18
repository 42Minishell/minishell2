#include <fcntl.h>
#include <unistd.h>
#include "io.h"

//TODO: Refactor
// TODO: PROTECT SYSTEM CALLS DUP


static int	setup_redir_to_overwrite(t_token *redir, t_token *prev)
{
	int	fd;

	fd = open(redir->token, O_CREAT | O_WRONLY, 0666);
	if (fd < 0)
		return (0);
	prev->next = redir->next;
	free(redir);
	if (dup2(fd, 1) == -1)
		return (0);
	return (1);
}

static int	setup_redir_to_append(t_token *redir, t_token *prev)
{
	int	fd;

	fd = open(redir->token, O_CREAT | O_WRONLY | O_APPEND, 0666);
	if (fd < 0)
		return (0);
	prev->next = redir->next;
	free(redir);
	if (dup2(fd, 1) == -1)
		return(0);
	return (1);
}

static int	setup_redir_from_file(t_token *redir, t_token *prev)
{
	int	fd;

	fd = open(redir->token, O_RDONLY);
	if (fd < 0)
		return (0);
	prev->next = redir->next;
	free(redir);
	if (dup2(fd, 0) == -1)
		return(0);
	return (1);
}

int	io_setup(t_token *head)
{
	t_token			*head_prev;
	int				res;

	res = 1;
	head_prev = head;
	head = head->next;
	while (head && head->type != executable)
	{
		if (head->type == redirect_to_overwrite)
			res = setup_redir_to_overwrite(head, head_prev);
		if (head->type == redirect_to_append)
			res = setup_redir_to_append(head, head_prev);
		if (head->type == redirect_from_file)
			res = setup_redir_from_file(head, head_prev);
		head_prev = head;
		head = head->next;
	}
	return (res);
}
