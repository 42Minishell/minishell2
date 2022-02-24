/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   io.h                                               :+:    :+:            */
/*                                                     +:+                    */
/*   By: zgargasc <zgargasc@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2021/12/18 17:27:48 by zgargasc      #+#    #+#                 */
/*   Updated: 2022/02/16 19:10:01 by zgargasc      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#ifndef IO_H
# define IO_H
# include "minishell.h"

int		io_setup(t_token *list);

/// Our protected malloc function.
void	*ft_malloc(size_t size);

#endif
