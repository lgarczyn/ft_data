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

#define SIZE(a) (a->key_size + a->value_size)

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

	res.it.bucket_id = start + (end - start) / 2;
	res.key = key;
	while (start < end)
	{
		//DEAL WITH EMPTY ZONE
		if (res.it.bucket_id == start)
		{
			if (a->predicate(key, pma_cget(a, res.it.bucket_id)) == 0)
			{
				if (a->predicate(pma_cget(a, res.it.bucket_id), key) == 0)
					res.key = NULL;
				else
					res.it.bucket_id++;
			}
		}
		else if (a->predicate(key, pma_cget(a, res.it.bucket_id)))
			res = pma_search_range(a, key, start, res.it.bucket_id);
		else
			res = pma_search_range(a, key, res.it.bucket_id, end);
	}
	return (res);
}

t_pma_en		pma_search(const t_pma *a, const void *ptr)
{
	return (pma_search_range(a, ptr, 0, pma_len(a)));
}

static void		bucket_delete(t_pma *a, t_bucket *b, size_t id, void *out)
{
	void		*value;

	if (out)
	{
		value = pma_get(a, id) + a->key_size;
		ft_memmove(out, value, a->value_size);
		ft_bzero(value, a->value_size);//to remove
	}
	bitmap_set(&(b->occ), id, false);
}

static void		bucket_set(t_pma *a, t_bucket *b, size_t id, void *key, void *val)
{
	void		*ptr;

	ptr = pma_get(a, id);
	ft_memmove(ptr, key, a->key_size);
	ft_memmove(ptr + a->key_size, val, a->value_size);
	bitmap_set(&(b->occ), id, true);
}

static int		bucket_insert(t_pma *a, t_bucket *b, size_t id, void *key, void *val)
{
	void		*ptr;
	size_t		move_len;
	size_t		size;

	move_len = 0;
	while (id + move_len < b->occ.pos && bitmap_get(&(b->occ), id + move_len))
	{
		move_len++;
	}
	size = SIZE(a);
	array_move(a, id * size, (id + 1) * size, move_len * size);
	if (id + move_len == b->occ.pos)
		bitmap_push(&(b->occ), true);
	else
		bitmap_set(&(b->occ), id + move_len, true);
	bucket_set(a, b, id, key, val);
	return (OK);//DONT DO THAT
}

t_pma_en		pma_delete(t_pma *a, const void *key, void *out)
{
	t_pma_en	en;

	en = pma_search(a, key);
	if (en.key)
	{
		bucket_delete(a, &(a->bucket), en.it.bucket_id, out);
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
		a->count ++;//I DONT KNOW DO SOMETHING
		return (bucket_insert(a, &(a->bucket), en.it.bucket_id, key, val));
	}
	else
	{
		bucket_set(a, &(a->bucket), en.it.bucket_id, key, val);
	}
	return (OK);
}

int				pma_replace(t_pma *a, const void *key, void *data)
{

}

size_t			pma_len(const t_pma *a)
{
	return (a->count);
}

bool			pmait_get(const t_pma_it *i, void *data, void *key);
bool			pmait_next(t_pma_it *i, void *data, void *key);
bool			pmait_prev(t_pma_it *i, void *data, void *key);
bool			pmait_delete(t_pma_it *i, void *out);

t_pma_it		pma_ensure(t_pma_en res, void *data);