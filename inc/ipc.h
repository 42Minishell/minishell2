/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ipc.h                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tjans <tnjans@outlook.de>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/18 17:27:47 by zgargasc      #+  #+#    #+#             */
/*   Updated: 2022/02/14 21:05:16 by tjans            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

/**
 * @file
 * IPC Helper functions, used for builtins
 *
 * IPC messages in minishell consist of a key and value part
 * @warning
 * When IPC communication is established it is mandatory to send a
 * END_IPC message at the end of the transaction, otherwise the internal state
 * of minishell might not be updated or get stuck in a loop of undefined
 * behaviour
 */

#ifndef IPC_H
# define IPC_H
# include <stdlib.h>
# include "minishell.h"

/**
 * @enum t_builtin_message_type
 * Type of the IPC Message sent.
 *
 * Based on the type the parent process will switch control paths and read
 * different variables
 */
typedef enum e_builtin_message_type
{
	ENV_ADD,
	ENV_DEL,
	CHDIR,
	EXIT,
	END_IPC
}	t_builtin_message_type;

/**
 * @struct t_builtin_message
 * IPC Message
 * @var t_builtin_message::type
 * Type of the message
 * @var t_builtin_message::key_len
 * Contains the length of the key string OR in the case when
 * t_builtin_message::type is EXIT it is used to store the exit code
 * @var t_builtin_message::value_len
 * Contains the length of the value string, or 0 in the case there is no string
 * sent.
 */
typedef struct s_builtin_message
{
	t_builtin_message_type	type;
	size_t					key_len;
	size_t					value_len;
}	t_builtin_message;

/**
 * @brief Read from IPC pipe and mutate state
 *
 * This function reads from the IPC pipe and mutates the state object based
 * on commands from the child process. It stops reading once the pipe is closed
 * or when END_IPC is received. Blocks!
 * @param fd Pipe/FD to read from
 * @param state State object of parent process
 * @return 0 on success, non-zero on failure
 */
int		receive_and_process_ipc(int fd, t_state *state);

/**
 * @brief This function sends an IPC message over the specified pipe
 *
 * It uses ft_strlen to check key and value size, value can be NULL
 * @param fd Pipe/FD to write to
 * @param type The message type
 * @param key Key, cannot be NULL
 * @param value Value
 */
void	send_ipc(int fd, t_builtin_message_type type, char *key, char *value);

/**
 * @brief This function sends an IPC message over the specified pipe
 *
 * This variation is for EXIT and END_IPC(value can be 0, is ignored)
 * @param fd Pipe/FD to write to
 * @param type The message type
 * @param value Integral value
 */
void	send_ipc_int(int fd, t_builtin_message_type type, int value);
#endif
