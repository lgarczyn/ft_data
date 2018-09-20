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

t_searchres		sorted_search(t_sorted *a, void *ptr, size_t start, size_t end)
{
	t_searchres	res;

	res.index = start + (end - start) / 2;
	res.found = 0;
	if (start >= end)
		res.index = -1;
	else if (res.index == start)
	{
		if (a->predicate(&a->data[res.index * a->word], ptr) == 0)
			if (a->predicate(ptr, &a->data[res.index * a->word]) == 0)
				res.found = 1;
			else
				res.index--;
		else
			res.index++;
	}
	else if (a->predicate(ptr, &a->data[res.index * a->word]))
		res = sorted_search(a, ptr, start, res.index - 1);
	else
		res = sorted_search(a, ptr, res.index, end);
	return (res);
}

int				sorted_insert(t_sorted *a, void *data)
{
	size_t		new_pos;
	t_searchres	res;
	void		*array_data;

	res = sorted_search(a, data, 0, a->pos / a->word);
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
		array_data = a->data + res.index * a->word;
		ft_memmove(array_data + a->word, array_data, a->pos);
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
