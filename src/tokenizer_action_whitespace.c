/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tokenizer_action_whitespace.c                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tjans <tnjans@outlook.de>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/16 11:49:46 by tjans             #+#    #+#             */
/*   Updated: 2022/02/16 11:49:51 by tjans            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "tokenizer.h"

int	lexer_action_whitespace(t_token **dst, char **in)
{
	(void)dst;
	while (**in && **in == ' ')
		(*in)++;
	return (0);
}
