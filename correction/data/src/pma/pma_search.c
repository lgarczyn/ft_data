/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pma_search.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lgarczyn <lgarczyn@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2014/11/07 16:18:53 by lgarczyn          #+#    #+#             */
/*   Updated: 2018/11/05 19:54:38 by lgarczyn         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

#include "pma_int.h"

static int		pred(const t_pma *a, const void *pa, const void *pb)
{
	if (a->multi)
		return (!a->predicate(pb, pa));
	return (a->predicate(pa, pb));
}

static t_pmait	pma_search_pos(const t_pma *a, const void *key)
{
	size_t		i;
	t_pmait		it;

	it = pmait(a);
	while (it.id < it.end)
	{
		i = it.id + (it.end - it.id) / 2;
		while (i < it.end && bitset_get(&(a->bucket.flags), i) == false)
			i++;
		if (i == it.end)
			it.end = it.id + (it.end - it.id) / 2;
		else if (it.end == it.id + 1)
		{
			if (it.id == 0 && pred(a, key, pma_cat(a, i)))
				it.end--;
			else if (pred(a, pma_cat(a, i), key))
				it.id++;
			break ;
		}
		else if (pred(a, key, pma_cat(a, i)))
			it.end = i;
		else
			it.id = i;
	}
	return (it);
}

t_pmaen			pma_search(const t_pma *a, const void *key)
{
	t_pmaen		res;

	res.it = pma_search_pos(a, key);
	res.key = (void*)key;
	if (a->multi)
		while (res.it.end < bucket_size(&a->bucket) &&
			(bitset_get(&(a->bucket.flags), res.it.end) == false ||
			a->predicate(key, pma_cat(a, res.it.end)) == 0))
			res.it.end++;
	res.found = res.it.id < res.it.end;
	return (res);
}

t_pmait			pma_range(const t_pma *a,
	const void *start, const void *end)
{
	t_pmait		it;

	it = pmait(a);
	if (start)
		it.id = pma_search(a, start).it.id;
	if (end)
		it.end = pma_search(a, end).it.end;
	return (it);
}

int				pma_get(const t_pma *a, const void *key,
	void *out_key, void *out_val)
{
	t_pmaen		en;

	en = pma_search(a, key);
	if (en.found)
		pmait_get(&(en.it), out_key, out_val);
	return (en.found ? OK : ERR_MISSING);
}
