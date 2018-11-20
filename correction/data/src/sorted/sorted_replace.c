/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sorted_replace.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lgarczyn <lgarczyn@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/09/13 22:02:52 by lgarczyn          #+#    #+#             */
/*   Updated: 2018/11/05 19:54:32 by lgarczyn         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include "sorted_int.h"

t_sorteden		sorted_replace(t_sorted *a, void *data)
{
	t_sorteden	res;

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

t_sorteden		sorted_replace_hint(t_sorted *a, void *data, size_t hint)
{
	if (hint == 0 || a->predicate(sorted_get(a, hint - 1), data))
		if (hint >= sorted_len(a) || a->predicate(data, sorted_get(a, hint)))
		{
			ft_memswap(sorted_get(a, hint), data, a->word);
		}
	return (sorted_replace(a, data));
}
