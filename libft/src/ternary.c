/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   ternary.c                                          :+:    :+:            */
/*                                                     +:+                    */
/*   By: zgargasc <zgargasc@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2021/12/18 17:26:39 by zgargasc      #+#    #+#                 */
/*   Updated: 2021/12/18 17:26:40 by zgargasc      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ternary_i(int condition, int ret_true, int ret_false)
{
	if (condition)
		return (ret_true);
	return (ret_false);
}
