/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sorted_insert.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lgarczyn <lgarczyn@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/09/13 22:02:52 by lgarczyn          #+#    #+#             */
/*   Updated: 2018/11/06 00:06:07 by lgarczyn         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include "sorted_int.h"

int				sorted_insert_index(t_sorted *a, const void *data, size_t i)
{
	size_t		new_pos;
	size_t		prev_len;
	size_t		next_len;

	new_pos = a->pos + a->word;
	if (new_pos > a->size)
		if (ft_realloc(
			&a->data,
			a->pos,
			new_pos * REALLOC_GROWTH_FACTOR,
			&a->size))
			return (ERR_ALLOC);
	prev_len = i * a->word;
	next_len = a->pos - prev_len;
	if (a->pos - prev_len)
		ft_memmove(sorted_get_mut(a, i + 1), sorted_get(a, i), next_len);
	ft_memcpy(sorted_get_mut(a, i), data, a->word);
	a->pos = new_pos;
	return (OK);
}

int				sorted_insert_hint(t_sorted *a, const void *data, size_t hint)
{
	size_t		index_prev;
	size_t		index_self;

	index_prev = (hint - 1) * a->word;
	index_self = hint * a->word;
	if (hint == 0 || a->predicate(a->data + index_prev, data))
		if (hint >= sorted_len(a) || a->predicate(data, a->data + index_self))
			return (sorted_insert_index(a, data, hint));
	return (sorted_insert(a, data));
}

int				sorted_insert(t_sorted *a, const void *data)
{
	t_sorteden	res;

	res = sorted_search(a, data);
	if (res.found)
		ft_memcpy(a->data + res.index * a->word, data, a->word);
	else
	{
		return (sorted_insert_index(a, data, res.index));
	}
	return (OK);
}
