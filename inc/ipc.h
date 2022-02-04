#ifndef IPC_H
# define IPC_H
# include <stdlib.h>
# include "minishell.h"

typedef enum e_builtin_message_type
{
	ENV_ADD,
	ENV_DEL,
	CHDIR,
	EXIT,
	END_IPC
}	t_builtin_message_type;

typedef struct s_builtin_message
{
	t_builtin_message_type	type;
	size_t					key_len;
	size_t					value_len;
}	t_builtin_message;

int	receive_and_process_ipc(int fd, t_state *state);
void send_ipc(int fd, t_builtin_message_type type, char *key, char *value);
void send_ipc_int(int fd, t_builtin_message_type type, int value);
#endif
