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

t_sorted		sorted(t_predicate predicate, size_t word)
{
	t_sorted			out;

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
			if (a->predicate(ptr, &a->data[res.index * a->word]) == 0)
			{
				if (a->predicate(&a->data[res.index * a->word], ptr) == 0)
					res.found = 1;
				else
					res.index++;
			}
		}
		else if (a->predicate(ptr, &a->data[res.index * a->word]))
			res = sorted_search_range(a, ptr, start, res.index);
		else
			res = sorted_search_range(a, ptr, res.index, end);
	}
	return (res);
}

t_searchres		sorted_search(const t_sorted *a, const void *ptr)
{
	return (sorted_search_range(a, ptr, 0, a->pos / a->word));
}

int				sorted_insert(t_sorted *a, const void *data)
{
	size_t		new_pos;
	size_t		prev_len;
	t_searchres	res;
	void		*array_data;

	res = sorted_search(a, data);
	if (res.found)
		ft_memcpy(a->data + res.index * a->word, data, a->word);
	else
	{
		new_pos = a->pos + a->word;
		if (new_pos > a->size)
		{
			if (ft_realloc(&a->data, a->size, new_pos * 2))
				return (ERR_ALLOC);
			a->size = new_pos * 2;
		}
		prev_len = res.index * a->word;
		array_data = a->data + prev_len;
		if (a->pos - prev_len)
			ft_memmove(array_data + a->word, array_data, a->pos - prev_len);
		ft_memcpy(array_data, data, a->word);
		a->pos = new_pos;
	}
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

int				sorted_pop(t_sorted *a, void *data)
{
	size_t		new_pos;

	if (a->pos <= 0)
		return (ERR_ARG);
	new_pos = a->pos - a->word;
	ft_memcpy(data, a->data + new_pos, a->word);
	if (new_pos <= a->size / 4)
	{
		if (ft_realloc(&a->data, a->size, new_pos) == 0)
		{
			a->size = new_pos * 2;
		}
	}
	a->pos = new_pos;
	return (OK);
}
