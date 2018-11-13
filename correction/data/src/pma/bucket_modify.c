/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   bucket_modify.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lgarczyn <lgarczyn@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2014/11/07 16:18:53 by lgarczyn          #+#    #+#             */
/*   Updated: 2018/11/05 19:54:41 by lgarczyn         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

#include "pma_int.h"

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
	t_uint		word;

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

