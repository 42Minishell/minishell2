/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   debug_options.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tjans <tnjans@outlook.de>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/15 21:57:10 by tjans             #+#    #+#             */
/*   Updated: 2022/02/15 21:57:11 by tjans            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	parse_flags(int argc, char **argv, t_state *state)
{
	int	i;

	i = 1;
	while (i < argc)
	{
		if (strncmp("--tokenizer-debug", argv[i], 18) == 0)
			state->tokenizer_debug_mode = 1;
		else
			printf("Warning: Option %s not recognized\n", argv[i]);
		i++;
	}
}
