/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   prompt.c                                           :+:    :+:            */
/*                                                     +:+                    */
/*   By: zgargasc <zgargasc@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2021/12/18 17:13:58 by zgargasc      #+#    #+#                 */
/*   Updated: 2022/03/23 20:40:10 by zgargasc      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

// Created by Tom Jans on 01-03-21.

#include <stdio.h>
#include "minishell.h"
#include "config.h"

char	*prompt(t_state *state)
{
	char	*input;

	(void)state;
	input = readline(PROMPT);
	if (!input)
	{
		printf("\n");
		exit(0);
	}
	if (*input)
		add_history(input);
	return (input);
}
