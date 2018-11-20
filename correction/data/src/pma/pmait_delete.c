/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pmait_delete.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lgarczyn <lgarczyn@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2014/11/07 16:18:53 by lgarczyn          #+#    #+#             */
/*   Updated: 2018/11/05 19:54:36 by lgarczyn         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

#include "pma_int.h"

bool			pmait_delete(t_pmait *i, void *key, void *val)
{
	if (i->pma->canary != i->canary)
		ft_putendl_fd("USING INVALID ITERATOR", STDERR);
	if (pmait_get(i, key, val))
	{
		bucket_delete(&(i->pma->bucket), i->id, &(i->id), &(i->end));
		i->pma->canary++;
		i->canary++;
		return (true);
	}
	return (false);
}

bool			pmait_delete_back(t_pmait *i, void *key, void *val)
{
	if (i->pma->canary != i->canary)
		ft_putendl_fd("USING INVALID ITERATOR", STDERR);
	if (pmait_get_back(i, key, val))
	{
		bucket_delete(&(i->pma->bucket), i->end - 1, &(i->id), &(i->end));
		i->pma->canary++;
		i->canary++;
		return (true);
	}
	return (false);
}
