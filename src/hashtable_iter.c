/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   hashtable_iter.c                                   :+:    :+:            */
/*                                                     +:+                    */
/*   By: zgargasc <zgargasc@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2021/12/18 17:12:31 by zgargasc      #+#    #+#                 */
/*   Updated: 2021/12/18 17:19:02 by zgargasc      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

// Created by Tom Jans on 28-02-21.
#include "libft.h"
#include "hashtable.h"

void	bucket_iter(t_bucket *table, t_bucket_iterator f, void *data)
{
	int			i;
	t_bucket	*bucket;

	i = 0;
	while (i < HASHTABLE_SIZE)
	{
		bucket = table + i;
		while (bucket)
		{
			if (bucket->key && ft_strncmp(bucket->key, "", \
					ft_strlen(bucket->key)) != 0)
				data = f(bucket->key, bucket->value, data);
			bucket = bucket->next;
		}
		i++;
	}
}
