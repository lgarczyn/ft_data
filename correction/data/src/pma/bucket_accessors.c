/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   bucket_accessors.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lgarczyn <lgarczyn@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2014/11/07 16:18:53 by lgarczyn          #+#    #+#             */
/*   Updated: 2018/11/05 19:54:41 by lgarczyn         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

#include "pma_int.h"

void			bucket_set(t_bucket *b, size_t id,
	const void *key, const void *val)
{
	void		*ptr;

	ptr = bucket_at(b, id);
	ft_memmove(ptr, key, b->sizes.key);
	ft_memmove(ptr + b->sizes.key, val, b->sizes.val);
	bitset_set(&(b->flags), id, true);
}

void			bucket_get(t_bucket *b, size_t id,
	void *key, void *val)
{
	void		*ptr;

	ptr = bucket_at(b, id);
	if (key)
		ft_memmove(key, ptr, b->sizes.key);
	if (val)
		ft_memmove(val, ptr + b->sizes.key, b->sizes.val);
}

