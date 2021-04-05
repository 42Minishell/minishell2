#include <sys/stat.h>
#include <fcntl.h>
#include <stdio.h>

#include "libft.h"
#include "tests.h"
#include "hashtable.h"

static int	find_testdata(char *dst)
{
	struct stat	statbuf;

	if (stat("dummy.txt", &statbuf) == 0)
		ft_strlcpy(dst, "dummy.txt", 255);
	else if (stat("../dummy.txt", &statbuf) == 0)
		ft_strlcpy(dst, "../dummy.txt", 255);
	else if (stat("../test/dummy.txt", &statbuf) == 0)
		ft_strlcpy(dst, "../test/dummy.txt", 255);
	else
		return (0);
	return (1);
}

static void	add_env(char *argv, t_bucket *bucket)
{
	char	**split;
	void	*sfree;
	char	*key;
	char	*value;

	split = ft_split(argv, '=');
	if (split[1])
	{
		key = split[0];
		value = split[1];
		bucket_add(bucket, key, value);
	}
	sfree = split;
	while (*split)
	{
		split++;
		free(*(split - 1));
	}
	free(sfree);
}

static void	ht_tests(t_fdstream *fd, char *path, t_bucket *table)
{
	char		*line;
	char		key[64];
	char		*val;

	while (fd_readline(fd, &line))
	{
		add_env(line, table);
		free(line);
	}
	fd_close(fd);
	free(line);
	free(fd);
	fd = fd_open(path, O_RDONLY);
	while (fd_readline(fd, &line))
	{
		ft_strlcpy(key, line, ft_strclen(line, '=') + 1);
		val = bucket_get_value(table, key);
		uassert((val != NULL), "Key not found");
		if (val != NULL)
			uassert((strncmp(val, "test1234merpmerp", 17) == 0),
				"value not correct");
		free(line);
	}
	free(line);
	free(fd);
}

void	test_hashtable(void)
{
	char		path[255];
	t_bucket	*table;

	uassert((find_testdata(path) == 1), "Test data could not be found.");
	table = bucket_new_table();
	uassert((table != NULL), "bucket_new_table returned NULL.");
	ht_tests(fd_open(path, O_RDONLY), path, table);
	bucket_free_table(table);
}
