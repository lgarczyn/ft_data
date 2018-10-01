/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sorted.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lgarczyn <lgarczyn@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/09/13 22:02:52 by lgarczyn          #+#    #+#             */
/*   Updated: 2018/09/14 01:10:53 by lgarczyn         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include "data.h"

t_sorted		sorted(t_predicate predicate, size_t word)
{
	t_sorted	out;

	ft_bzero(&out, sizeof(out));
	out.predicate = predicate;
	out.word = MAX(word, 1);
	return (out);
}

void			sorted_free(t_sorted *a)
{
	free(a->data);
	*a = sorted(a->predicate, a->word);
}

void			*sorted_get(t_sorted *a, size_t index)
{
	return (a->data + (index * a->word));
}

const void		*sorted_cget(const t_sorted *a, size_t index)
{
	return (a->data + (index * a->word));
}

t_searchres		sorted_search_range(
	const t_sorted *a, const void *ptr, size_t start, size_t end)
{
	t_searchres	res;

	res.index = start + (end - start) / 2;
	res.found = 0;
	if (start < end)
	{
		if (res.index == start)
		{
			if (a->predicate(ptr, sorted_cget(a, res.index)) == 0)
			{
				if (a->predicate(sorted_cget(a, res.index), ptr) == 0)
					res.found = 1;
				else
					res.index++;
			}
		}
		else if (a->predicate(ptr, sorted_cget(a, res.index)))
			res = sorted_search_range(a, ptr, start, res.index);
		else
			res = sorted_search_range(a, ptr, res.index, end);
	}
	return (res);
}

t_searchres		sorted_search(const t_sorted *a, const void *ptr)
{
	return (sorted_search_range(a, ptr, 0, sorted_len(a)));
}

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

static void		shrink_to_fit(t_sorted *a)
{
	if (ft_realloc(&a->data, a->size, a->pos) == OK)
	{
		a->size = a->pos;
	}
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
		shrink_to_fit(a);
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


t_searchres		sorted_replace(t_sorted *a, void *data)
{
	t_searchres	res;

	res = sorted_search(a, data);
	if (res.found)
	{
		ft_memswap(sorted_get(a, res.index), data, a->word);
	}
	else 
	{
		sorted_insert_index(a, data, res.index);
	}
	return (res);
}

t_searchres		sorted_replace_hint(t_sorted *a, void *data, size_t hint)
{
	if (hint == 0 || a->predicate(sorted_get(a, hint - 1), data))
		if (hint >= sorted_len(a) || a->predicate(data, sorted_get(a, hint)))
		{
			ft_memswap(sorted_get(a, hint), data, a->word);
		}
	return (sorted_replace(a, data));
}

int				sorted_pop(t_sorted *a, void *data)
{
	if (sorted_len(a) <= 0)
		return (ERR_ARG);
	sorted_delete_index(a, sorted_len(a) - 1, data);
	return (OK);
}

int				sorted_reserve(t_sorted *a, size_t s)
{
	s *= a->word;
	if (s > a->size)
	{
		if (ft_realloc(&a->data, a->size, s))
			return (ERR_ALLOC);
	}
	return (OK);
}

size_t			sorted_len(const t_sorted *a)
{
	return (a->pos / a->word);
}
