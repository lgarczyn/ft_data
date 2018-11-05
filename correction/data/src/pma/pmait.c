/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pmait.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lgarczyn <lgarczyn@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2014/11/07 16:18:53 by lgarczyn          #+#    #+#             */
/*   Updated: 2018/11/05 19:54:36 by lgarczyn         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

#include "pma_int.h"

t_pmait			pmait(const t_pma *a)
{
	t_pmait		it;

	it.id = 0;
	it.end = pma_size(a);
	it.pma = (t_pma*)a;
	it.canary = a->canary;
	return (it);
}

bool			pmait_get(t_pmait *i, void *key, void *val)
{
	t_pma		*a;
	t_bitmap	*bmp;

	a = i->pma;
	if (a->canary != i->canary)
		ft_putendl_fd("USING INVALID ITERATOR", STDERR);
	bmp = &(a->bucket.flags);
	while (i->id < i->end && bitmap_get(bmp, i->id) == false)
		i->id++;
	if (i->id >= i->end)
		return (false);
	bucket_get(&(a->bucket), i->id, key, val);
	return (true);
}

bool			pmait_get_back(t_pmait *i, void *key, void *val)
{
	t_pma		*a;
	t_bitmap	*bmp;

	a = i->pma;
	if (a->canary != i->canary)
		ft_putendl_fd("USING INVALID ITERATOR", STDERR);
	bmp = &(a->bucket.flags);
	while (i->end > i->id && bitmap_get(bmp, i->end - 1) == false)
		i->end--;
	if (i->end <= i->id)
		return (false);
	bucket_get(&(a->bucket), i->end - 1, key, val);
	return (true);
}

bool			pmait_next(t_pmait *i, void *key, void *val)
{
	if (i->pma->canary != i->canary)
		ft_putendl_fd("USING INVALID ITERATOR", STDERR);
	if (pmait_get(i, key, val))
	{
		i->id++;
		return (true);
	}
	return (false);
}

bool			pmait_next_back(t_pmait *i, void *key, void *val)
{
	if (i->pma->canary != i->canary)
		ft_putendl_fd("USING INVALID ITERATOR", STDERR);
	if (pmait_get_back(i, key, val))
	{
		i->end--;
		return (true);
	}
	return (false);
}

