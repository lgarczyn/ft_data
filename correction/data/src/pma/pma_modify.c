/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pma_modify.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lgarczyn <lgarczyn@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2014/11/07 16:18:53 by lgarczyn          #+#    #+#             */
/*   Updated: 2018/11/05 19:54:39 by lgarczyn         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

#include "pma_int.h"

bool			pma_delete(t_pma *a, const void *key,
	void *out_key, void *out_val)
{
	t_pmaen	en;

	a->canary++;
	en = pma_search(a, key);
	if (en.found)
	{
		bucket_get(&(a->bucket), en.it.id, out_key, out_val);
		bucket_delete(&(a->bucket), en.it.id, NULL, NULL);
	}
	en.key = (void*)key;
	return (en.found);
}

int				pma_insert(t_pma *a, const void *key, const void *val)
{
	t_pmaen	en;

	a->canary++;
	en = pma_search(a, key);
	if (en.found)
	{
		bucket_set(&(a->bucket), en.it.id, key, val);
		return (OK);
	}
	else
	{
		if (bucket_insert(&(a->bucket), en.it.id, key, val))
			return (ERR_ALLOC);
		return (OK);
	}
}

