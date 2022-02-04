#include "libft.h"
#include "ipc.h"

static void mutate_state(t_state *state, t_builtin_message *ipc_msg, char *key, char *value)
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
	t_builtin_message ipc_msg;
	ssize_t recv_len;
	char key[255];
	char value[255];

	while (1) {
		recv_len = read(fd, &ipc_msg, sizeof(t_builtin_message));
		if (recv_len != sizeof(t_builtin_message))
			return 1;
		if (ipc_msg.type == RET_STATUS)
		{
			state->ret = (int)ipc_msg.key_len;
			env_update_envp(state->env);
			return 0;
		}
		recv_len = read(fd, key, ipc_msg.key_len);
		if (ipc_msg.value_len && recv_len)
			read(fd, value, ipc_msg.value_len);
		else
			*value = 0;
		mutate_state(state, &ipc_msg, key, value);
	}
}

void send_ipc(int fd, t_builtin_message_type type, char *key, char *value)
{
	t_builtin_message ipc_msg;

	ipc_msg.type = type;
	ipc_msg.key_len = ft_strlen(key);
	if (value)
		ipc_msg.value_len = ft_strlen(value);
	else
		ipc_msg.value_len = 0;
	write(fd, &ipc_msg, sizeof(t_builtin_message));
	write(fd, key, ft_strlen(key));
	if (value)
		write(fd, value, ft_strlen(value));
}
