/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pma_int.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lgarczyn <lgarczyn@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2014/11/07 16:18:53 by lgarczyn          #+#    #+#             */
/*   Updated: 2018/11/05 19:54:39 by lgarczyn         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef _PMA_INT_H
# define _PMA_INT_H

# define GROWTH_FACTOR 3
# define PADDING 6
# define MAX_HAMMER_INSERT_LEN 100
# define CANARY_STEP 10000000

# include "libft.h"
# include "data.h"

/*
** pma.c
*/
t_pma		pma(t_predicate	predicate, t_uint key, t_uint value);
void		pma_free(t_pma	*a);
size_t		pma_size(const	t_pma *a);
size_t		pma_len(const	t_pma *a);
/*
** bucket_tools.c
*/
void		bucket_free(t_bucket	*b);
void		*bucket_at(t_bucket	*b, size_t index);
const void	*bucket_cat(const t_bucket *b, size_t index);
size_t		bucket_word(const	t_bucket *b);
size_t		bucket_size(const	t_bucket *b);
/*
** pma_tools.c
*/
void		*pma_at(t_pma	*a, size_t index);
const void	*pma_cat(const t_pma *a, size_t index);
/*
** pma_search.c
*/
t_pmaen		pma_search(const t_pma *a, const void *key);
t_pmait		pma_search_range(const t_pma *a, const void *start, const void *end);
bool		pma_get(const t_pma *a, const void *key, void *out_key, void *out_val);
/*
** bucket_accesors.c
*/
void		bucket_set(t_bucket *b, size_t id, const void *key, const void *val);
void		bucket_get(t_bucket *b, size_t id, void *key, void *val);
/*
** bucket_rebalance.c
*/
int			bucket_rebalance(t_bucket *b, size_t *it_a, size_t *it_b, size_t *add);
/*
** bucket_modify.c
*/
int			bucket_insert(t_bucket *b, size_t id, const void *key, const void *val);
void		bucket_delete(t_bucket *b, size_t id, size_t *it_a, size_t *it_b);
/*
** pma_modify.c
*/
bool		pma_delete(t_pma *a, const void *key, void *out_key, void *out_val);
int			pma_insert(t_pma *a, const void *key, const void *val);
/*
** pmait.c
*/
t_pmait		pmait(const t_pma *a);
bool		pmait_get(t_pmait *i, void *key, void *val);
bool		pmait_get_back(t_pmait *i, void *key, void *val);
bool		pmait_next(t_pmait *i, void *key, void *val);
bool		pmait_next_back(t_pmait *i, void *key, void *val);
/*
** pmait_delete.c
*/
bool		pmait_delete(t_pmait *i, void *key, void *val);
bool		pmait_delete_back(t_pmait *i, void *key, void *val);
/*
** pma_wrappers.c
*/
int			pma_ensure(t_pmaen *en, const void *data);
bool		pma_pop_back(t_pma *a, void *key, void *val);
bool		pma_pop_front(t_pma *a, void *key, void *val);
#endif
