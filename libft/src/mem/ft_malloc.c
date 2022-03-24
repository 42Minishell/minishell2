/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_malloc.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tjans <tnjans@outlook.de>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/24 11:33:20 by tjans             #+#    #+#             */
/*   Updated: 2022/03/24 11:33:22 by tjans            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include "libft.h"

void	*ft_malloc(size_t size)
{
	void	*new;

	new = malloc(size);
	if (!new)
	{
		write(2, "Memory allocation went wrong\n", 30);
		exit(1);
	}
	return (new);
}
