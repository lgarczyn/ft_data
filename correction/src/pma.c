/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pma.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lgarczyn <lgarczyn@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2014/11/07 16:18:53 by lgarczyn          #+#    #+#             */
/*   Updated: 2018/10/09 21:52:37 by lgarczyn         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include "data.h"

t_pma			pma(t_predicate predicate, t_uint key, t_uint value)
{
	t_pma		out;

	ft_bzero(&out, sizeof(t_pma));
	out.predicate = predicate;
	out.sizes.key = key;
	out.sizes.val = value;
	out.bucket.sizes = out.sizes;
	return (out);
}

void			pma_free(t_pma *a)
{
	bitmap_free(&(a->bucket.flags));
	array_free(&(a->bucket.values));
	*a = pma(a->predicate, a->sizes.key, a->sizes.val);
}

void			*bucket_at(t_bucket *b, size_t index)
{
	return (b->values.data + (index * (b->sizes.key + b->sizes.val)));
}

const void		*bucket_cat(const t_bucket *b, size_t index)
{
	return (b->values.data + (index * (b->sizes.key + b->sizes.val)));
}

void			*pma_at(t_pma *a, size_t index)
{
	return (bucket_at(&(a->bucket), index));
}

const void		*pma_cat(const t_pma *a, size_t index)
{
	return (bucket_cat(&(a->bucket), index));
}

size_t			pma_len(const t_pma *a)
{
	return (a->count);
}

size_t			bucket_size(const t_bucket *b)
{
	return (bitmap_len(&(b->flags)));
}

size_t			pma_size(const t_pma *a)
{
	return (bucket_size(&(a->bucket)));
}


//add pma search it
t_pma_en		pma_search_range(const t_pma *a, const void *key, size_t start, size_t end)
{
	t_pma_en	res;
	size_t		i;

	res.key = (void*)key;
	res.it.pma = (t_pma*)a;
	//WHILE SEARCH RANGE IS VALID
	i = start + (end - start) / 2;
	while (start < end)
	{
		//while i is in range, and is not a valid target
		while (i < end && bitmap_get(&(a->bucket.flags), i) == false)
		{
			//printf("WTF3 %lu->%lu %lu\n", start, end, i);
			i++;
		}
		//if i reached end, change range
		if (i == end)
		{
			//printf("WTF4 %lu->%lu %lu  %lu->%lu\n", start, end, i, end, start + (end - start) / 2);
			end = start + (end - start) / 2;
		}
		//if there's only one pos left
		else if (end == start + 1)
		{
			//if pos fits, set key to NULL (meaning found)
			if (a->predicate(key, pma_cat(a, i)) == 0)
			{
				if (a->predicate(pma_cat(a, i), key) == 0)
					res.key = NULL;
				//if current pos is too small, take next place
				else
					i++;
			}
			break;
		}
		//if key is smaller than i, reduce end, else increase start
		else if (a->predicate(key, pma_cat(a, i)))
			end = i;
		else
			start = i;
		i = start + (end - start) / 2;
	}
	res.it.id = i;
	res.found = res.key == NULL;
	return (res);
}

t_pma_en		pma_search(const t_pma *a, const void *key)
{
	return (pma_search_range(a, key, 0, pma_size(a)));
}

static void		bucket_set(t_bucket *b, size_t id, const void *key, const void *val)
{
	void		*ptr;

	ptr = bucket_at(b, id);
	ft_memmove(ptr, key, b->sizes.key);
	ft_memmove(ptr + b->sizes.key, val, b->sizes.val);
	bitmap_set(&(b->flags), id, true);
}

static void		bucket_get(t_bucket *b, size_t id, void *key, void *val)
{
	void		*ptr;

	ptr = bucket_at(b, id);
	ft_memmove(key, ptr, b->sizes.key);
	ft_memmove(val, ptr + b->sizes.key, b->sizes.val);
}

#define MAGIC 4
#define MAGIC_2 100

int				bucket_rebalance(t_bucket *b)
{
	size_t		b_i;
	size_t		tmp_i;
	size_t		size;
	t_array		tmp;
	size_t		new_size;

	size = b->sizes.key + (size_t)b->sizes.val;
	new_size = b->count * MAGIC + (MAGIC - 1);
	tmp = array();
	if (bitmap_reserve(&(b->flags), new_size))
	 	return (ERR_ALLOC);
	if (array_reserve(&tmp, new_size * size))
		return (ERR_ALLOC);
	b->flags.pos = new_size;
	tmp.pos = new_size * size;
	b_i = 0;
	tmp_i = MAGIC - 1;
	while (b_i < bucket_size(b))
	{
		if (bitmap_get(&(b->flags), b_i))
		{
			ft_bzero(tmp.data + (tmp_i * size), size);
			ft_memmove(
				tmp.data + (tmp_i * size),
				b->values.data + (b_i * size), size);
			ft_bzero(tmp.data + ((tmp_i + 1) * size), size);
			tmp_i += MAGIC;
		}
		b_i++;
	}
	array_free(&(b->values));
	b->values = tmp;
	b_i = 0;
	while (b_i < bucket_size(b))
	{
		bitmap_set(&(b->flags), b_i, b_i % MAGIC == MAGIC - 1);
		b_i++;
	}
	return (OK);
}

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

static int		bucket_insert(t_bucket *b, size_t id, const void *key, const void *val)
{
	size_t		move_len;
	size_t		size;
	bool		forward;

	if (b->count * 2 + 1 > bucket_size(b))
		if (bucket_rebalance(b))
			return (ERR_ALLOC);
	if (id == bucket_size(b))
		id--;
	move_len = count_moves(&(b->flags), id, &forward);
	if (move_len > MAGIC_2)
	{
		if (bucket_rebalance(b))
			return (ERR_ALLOC);
		move_len = count_moves(&(b->flags), id, &forward);
	}
	size = b->sizes.key + b->sizes.val;
	if (forward)
	{
		array_move(&(b->values), id * size, (id + 1) * size, move_len * size);
		bitmap_set(&(b->flags), id + move_len, true);
	}
	else
	{
		array_move(&(b->values), (id - move_len) * size, (id - move_len - 1) * size, move_len * size);
		bitmap_set(&(b->flags), id - move_len - 1, true);
	}
	bucket_set(b, id, key, val);
	b->count++;
	return (OK);
}

static void		bucket_delete(t_bucket *b, size_t id)
{
	void		*value;

	value = bucket_at(b, id);
	ft_bzero(value, b->sizes.val + b->sizes.key);
	bitmap_set(&(b->flags), id, false);
	b->count--;
	if (b->count * MAGIC * MAGIC < bucket_size(b))
		bucket_rebalance(b);
}

t_pma_en		pma_delete(t_pma *a, const void *key,
	void *out_key, void *out_val)
{
	t_pma_en	en;

	en = pma_search(a, key);
	if (en.found)
	{
		bucket_get(&(a->bucket), en.it.id, out_key, out_val);
		bucket_delete(&(a->bucket), en.it.id);
		a->count--;
	}
	en.key = (void*)key;
	return (en);
}

int				pma_insert(t_pma *a, const void *key, const void *val)
{
	t_pma_en	en;

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
		a->count++;
		return (OK);
	}
}

bool			pmait_get(t_pma_it *i, void *key, void *val)
{
	bool		b;
	t_pma		*a;
	t_bitmap	*bmp;

	a = i->pma;
	bmp = &(a->bucket.flags);
	b = true;
	while (bitmap_get_safe(bmp, i->id, &b) && b == false)
		i->id++;
	if (i->id >= bitmap_len(bmp))
		return (false);
	if (key)
		ft_memmove(key, pma_cat(a, i->id), a->sizes.key);
	if (val)
		ft_memmove(val, pma_cat(a, i->id) + a->sizes.key, a->sizes.val);
	return (true);
}

bool			pmait_next(t_pma_it *i, void *key, void *val)
{
	if (pmait_get(i, key, val))
	{
		i->id++;
		return (true);
	}
	return (false);
}

bool			pmait_prev(t_pma_it *i, void *key, void *val)
{
	bool		b;
	t_bitmap	*bmp;

	bmp = &(i->pma->bucket.flags);
	b = true;
	if (pmait_get(i, key, val))
	{
		while (bitmap_get_safe(bmp, i->id, &b) && b == false)
			i->id--;
		return (true);
	}
	return (false);
}

bool			pmait_delete(t_pma_it *i, void *key, void *val)
{
	if (pmait_get(i, key, val))
	{
		bucket_delete(&(i->pma->bucket), i->id);
		i->pma->count--;
		return (true);
	}
	return (false);
}

int				pma_ensure(t_pma_en *en, const void *data)
{
	if (en->found == false)
	{
		if (bucket_insert(
			&(en->it.pma->bucket),
			en->it.id,
			en->key, data))
			return (ERR_ALLOC);
		en->it.pma->count--;
		en->key = NULL;
		en->found = true;
	}
	return (OK);
}

t_pma_it		pmait_first(t_pma *a)
{
	t_pma_it	it;

	it.id = 0;
	it.pma = a;
	return (it);
}

t_pma_it		pmait_last(t_pma *a)
{
	t_pma_it	it;

	it.id = bitmap_len(&(a->bucket.flags));
	it.pma = a;
	return (it);
}
