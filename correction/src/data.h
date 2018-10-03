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

typedef struct		s_bucket
{
	t_bitmap		occ;
	t_array			values;
}					t_bucket;

typedef struct		s_pma
{
	t_uint			key_size;
	t_uint			value_size;
	size_t			count;
	t_predicate		predicate;
	t_bucket		bucket;
	//t_array			data;
}					t_pma;

typedef struct		s_pma_it
{
	t_pma			*pma;
	size_t			bucket_id;
//	size_t			data_id;
}					t_pma_it;

typedef struct		s_pma_en
{
	t_pma_it		it;
	void			*key;
}					t_pma_en;


t_array				array(void);
void				array_free(t_array *a);
size_t				array_len(const t_array *a, size_t word);
int					array_insert(t_array *a, const void *data,
	size_t i, size_t size);
int					array_remove(t_array *a, void *data,
	size_t i, size_t size);
int					array_move(t_array *a, size_t from, size_t to, size_t len);
int					array_push(t_array *a, const void *data, size_t size);
int					array_pop(t_array *a, void *data, size_t size);
int					array_reserve(t_array *a, size_t s);

t_bitmap			bitmap(void);
void				bitmap_free(t_bitmap *a);
int					bitmap_realloc(t_bitmap *bitmap, size_t new_size);
bool				bitmap_get(const t_bitmap *a, size_t i);
int					bitmap_get_safe(const t_bitmap *a, size_t i, bool *out);
void				bitmap_set(t_bitmap *a, size_t p, bool b);
int					bitmap_set_safe(t_bitmap *a, size_t i, bool b);
int					bitmap_push(t_bitmap *a, bool b);
int					bitmap_pop(t_bitmap *a, bool *data);

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

t_pma				pma(t_predicate predicate, t_uint key, t_uint value);
void				pma_free(t_pma *a);
t_pma_en			pma_search(const t_pma *a, const void *key);
t_pma_en			pma_delete(t_pma *a, const void *key, void *out);
int					pma_insert(t_pma *a, const void *key, const void *data);
int					pma_replace(t_pma *a, const void *key, void *data);
size_t				pma_len(const t_pma *a);

bool				pmait_get(const t_pma_it *i, void *data, void *key);
bool				pmait_next(t_pma_it *i, void *data, void *key);
bool				pmait_prev(t_pma_it *i, void *data, void *key);
bool				pmait_delete(t_pma_it *i, void *out);

t_pma_it			pma_ensure(t_pma_en res, void *data);

#endif
