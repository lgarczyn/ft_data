/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   data.h                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lgarczyn <lgarczyn@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2014/11/07 16:18:53 by lgarczyn          #+#    #+#             */
/*   Updated: 2018/03/28 23:47:55 by lgarczyn         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef _DATA_H
# define _DATA_H

# include <stdlib.h>
# include <stdbool.h>

typedef uint32_t	t_uint;

typedef struct		s_array
{
	void			*data;
	size_t			pos;
	size_t			size;
}					t_array;

typedef struct		s_bitmap
{
	char			*data;
	size_t			pos;
	size_t			size;
}					t_bitmap;

typedef struct		s_queue
{
	void			*data;
	size_t			pos;
	size_t			start;
	size_t			size;
	size_t			word;
}					t_queue;

typedef int			(*t_predicate)(const void *a, const void *b);

typedef struct		s_sorted
{
	void			*data;
	size_t			word;
	size_t			size;
	size_t			pos;
	t_predicate		predicate;
}					t_sorted;

typedef struct		s_searchres
{
	size_t			index;
	bool			found;
}					t_searchres;

typedef struct		s_branch
{
	t_uint			size;
	t_uint			pos;
	void			*data;
}					t_branch;

typedef struct		s_sizes
{
	t_uint			key;
	t_uint			val;
	t_uint			word;
	t_uint			bucket;
}					t_sizes;

typedef struct		s_btree
{
	size_t			count;
	t_sizes			sizes;
	t_branch		root;
}					t_btree;

typedef struct		s_branch_it
{
	t_branch		*branch;
	t_uint			pos;
}					t_branch_it;

typedef struct		s_btree_it
{
	t_btree			*tree;
	void			*key;
	void			*data;
	t_uint			pos;
	t_branch_it		iterators[6];
	bool			end;
}					t_btree_it;

typedef struct		s_btree_en
{
	t_btree_it		it;
	char			*key;
}					t_btree_en;

t_array				array(void);
void				array_free(t_array *a);
size_t				array_len(const t_array *a, size_t word);
int					array_push(t_array *a, const void *data, size_t size);
int					array_pop(t_array *a, void *data, size_t size);
int					array_reserve(t_array *a, size_t s);

t_bitmap			bitmap(void);
void				bitmap_free(t_bitmap *a);
int					bitmap_realloc(t_bitmap *bitmap, size_t new_size);
int					bitmap_push(t_bitmap *a, bool b);
int					bitmap_pop(t_bitmap *a, bool *data);
bool				bitmap_get(const t_bitmap *a, size_t i);
int					bitmap_get_safe(const t_bitmap *a, size_t i, bool *out);

t_queue				queue(size_t word);
void				queue_free(t_queue *a);
size_t				queue_len(const t_queue *a);
int					queue_push_back(t_queue *a, const void *data);
int					queue_push_front(t_queue *a, const void *data);
int					queue_pop_back(t_queue *a, void *data);
int					queue_pop_front(t_queue *a, void *data);
int					queue_reserve(t_queue *a, size_t s);

t_sorted			sorted(t_predicate predicate, size_t word);
void				sorted_free(t_sorted *a);
void				*sorted_get(t_sorted *a, size_t index);
const void			*sorted_cget(const t_sorted *a, size_t index);
t_searchres			sorted_search_range(
	const t_sorted *a, const void *ptr, size_t start, size_t end);
t_searchres			sorted_search(const t_sorted *a, const void *d);
int					sorted_insert_hint(t_sorted *a, const void *d, size_t h);
int					sorted_insert(t_sorted *a, const void *data);
t_searchres			sorted_replace(t_sorted *a, void *data);
t_searchres			sorted_replace_hint(t_sorted *a, void *data, size_t hint);
void				sorted_delete_index(t_sorted *a, size_t index, void *out);
t_searchres			sorted_delete(t_sorted *a, const void *data, void *out);
int					sorted_pop(t_sorted *a, void *data);
int					sorted_reserve(t_sorted *a, size_t s);
size_t				sorted_len(const t_sorted *a);

t_btree				btree(t_predicate predicate, t_uint key, t_uint value);
void				btree_free(t_btree *a);
t_btree_en			btree_search(const t_btree *a, const void *key);
t_btree_en			btree_delete(t_btree *a, const void *key, void *out);
bool				btree_insert(t_btree *a, const void *key, const void *data);
bool				btree_replace(t_btree *a, const void *key, void *data);
size_t				btree_len(const t_btree *a);

bool				btree_get(const t_btree_it *i, void *data, void *key);
bool				btree_next(t_btree_it *i, void *data, void *key);
bool				btree_prev(t_btree_it *i, void *data, void *key);

t_btree_it			btree_ensure(t_btree_en res, void *data);
bool				btree_delete_it(t_btree_it *i, void *out);

#endif
