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

#include "libft.h"
#include "data.h"

t_pma			pma(t_predicate predicate, t_uint key, t_uint value)
{
	t_pma		out;

	bzero(&out, sizeof(t_pma));
	out.predicate = predicate;
	out.key_size = key;
	out.value_size = value;
	return (out);
}

void			pma_free(t_pma *a)
{
	bitmap_free(&(a->bucket.occ));
	array_free(&(a->bucket.values));
	*a = pma(a->predicate, a->key_size, a->value_size);
}

void			*pma_get(t_pma *a, size_t index)
{
	return (a->bucket.values.data + (index * (a->key_size + a->value_size)));
}

const void		*pma_cget(const t_pma *a, size_t index)
{
	return (a->bucket.values.data + (index * (a->key_size + a->value_size)));
}

t_pma_en		pma_search_range(const t_pma *a, const void *key, size_t start, size_t end)
{
	t_pma_en	res;
	size_t		i;

	i = start + (end - start) / 2;
	res.key = key;
	//WHILE SEARCH RANGE IS VALID
	while (start < end)
	{
		//while i is in range, and is not a valid target
		while (i < end && bitmap_get(&(a->bucket.occ), i) == false)
			i++;
		//if i reached end, change range
		if (i == end)
			end = start + (end - start) / 2;
		//if there's only one pos left
		else if (end == start + 1)
		{
			//if pos fits, set key to NULL (meaning found)
			if (a->predicate(key, pma_cget(a, i)) == 0)
			{
				if (a->predicate(pma_cget(a, i), key) == 0)
					res.key = NULL;
				//if current pos is too small, take next place
				else
					i++;
				break;
			}
		}
		//if key is smaller than i, reduce end, else increase start
		else if (a->predicate(key, pma_cget(a, i)))
			end = i;
		else
			start = i;
	}
	res.it.bucket_id = i;
	res.found = res.key == NULL;
	return (res);
}

t_pma_en		pma_search(const t_pma *a, const void *ptr)
{
	return (pma_search_range(a, ptr, 0, pma_len(a)));
}

static void		bucket_set(t_pma *a, t_bucket *b, size_t id, void *key, void *val)
{
	void		*ptr;

	ptr = pma_get(a, id);
	ft_memmove(ptr, key, a->key_size);
	ft_memmove(ptr + a->key_size, val, a->value_size);
	bitmap_set(&(b->occ), id, true);
}

static void		bucket_get(t_pma *a, t_bucket *b, size_t id, void *key, void *val)
{
	void		*ptr;

	ptr = pma_get(a, id);
	ft_memmove(key, ptr, a->key_size);
	ft_memmove(val, ptr + a->key_size, a->value_size);
}

static void		bucket_delete(t_pma *a, t_bucket *b, size_t id)
{
	void		*value;

	value = pma_get(a, id);
	ft_bzero(value, a->value_size + a->key_size);
	bitmap_set(&(b->occ), id, false);
	a->count--;
}

static int		bucket_insert(t_pma *a, t_bucket *b, size_t id, void *key, void *val)
{
	void		*ptr;
	size_t		move_len;
	size_t		size;
	int			r;

	move_len = 0;
	while (id + move_len < b->occ.pos && bitmap_get(&(b->occ), id + move_len))
	{
		move_len++;
	}
	size = a->key_size + a->value_size;
	r = array_move(a, id * size, (id + 1) * size, move_len * size);
	if (r)
		return (r);
	if (id + move_len == b->occ.pos)
		r = bitmap_push(&(b->occ), true);
	else
		bitmap_set(&(b->occ), id + move_len, true);
	if (r)
		return (r);
	bucket_set(a, b, id, key, val);
	a->count++;
	return (OK);
}

t_pma_en		pma_delete(t_pma *a, const void *key,
	void *out_key, void *out_val)
{
	t_pma_en	en;

	en = pma_search(a, key);
	if (en.key)
	{
		bucket_get(a, &(a->bucket), en.it.bucket_id, out_key, out_val);
		bucket_delete(a, &(a->bucket), en.it.bucket_id);
	}
	en.key = key;
	return (en);
}

int				pma_insert(t_pma *a, const void *key, const void *val)
{
	t_pma_en	en;

	en = pma_search(a, key);
	if (en.key == NULL)
	{
		return (bucket_insert(a, &(a->bucket), en.it.bucket_id, key, val));
	}
	else
	{
		bucket_set(a, &(a->bucket), en.it.bucket_id, key, val);
	}
	return (OK);
}

int				pma_replace(t_pma *a, const void *key, void *val)
{
	t_pma_en	en;
	void		*ptr;

	en = pma_search(a, key);
	if (en.key == NULL)
	{
		return (bucket_insert(a, &(a->bucket), en.it.bucket_id, key, val));
	}
	else
	{
		ptr = pma_get(a, en.it.bucket_id);
		ft_memswap(ptr, key, a->key_size);
		ft_memswap(ptr + a->key_size, val, a->value_size);
	}
	return (OK);
}

size_t			pma_len(const t_pma *a)
{
	return (a->count);
}

bool			pmait_get(t_pma_it *i, void *key, void *val)
{
	bool		b;
	t_pma		*a;
	t_bitmap	*bmp;

	a = i->pma;
	bmp = &(a->bucket.occ);
	b = true;
	while (bitmap_get_safe(bmp, i->bucket_id, &b) && b == false)
		i->bucket_id++;
	if (i->bucket_id >= bitmap_len(bmp))
		return (false);
	if (key)
		ft_memmove(key, pma_cget(a, i->bucket_id), a->key_size);
	if (val)
		ft_memmove(val, pma_cget(a, i->bucket_id) + a->key_size, a->value_size);
	return (true);
}

bool			pmait_next(t_pma_it *i, void *key, void *val)
{
	if (pmait_get(i, key, val))
	{
		i->bucket_id++;
		return (true);
	}
	return (false);
}

bool			pmait_prev(t_pma_it *i, void *key, void *val)
{
	if (pmait_get(i, key, val))
	{
		while (bitmap_get_safe(bmp, i->bucket_id, &b) && b == false)
			i->bucket_id--;
		return (true);
	}
}

bool			pmait_delete(t_pma_it *i, void *key, void *val)
{
	if (pmait_get(i, key, val))
	{
		bucket_delete(i->pma, &(i->pma->bucket), i->bucket_id);
		return (true);
	}
	return (false);
}

int				pma_ensure(t_pma_en *en, const void *data)
{
	if (en->key != NULL)
	{
		if (bucket_insert(
			&(en->it.pma),
			&(en->it.pma->bucket),
			en->it.bucket_id,
			en->key, data))
			return (ERR_ALLOC);
		en->key = NULL;
		en->found = true;
	}
}

t_pma_it		pmait_first(t_pma *a)
{
	t_pma_it	it;

	it.bucket_id = 0;
	it.pma = a;
}

t_pma_it		pmait_last(t_pma *a)
{
	t_pma_it	it;

	it.bucket_id = a->;
	it.pma = a;
}
