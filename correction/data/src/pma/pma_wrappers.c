/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pma_wrappers.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lgarczyn <lgarczyn@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2014/11/07 16:18:53 by lgarczyn          #+#    #+#             */
/*   Updated: 2018/11/05 19:54:37 by lgarczyn         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

#include "pma_int.h"

int				pma_ensure(t_pmaen *en, const void *data)
{
	if (en->it.pma->canary != en->it.canary)
		ft_putendl_fd("USING INVALID ITERATOR", STDERR);
	if (en->found == false)
	{
		if (bucket_insert(
			&(en->it.pma->bucket),
			en->it.id,
			en->key, data))
			return (ERR_ALLOC);

		en->it.pma->canary++;
		en->it.canary++;
		en->found = true;
	}
	return (OK);
}

bool			pma_pop_back(t_pma *a, void *key, void *val)
{
	t_pmait		it;

	it = pmait(a);
	if (pmait_get_back(&it, key, val) == false)
		return (false);
	pmait_delete_back(&it, NULL, NULL);
	a->canary++;
	return (true);
}

bool			pma_pop_front(t_pma *a, void *key, void *val)
{
	t_pmait		it;

	it = pmait(a);
	if (pmait_get(&it, key, val) == false)
		return (false);
	pmait_delete(&it, NULL, NULL);
	a->canary++;
	return (true);
}
