/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   utils.c                                            :+:    :+:            */
/*                                                     +:+                    */
/*   By: zgargasc <zgargasc@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/02/16 19:11:30 by zgargasc      #+#    #+#                 */
/*   Updated: 2022/02/16 19:20:34 by zgargasc      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include "tokenizer.h"

void	*ft_malloc(size_t size)
{
	void	*new;

	new = malloc(size);
	if (!new)
		ft_error("Memory allocation went wrong", 29);
	return (new);
}
