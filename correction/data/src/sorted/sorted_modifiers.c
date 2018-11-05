/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sorted_modifiers.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lgarczyn <lgarczyn@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/09/13 22:02:52 by lgarczyn          #+#    #+#             */
/*   Updated: 2018/11/05 19:54:33 by lgarczyn         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include "sorted_int.h"

static int		sorted_insert_index(t_sorted *a, const void *data, size_t i)
{
	size_t		new_pos;
	size_t		prev_len;
	size_t		next_len;

	new_pos = a->pos + a->word;
	if (new_pos > a->size)
	{
		if (ft_realloc(&a->data, a->size, new_pos * 2))
			return (ERR_ALLOC);
		a->size = new_pos * 2;
	}
	prev_len = i * a->word;
	next_len = a->pos - prev_len;
	if (a->pos - prev_len)
		ft_memmove(sorted_get(a, i + 1), sorted_cget(a, i), next_len);
	ft_memcpy(sorted_get(a, i), data, a->word);
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
	t_searchres	res;

	res = sorted_search(a, data);
	if (res.found)
		ft_memcpy(a->data + res.index * a->word, data, a->word);
	else
	{
		return (sorted_insert_index(a, data, res.index));
	}
	return (OK);
}

void			sorted_delete_index(t_sorted *a, size_t index, void *out)
{
	size_t		new_pos;
	size_t		prev_len;
	size_t		next_len;
	void		*array_data;

	new_pos = a->pos - a->word;
	prev_len = index * a->word;
	next_len = new_pos - prev_len;
	array_data = a->data + prev_len;
	if (out)
		ft_memcpy(out, array_data, a->word);
	if (next_len)
		ft_memmove(array_data, array_data + a->word, next_len);
	if (a->pos <= a->size / 4)
		if (ft_realloc(&a->data, a->size, a->pos) == OK)
			a->size = a->pos;
	a->pos = new_pos;
}

t_searchres		sorted_delete(t_sorted *a, const void *data, void *out)
{
	t_searchres	res;

	res = sorted_search(a, data);
	if (res.found)
	{
		sorted_delete_index(a, res.index, out);
	}
	return (res);
}

