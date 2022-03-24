/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   config.h                                           :+:    :+:            */
/*                                                     +:+                    */
/*   By: zgargasc <zgargasc@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2021/12/18 17:27:43 by zgargasc      #+#    #+#                 */
/*   Updated: 2021/12/18 17:27:44 by zgargasc      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

// Created by Tom Jans on 28-02-21.

#ifndef CONFIG_H
# define CONFIG_H

# ifndef POPULATE_ENV
#  define POPULATE_ENV 1
# endif

/// Block size for dynamic reallocation of strings
# define TOK_ALLOC_BLK_SIZE 256

/**
 * Amount of buckets in the hashtable
 * Prime number is preferred because it causes less hash collisions with string
 * hashing algorithms
 */
# define HASHTABLE_SIZE 149

#endif
