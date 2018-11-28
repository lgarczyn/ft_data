/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tructs                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lgarczyn <lgarczyn@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2014/11/07 16:18:53 by lgarczyn          #+#    #+#             */
/*   Updated: 2018/10/10 23:48:46 by lgarczyn         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef _STRUCTS_H
# define _STRUCTS_H

# include <stdlib.h>
# include <stdbool.h>
# include "libft.h"

typedef struct	s_array
{
	void		*data;
	size_t		pos;
	size_t		size;
	size_t		warning;
}				t_array;

typedef struct	s_bitset
{
	t_uchar		*data;
	size_t		pos;
	size_t		size;
}				t_bitset;

typedef struct	s_queue
{
	void		*data;
	size_t		pos;
	size_t		start;
	size_t		size;
	t_uint		word;
}				t_queue;

typedef int		(*t_predicate)(const void *a, const void *b);
typedef void	(*t_printer)(const void *p);

typedef struct	s_sorted
{
	void		*data;
	t_uint		word;
	size_t		size;
	size_t		pos;
	t_predicate	predicate;
}				t_sorted;

typedef struct	s_sorteden
{
	size_t		index;
	bool		found;
}				t_sorteden;

typedef struct	s_sizes
{
	t_uint		key;
	t_uint		val;
}				t_sizes;

typedef struct	s_bucket
{
	t_bitset	flags;
	t_array		values;
	t_sizes		sizes;
	size_t		count;
}				t_bucket;

typedef struct	s_pma
{
	t_predicate	predicate;
	t_bucket	bucket;
	size_t		canary:63;
	bool		multi:1;
}				t_pma;

typedef struct	s_pmait
{
	t_pma		*pma;
	size_t		id;
	size_t		end;
	size_t		canary;
}				t_pmait;

typedef struct	s_pmaen
{
	t_pmait		it;
	const void	*key;
	bool		found;
}				t_pmaen;

#endif
