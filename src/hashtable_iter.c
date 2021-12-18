// Created by Tom Jans on 28-02-21.
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
			if (bucket->key && ft_strncmp(bucket->key, "", ft_strlen(bucket->key)) != 0)
				data = f(bucket->key, bucket->value, data);
			bucket = bucket->next;
		}
		i++;
	}
}
