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
size_t		array_len(const t_array *a);
int			array_reserve(t_array *a, size_t s);
int			array_set_len(t_array *a, size_t len);
int			array_insert(t_array *a, const void *data, size_t i, size_t size);
int			array_remove(t_array *a, void *data, size_t i, size_t size);
int			array_move(t_array *a, size_t from, size_t to, size_t len);
int			array_push(t_array *a, const void *data, size_t size);
int			array_pop(t_array *a, void *data, size_t size);

t_bitset	bitset(void);
void		bitset_free(t_bitset *a);
size_t		bitset_len(const t_bitset *a);
int			bitset_set_len(t_bitset *bitset, size_t new_size);
int			bitset_reserve(t_bitset *bitset, size_t new_size);
void		bitset_display(const t_bitset *a);
bool		bitset_get(const t_bitset *a, size_t i);
int			bitset_get_safe(const t_bitset *a, size_t i, bool *out);
void		bitset_set(t_bitset *a, size_t i, bool b);
int			bitset_set_safe(t_bitset *a, size_t i, bool b);
int			bitset_push(t_bitset *a, bool b);
int			bitset_pop(t_bitset *a, bool *data);

t_queue		queue(t_uint word);
void		queue_free(t_queue *a);
size_t		queue_len(const t_queue *a);
int			queue_reserve(t_queue *a, size_t s);
int			queue_push_back(t_queue *a, const void *data);
int			queue_push_front(t_queue *a, const void *data);
int			queue_pop_back(t_queue *a, void *data);
int			queue_pop_front(t_queue *a, void *data);

t_sorted	sorted(t_predicate predicate, t_uint word);
void		sorted_free(t_sorted *a);
size_t		sorted_len(const t_sorted *a);
int			sorted_reserve(t_sorted *a, size_t s);
const void	*sorted_get(const t_sorted *a, size_t index);
t_sorteden	sorted_search(const t_sorted *a, const void *d);
int			sorted_insert(t_sorted *a, const void *data);
/*
** sorted_replace
** if any item in t_sorted matches with data, swap data and item
*/
t_sorteden	sorted_replace(t_sorted *a, void *data);
t_sorteden	sorted_delete(t_sorted *a, const void *data, void *out);
int			sorted_delete_index(t_sorted *a, size_t index, void *out);
int			sorted_pop(t_sorted *a, void *data);

int			sorted_insert_hint(t_sorted *a, const void *d, size_t h);
t_sorteden	sorted_replace_hint(t_sorted *a, void *data, size_t hint);

t_pma		pma(t_predicate predicate, t_uint key, t_uint value);
void		pma_free(t_pma *a);
size_t		pma_len(const t_pma *a);
int			pma_insert(t_pma *a, const void *key, const void *val);
int			pma_delete(t_pma *a, const void *key, void *o_key, void *o_val);
int			pma_get(const t_pma *a, const void *key, void *o_key, void *o_val);
void		pma_display(t_pma *a, t_printer key, t_printer val);

int			pma_pop_back(t_pma *a, void *key, void *val);
int			pma_pop_front(t_pma *a, void *key, void *val);

t_pmait		pmait(const t_pma *a);
t_pmaen		pma_search(const t_pma *a, const void *key);
bool		pmait_next(t_pmait *i, void *key, void *val);
bool		pmait_delete(t_pmait *i, void *key, void *val);
void		pmait_display(t_pmait *it, t_printer key, t_printer val);

t_pmait		pma_range(const t_pma *a, const void *key_a, const void *key_b);
bool		pmait_next_back(t_pmait *i, void *key, void *val);
bool		pmait_delete_back(t_pmait *i, void *key, void *val);

int			pma_ensure(t_pmaen *en, const void *data);

#endif
