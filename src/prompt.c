/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   prompt.c                                           :+:    :+:            */
/*                                                     +:+                    */
/*   By: zgargasc <zgargasc@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2021/12/18 17:13:58 by zgargasc      #+#    #+#                 */
/*   Updated: 2021/12/18 17:13:59 by zgargasc      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

// Created by Tom Jans on 01-03-21.

#include "minishell.h"

char	*prompt(t_state *state)
{
	char	*input;

	(void)state;
	input = readline("MS > ");
	if (!input)
	{
		printf("\n");
		exit(0);
	}
	if (*input)
		add_history(input);
	return (input);
}
