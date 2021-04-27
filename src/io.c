#include <fcntl.h>
#include <unistd.h>
#include "io.h"

static int	setup_redir_to_overwrite(t_token *redir, t_token *prev)
{
	int	fd;

	fd = open(redir->token, O_CREAT | O_WRONLY, 0666);
	if (fd < 0)
		return (0);
	prev->next = redir->next;
	free(redir);
	dup2(fd, 1);
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
	dup2(fd, 1);
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
	dup2(fd, 0);
	return (1);
}

int	io_setup(t_token *head)
{
	t_token			*head_prev;

	head_prev = head;
	head = head->next;
	while (head && head->type != executable)
	{
		if (head->type == redirect_to_overwrite)
			setup_redir_to_overwrite(head, head_prev);
		if (head->type == redirect_to_append)
			setup_redir_to_append(head, head_prev);
		if (head->type == redirect_from_file)
			setup_redir_from_file(head, head_prev);
		head_prev = head;
		head = head->next;
	}
	return (1);
}
