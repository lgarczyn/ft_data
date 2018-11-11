/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   bucket_rebalance.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lgarczyn <lgarczyn@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2014/11/07 16:18:53 by lgarczyn          #+#    #+#             */
/*   Updated: 2018/11/05 19:54:40 by lgarczyn         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

#include "pma_int.h"

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
	if (bitmap_set_len(&(tmp->flags), new_size))
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

