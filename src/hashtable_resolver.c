/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   hashtable_resolver.c                               :+:    :+:            */
/*                                                     +:+                    */
/*   By: zgargasc <zgargasc@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2021/12/18 17:12:32 by zgargasc      #+#    #+#                 */
/*   Updated: 2021/12/18 17:12:33 by zgargasc      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

// Created by Tom Jans on 28-02-21.

#include "hashtable.h"
#include "minishell.h"

unsigned long	hash(char *str)
{
	unsigned long	hash;

	hash = 0;
	while (*str)
	{
		hash += *str;
		str++;
	}
	return (hash % HASHTABLE_SIZE);
}

static t_bucket	*bucket_get_overflow(t_bucket *bucket, char *key, int create)
{
	while (bucket)
	{
		if (bucket->key
			&& ft_strncmp(bucket->key, key, ft_strlen(bucket->key)) == 0)
		{
			if (create)
				free(key);
			return (bucket);
		}
		if (!bucket->next && create)
		{
			bucket->next = ft_calloc(1, sizeof(t_bucket));
			if (bucket->next == NULL)
				ft_error("ft_calloc bucket went wrong", 28);
			bucket = bucket->next;
			bucket->key = key;
			return (bucket);
		}
		bucket = bucket->next;
	}
	return (NULL);
}

t_bucket	*bucket_get(t_bucket *table, char *key, int create)
{
	unsigned long	keyhash;
	t_bucket		*bucket;

	if (key == NULL)
		ft_error("strdup, bucket key error", 25);
	keyhash = hash(key);
	bucket = table + keyhash;
	if (bucket->key || bucket->next)
		return (bucket_get_overflow(bucket, key, create));
	else if (create)
	{
		bucket->key = key;
		return (bucket);
	}
	return (NULL);
}

char	*bucket_get_value(t_bucket *table, char *key)
{
	t_bucket	*bucket;

	bucket = bucket_get(table, key, 0);
	if (!bucket)
		return (NULL);
	return (bucket->value);
}
