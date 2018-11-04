/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pma.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lgarczyn <lgarczyn@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2014/11/07 16:18:53 by lgarczyn          #+#    #+#             */
/*   Updated: 2018/10/11 00:29:19 by lgarczyn         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include "pma_int.h"

t_pma			pma(t_predicate predicate, t_uint key, t_uint value)
{
	t_pma		out;
	static u64	global_canary = 1337;

	ft_bzero(&out, sizeof(t_pma));
	out.predicate = predicate;
	out.bucket.sizes.key = key;
	out.bucket.sizes.val = value;
	out.canary = global_canary;
	global_canary += CANARY_STEP;
	return (out);
}

void			pma_free(t_pma *a)
{
	bucket_free(&(a->bucket));
	*a = pma(a->predicate, a->bucket.sizes.key, a->bucket.sizes.val);
}

size_t			pma_size(const t_pma *a)
{
	return (bucket_size(&(a->bucket)));
}

size_t			pma_len(const t_pma *a)
{
	return (a->bucket.count);
}

//bucket_tools.c

void			bucket_free(t_bucket *b)
{
	t_sizes		sizes;

	bitmap_free(&(b->flags));
	array_free(&(b->values));
	sizes = b->sizes;
	ft_bzero(b, sizeof(t_bucket));
	b->sizes = sizes;
}

void			*bucket_at(t_bucket *b, size_t index)
{
	return (b->values.data + (index * (b->sizes.key + b->sizes.val)));
}

const void		*bucket_cat(const t_bucket *b, size_t index)
{
	return (b->values.data + (index * (b->sizes.key + b->sizes.val)));
}

size_t			bucket_word(const t_bucket *b)
{
	return (b->sizes.key + b->sizes.val);
}

size_t			bucket_size(const t_bucket *b)
{
	return (bitmap_len(&(b->flags)));
}

//pma_tools.c

void			*pma_at(t_pma *a, size_t index)
{
	return (bucket_at(&(a->bucket), index));
}

const void		*pma_cat(const t_pma *a, size_t index)
{
	return (bucket_cat(&(a->bucket), index));
}

//pma_search.c

static t_pma_it	pma_search_pos(const t_pma *a, const void *key)
{
	size_t		i;
	t_pma_it	it;

	it = pmait(a);
	while (it.id < it.end)
	{
		i = it.id + (it.end - it.id) / 2;
		while (i < it.end && bitmap_get(&(a->bucket.flags), i) == false)
			i++;
		if (i == it.end)
			it.end = it.id + (it.end - it.id) / 2;
		else if (it.end == it.id + 1)
		{
			if (it.id == 0 && a->predicate(key, pma_cat(a, i)))
				it.end--;
			else if (a->predicate(pma_cat(a, i), key))
				it.id++;
			break;
		}
		else if (a->predicate(key, pma_cat(a, i)))
			it.end = i;
		else
			it.id = i;
	}
	return (it);
}

t_pma_en		pma_search(const t_pma *a, const void *key)
{
	t_pma_en	res;

	res.it = pma_search_pos(a, key);
	res.key = (void*)key;
	res.found = res.it.id < res.it.end;
	return (res);
}

t_pma_it		pma_search_range(const t_pma *a,
	const void *start, const void *end)
{
	t_pma_it	it;

	it = pmait(a);
	if (start)
		it.id = pma_search_pos(a, start).id;
	if (end)
		it.end = pma_search_pos(a, end).end;
	return (it);
}

//bucket_accesors.c

void			bucket_set(t_bucket *b, size_t id,
	const void *key, const void *val)
{
	void		*ptr;

	ptr = bucket_at(b, id);
	ft_memmove(ptr, key, b->sizes.key);
	ft_memmove(ptr + b->sizes.key, val, b->sizes.val);
	bitmap_set(&(b->flags), id, true);
}

void			bucket_get(t_bucket *b, size_t id,
	void *key, void *val)
{
	void		*ptr;

	ptr = bucket_at(b, id);
	if (key)
		ft_memmove(key, ptr, b->sizes.key);
	if (val)
		ft_memmove(val, ptr + b->sizes.key, b->sizes.val);
}

//bucket_rebalance.c

static void		set_clear(size_t **to, size_t val)
{
	**to = val;
	*to = NULL;
}

static void		update_its(t_bucket *b,
	size_t *it_a, size_t *it_b, size_t *add)
{
	size_t		i_from;
	size_t		i_to;

	i_from = 0;
	i_to = GROWTH_FACTOR - 1 + (PADDING - GROWTH_FACTOR) / 2;
	while (i_from <= bucket_size(b))
	{
		if (add && *add == i_from)
		{
			*add = i_to;
			i_to += GROWTH_FACTOR;
			add = NULL;
		}
		if (it_a && *it_a == i_from)
			set_clear(&it_a, i_to);
		if (it_b && *it_b == i_from)
			set_clear(&it_b, i_to);
		if (i_from < bucket_size(b) && bitmap_get(&(b->flags), i_from))
			i_to += GROWTH_FACTOR;
		i_from++;
	}
}

static int		bucket_clone(const t_bucket *b, t_bucket *tmp, bool adding)
{
	size_t		new_size;

	new_size = (b->count + adding) * GROWTH_FACTOR + PADDING;
	*tmp = *b;
	tmp->flags = bitmap();
	tmp->values = array();
	if (bitmap_set_size(&(tmp->flags), new_size))
		return(ERR_ALLOC);
	tmp->flags.pos = new_size;
	if (array_reserve(&(tmp->values), new_size * bucket_word(b)))
		return(ERR_ALLOC);
	tmp->values.pos = new_size * bucket_word(b);
	return (OK);
}

int				bucket_rebalance(t_bucket *b,
	size_t *it_a, size_t *it_b, size_t *add)
{
	t_bucket	tmp;
	size_t		i_from;
	size_t		i_to;

	if (bucket_clone(b, &tmp, add != NULL))
		return (ERR_ALLOC);
	i_from = 0;
	i_to = GROWTH_FACTOR - 1 + (PADDING - GROWTH_FACTOR) / 2;
	update_its(b, it_a, it_b, add);
	while (i_from < bucket_size(b))
	{
		if (bitmap_get(&(b->flags), i_from))
		{
			ft_memmove(tmp.values.data + (i_to * bucket_word(b)),
				b->values.data + (i_from * bucket_word(b)), bucket_word(b));
			bitmap_set(&(tmp.flags), i_to, true);
			i_to += GROWTH_FACTOR;
			if (add && *add == i_to)
				i_to += GROWTH_FACTOR;
		}
		i_from++;
	}
	bucket_free(b);
	*b = tmp;
	return (OK);
}

//bucket_modify.c

static size_t	count_moves(t_bitmap *b, size_t id, bool *forward)
{
	size_t		r;

	r = 0;
	while (id + r < bitmap_len(b) && bitmap_get(b, id + r))
		r++;
	if (id + r < bitmap_len(b))
	{
		*forward = true;
		return (r);
	}
	*forward = false;
	r = 0;
	id--;
	while (r < id && bitmap_get(b, id - r))
		r++;
	if (r >= id)
	{
		ft_perror("room wasn't made");
		ft_putchar('\n');
		exit(1);
	}
	return (r);
}

static void		make_space(t_bucket *b, size_t id, bool forward, size_t len)
{
	size_t		word;

	word = bucket_word(b);
	if (forward && len)
	{
		array_move(&(b->values),
			id * word,
			(id + 1) * word,
			len * word);
		bitmap_set(&(b->flags), id + len, true);
	}
	else if (len)
	{
		array_move(&(b->values),
			(id - len + 1) * word,
			(id - len) * word,
			len * word);
		bitmap_set(&(b->flags), id - len, true);
	}
}

int				bucket_insert(t_bucket *b, size_t id,
	const void *key, const void *val)
{
	size_t		move_len;
	bool		forward;

	if (b->count * 2 >= bucket_size(b))
	{
		if (bucket_rebalance(b, NULL, NULL, &id))
			return (ERR_ALLOC);
		move_len = count_moves(&(b->flags), id, &forward);
	}
	else 
	{
		move_len = count_moves(&(b->flags), id, &forward);
		if (move_len > MAX_HAMMER_INSERT_LEN)
			if (bucket_rebalance(b, NULL, NULL, &id))
				return (ERR_ALLOC);
		move_len = count_moves(&(b->flags), id, &forward);
	}
	if (forward == false)
		id--;
	make_space(b, id, forward, move_len);
	bucket_set(b, id, key, val);
	b->count++;
	return (OK);
}

void			bucket_delete(t_bucket *b, size_t id,
	size_t *it_a, size_t *it_b)
{
	void		*value;

	value = bucket_at(b, id);
	ft_bzero(value, b->sizes.val + b->sizes.key);
	bitmap_set(&(b->flags), id, false);
	b->count--;
	if (b->count * (GROWTH_FACTOR * 2) < bucket_size(b))
		bucket_rebalance(b, it_a, it_b, NULL);
}

//pma_modify.c

bool			pma_delete(t_pma *a, const void *key,
	void *out_key, void *out_val)
{
	t_pma_en	en;

	a->canary++;
	en = pma_search(a, key);
	if (en.found)
	{
		bucket_get(&(a->bucket), en.it.id, out_key, out_val);
		bucket_delete(&(a->bucket), en.it.id, NULL, NULL);
	}
	en.key = (void*)key;
	return (en.found);
}

int				pma_insert(t_pma *a, const void *key, const void *val)
{
	t_pma_en	en;

	a->canary++;
	en = pma_search(a, key);
	if (en.found)
	{
		bucket_set(&(a->bucket), en.it.id, key, val);
		return (OK);
	}
	else
	{
		if (bucket_insert(&(a->bucket), en.it.id, key, val))
			return (ERR_ALLOC);
		return (OK);
	}
}

//pmait.c

t_pma_it		pmait(const t_pma *a)
{
	t_pma_it	it;

	it.id = 0;
	it.end = pma_size(a);
	it.pma = (t_pma*)a;
	it.canary = a->canary;
	return (it);
}

bool			pmait_get(t_pma_it *i, void *key, void *val)
{
	t_pma		*a;
	t_bitmap	*bmp;

	a = i->pma;
	if (a->canary != i->canary)
		ft_putendl_fd("USING INVALID ITERATOR", STDERR);
	bmp = &(a->bucket.flags);
	while (i->id < i->end && bitmap_get(bmp, i->id) == false)
		i->id++;
	if (i->id >= i->end)
		return (false);
	bucket_get(&(a->bucket), i->id, key, val);
	return (true);
}

bool			pmait_get_back(t_pma_it *i, void *key, void *val)
{
	t_pma		*a;
	t_bitmap	*bmp;

	a = i->pma;
	if (a->canary != i->canary)
		ft_putendl_fd("USING INVALID ITERATOR", STDERR);
	bmp = &(a->bucket.flags);
	while (i->end > i->id && bitmap_get(bmp, i->end - 1) == false)
		i->end--;
	if (i->end <= i->id)
		return (false);
	bucket_get(&(a->bucket), i->end - 1, key, val);
	return (true);
}

bool			pmait_next(t_pma_it *i, void *key, void *val)
{
	if (i->pma->canary != i->canary)
		ft_putendl_fd("USING INVALID ITERATOR", STDERR);
	if (pmait_get(i, key, val))
	{
		i->id++;
		return (true);
	}
	return (false);
}

bool			pmait_next_back(t_pma_it *i, void *key, void *val)
{
	if (i->pma->canary != i->canary)
		ft_putendl_fd("USING INVALID ITERATOR", STDERR);
	if (pmait_get_back(i, key, val))
	{
		i->end--;
		return (true);
	}
	return (false);
}

//pmait_delete.c

bool			pmait_delete(t_pma_it *i, void *key, void *val)
{
	if (i->pma->canary != i->canary)
		ft_putendl_fd("USING INVALID ITERATOR", STDERR);
	if (pmait_get(i, key, val))
	{
		bucket_delete(&(i->pma->bucket), i->id, &(i->id), &(i->end));
		i->pma->canary++;
		i->canary++;
		return (true);
	}
	return (false);
}

bool			pmait_delete_back(t_pma_it *i, void *key, void *val)
{
	if (i->pma->canary != i->canary)
		ft_putendl_fd("USING INVALID ITERATOR", STDERR);
	if (pmait_get_back(i, key, val))
	{
		bucket_delete(&(i->pma->bucket), i->end - 1, &(i->id), &(i->end));
		i->pma->canary++;
		i->canary++;
		return (true);
	}
	return (false);
}

//pma_wrappers.c

int				pma_ensure(t_pma_en *en, const void *data)
{
	if (en->it.pma->canary != en->it.canary)
		ft_putendl_fd("USING INVALID ITERATOR", STDERR);
	if (en->found == false)
	{
		if (bucket_insert(
			&(en->it.pma->bucket),
			en->it.id,
			en->key, data))
			return (ERR_ALLOC);

		en->it.pma->canary++;
		en->it.canary++;
		en->found = true;
	}
	return (OK);
}

bool			pma_get(const t_pma *a, const void *key,
	void *out_key, void *out_val)
{
	t_pma_en	en;

	en = pma_search(a, key);
	if (en.found)
		pmait_get(&(en.it), out_key, out_val);
	return (en.found);
}

bool			pma_pop_back(t_pma *a, void *key, void *val)
{
	t_pma_it		it;

	it = pmait(a);
	if (pmait_get_back(&it, key, val) == false)
		return (false);
	pmait_delete_back(&it, NULL, NULL);
	a->canary++;
	return (true);
}

bool			pma_pop_front(t_pma *a, void *key, void *val)
{
	t_pma_it		it;

	it = pmait(a);
	if (pmait_get(&it, key, val) == false)
		return (false);
	pmait_delete(&it, NULL, NULL);
	a->canary++;
	return (true);
}
