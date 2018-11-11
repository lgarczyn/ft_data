/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   data.h                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lgarczyn <lgarczyn@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2014/11/07 16:18:53 by lgarczyn          #+#    #+#             */
/*   Updated: 2018/10/10 23:48:46 by lgarczyn         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef _DATA_H
# define _DATA_H

# include <stdlib.h>
# include <stdbool.h>
# include "structs.h"

t_array		array(void);
void		array_free(t_array *a);
size_t		array_len(const t_array *a, size_t word);
int			array_reserve(t_array *a, size_t s);
int			array_insert(t_array *a, const void *data, size_t i, size_t size);
int			array_remove(t_array *a, void *data, size_t i, size_t size);
int			array_move(t_array *a, size_t from, size_t to, size_t len);
int			array_push(t_array *a, const void *data, size_t size);
int			array_pop(t_array *a, void *data, size_t size);

t_bitmap	bitmap(void);
void		bitmap_free(t_bitmap *a);
size_t		bitmap_len(const t_bitmap *a);
int			bitmap_set_size(t_bitmap *bitmap, size_t new_size);
int			bitmap_reserve(t_bitmap *bitmap, size_t new_size);
bool		bitmap_get(const t_bitmap *a, size_t i);
int			bitmap_get_safe(const t_bitmap *a, size_t i, bool *out);
void		bitmap_set(t_bitmap *a, size_t i, bool b);
int			bitmap_set_safe(t_bitmap *a, size_t i, bool b);

int			bitmap_push(t_bitmap *a, bool b);
int			bitmap_pop(t_bitmap *a, bool *data);

t_queue		queue(size_t word);
void		queue_free(t_queue *a);
size_t		queue_len(const t_queue *a);
int			queue_reserve(t_queue *a, size_t s);
int			queue_push_back(t_queue *a, const void *data);
int			queue_push_front(t_queue *a, const void *data);
int			queue_pop_back(t_queue *a, void *data);
int			queue_pop_front(t_queue *a, void *data);

t_sorted	sorted(t_predicate predicate, size_t word);
void		sorted_free(t_sorted *a);
size_t		sorted_len(const t_sorted *a);
int			sorted_reserve(t_sorted *a, size_t s);
void		*sorted_get(t_sorted *a, size_t index);
const void	*sorted_cget(const t_sorted *a, size_t index);
t_searchres	sorted_search(const t_sorted *a, const void *d);
int			sorted_insert(t_sorted *a, const void *data);
t_searchres	sorted_replace(t_sorted *a, void *data);
t_searchres	sorted_delete(t_sorted *a, const void *data, void *out);
int			sorted_pop(t_sorted *a, void *data);

int			sorted_insert_hint(t_sorted *a, const void *d, size_t h);
t_searchres	sorted_replace_hint(t_sorted *a, void *data, size_t hint);
void		sorted_delete_index(t_sorted *a, size_t index, void *out);

t_pma		pma(t_predicate predicate, t_uint key, t_uint value);
void		pma_free(t_pma *a);
size_t		pma_len(const t_pma *a);
t_pmaen		pma_search(const t_pma *a, const void *key);
int			pma_insert(t_pma *a, const void *key, const void *val);
int			pma_delete(t_pma *a, const void *key, void *o_key, void *o_val);
int			pma_get(const t_pma *a, const void *key, void *o_key, void *o_val);

int			pma_pop_back(t_pma *a, void *key, void *val);
int			pma_pop_front(t_pma *a, void *key, void *val);

t_pmait		pmait(const t_pma *a);
bool		pmait_next(t_pmait *i, void *key, void *val);
bool		pmait_delete(t_pmait *i, void *key, void *val);

t_pmait		pma_range(const t_pma *a, void *key_a, void *key_b);
bool		pmait_next_back(t_pmait *i, void *key, void *val);
bool		pmait_delete_back(t_pmait *i, void *key, void *val);

int			pma_ensure(t_pmaen *en, const void *data);
void		pma_display(t_pma *a);

#endif
