/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sorted_search.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lgarczyn <lgarczyn@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/09/13 22:02:52 by lgarczyn          #+#    #+#             */
/*   Updated: 2018/11/05 19:54:32 by lgarczyn         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include "sorted_int.h"

t_sorteden		sorted_search_range(
	const t_sorted *a, const void *ptr, size_t start, size_t end)
{
	t_sorteden	res;

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

t_sorteden		sorted_search(const t_sorted *a, const void *ptr)
{
	return (sorted_search_range(a, ptr, 0, sorted_len(a)));
}

