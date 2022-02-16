/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   hashtable.h                                        :+:    :+:            */
/*                                                     +:+                    */
/*   By: zgargasc <zgargasc@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2021/12/18 17:27:45 by zgargasc      #+#    #+#                 */
/*   Updated: 2022/02/16 19:09:57 by zgargasc      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

// Created by Tom Jans on 27-02-21.

/**
 * @file
 * Implementation of a hash table
 *
 * The hash table is implemented with the t_bucket structure
 *
 * This is initialized by creating one array of empty buckets with memory
 * allocation. When a key needs to be stored an internal hashing feature is
 * called and this decides at which index the key and value is placed.
 *
 * In the case there is an conflict the buckets also have a pointer to the
 * next one so multiple keys can be stored in a linked list of buckets
 * in a single index.
 *
 * The size of the hashtable has been fixed to 64, in testing with real world
 * environment variables this value has given me the best tradeoff between
 * memory footprint and conflicts.
 *
 * In the best case with +-25 variables in the table you only have 2-3
 * conflicts, which means the majority of the env can be looked up with a
 * single call to the hash function and a single call to strcmp
 */
#ifndef HASHTABLE_H
# define HASHTABLE_H
# define HASHTABLE_SIZE 64
# include <stdlib.h>
# include <string.h>

/**
 * @struct t_bucket
 * Hash table object
 *
 * @var t_bucket::key
 * Key
 * @var t_bucket::value
 * Value
 * @var t_bucket::next
 * Pointer to the overflow bucket(s) in case of conflicts
 */
typedef struct s_bucket {
	char			*key;
	char			*value;
	struct s_bucket	*next;
}	t_bucket;

/**
 * @typedef t_bucket_iterator
 * @brief Interface for the bucket iterator
 *
 * This defines the interface of functions you can pass to bucket_iter(),
 * currently this is only used for generating envp in env_update_envp()
 * @param[in] key
 * Current key
 * @param[in] val
 * Current value
 * @param[out] data
 * Pointer to where the data should be written
 * @return
 * New pointer to pass as data to the next iteration
 */
typedef void	*(*t_bucket_iterator)(char *key, char *val, void *data);

/// Generate new hash table with the amount of elements as defined in
/// HASHTABLE_SIZE
t_bucket	*bucket_new_table(void);
/**
 * @warning
 * ft_strdup() is used to copy key and value. The original strings input into
 * this function still need to be freed at some point.
 * Add key,value entry to the hashtable
 * @param[in] table Table to write to
 * @param[in] key Key
 * @param[in] val Value
 */
void		bucket_add(t_bucket *table, char *key, char *val);
/**
 * @brief Deletes key,value entry from the hashtable
 *
 * To keep the code simple bucket_del frees the strings and replaces the key
 * with an empty string, so we do not have to regenerate the overflow buckets.
 * @param[in] table Table to write to
 * @param[in] key Key to remove
 */
void		bucket_del(t_bucket *table, char *key);
/**
 * Frees hashtable and cleans up everything in memory
 * @param[in] table Table to clear
 */
void		bucket_free_table(t_bucket *table);
/**
 * Internal function to get and/or create a bucket
 * @warning Do not use outside the hashtable implementation, if you want to
 * get a single value use bucket_get_value()
 * @param[in] table Table to read/write in
 * @param[in] key Key to lookup or create
 * @param[in] create boolean, when not 0 it creates a new key if the key is
 * not found
 * @return pointer to the bucket for the key, if create == 0 and key is not
 * found return NULL
 */
t_bucket	*bucket_get(t_bucket *table, char *key, int create);
/**
 * Get value from bucket
 * @param[in] table Table to read from
 * @param[in] key Key to find
 * @return NULL if not found, otherwise pointer to the value
 * @warning The pointer to the value is not a copy of the string, in no
 * circumstance free the returned value!
 */
char		*bucket_get_value(t_bucket *table, char *key);
/**
 * @brief Iterate through all elements in the hash table
 *
 * The order is completely semi-random according to to the hash function
 * used, do not assume it is alphabetically or fifo ordered
 * @param[in] table Table to iterate on
 * @param[in] f Function to call on each iteration
 * @param[out] data Pointer to pass to f
 */
void		bucket_iter(t_bucket *table, t_bucket_iterator f, void *data);

/// Our protected malloc function.
void	*ft_malloc(size_t size);
#endif
