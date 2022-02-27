/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   ipc.c                                              :+:    :+:            */
/*                                                     +:+                    */
/*   By: tjans <tnjans@outlook.de>                    +#+                     */
/*                                                   +#+                      */
/*   Created: 2021/12/18 17:13:36 by tjans         #+#    #+#                 */
/*   Updated: 2022/02/23 20:03:21 by zgargasc      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include "ipc.h"

static void	mutate_state(t_state *state, t_builtin_message *ipc_msg, char *key,
						char *value)
{
	if (ipc_msg->type == ENV_ADD)
		bucket_add(state->env->env, key, value);
	if (ipc_msg->type == ENV_DEL)
		bucket_del(state->env->env, key);
	if (ipc_msg->type == CHDIR)
		chdir(key);
}

int	receive_and_process_ipc(int fd, t_state *state)
{
	t_builtin_message	ipc_msg;
	ssize_t				recv_len;
	char				key[4096];
	char				value[4096];

	while (1)
	{
		recv_len = read(fd, &ipc_msg, sizeof(t_builtin_message));
		if (recv_len != sizeof(t_builtin_message))
			return (1);
		if (ipc_msg.type == END_IPC)
		{
			env_update_envp(state->env);
			return (0);
		}
		if (ipc_msg.type == EXIT)
			exit((int)ipc_msg.key_len);
		recv_len = read(fd, key, ipc_msg.key_len);
		if (ipc_msg.value_len && recv_len)
			read(fd, value, ipc_msg.value_len);
		else
			*value = 0;
		mutate_state(state, &ipc_msg, key, value);
	}
}

void	send_ipc(int fd, t_builtin_message_type type, char *key, char *value)
{
	t_builtin_message	ipc_msg;

	ipc_msg.type = type;
	ipc_msg.key_len = ft_strlen(key) + 1;
	if (value)
		ipc_msg.value_len = ft_strlen(value) + 1;
	else
		ipc_msg.value_len = 0;
	if (ipc_msg.key_len > 4096 || ipc_msg.value_len > 4096)
	{
		printf("IPC Error: Message too long!\n");
		return ;
	}
	write(fd, &ipc_msg, sizeof(t_builtin_message));
	write(fd, key, ft_strlen(key) + 1);
	if (value)
		write(fd, value, ft_strlen(value) + 1);
}

void	send_ipc_int(int fd, t_builtin_message_type type, int value)
{
	t_builtin_message	ipc_msg;

	ipc_msg.type = type;
	ipc_msg.key_len = value;
	ipc_msg.value_len = 0;
	write(fd, &ipc_msg, sizeof(t_builtin_message));
}
