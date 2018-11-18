/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   bitset_accessors.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lgarczyn <lgarczyn@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/09/13 22:02:52 by lgarczyn          #+#    #+#             */
/*   Updated: 2018/11/05 19:54:46 by lgarczyn         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include "bitset_int.h"

bool				bitset_get(const t_bitset *a, size_t i)
{
	return (a->data[i / 8] & (1 << (i % 8)));
}

int					bitset_get_safe(const t_bitset *a, size_t i, bool *out)
{
	if (i < a->pos)
	{
		*out = bitset_get(a, i);
		return (OK);
	}
	return (ERR_SIZE);
}

void				bitset_set(t_bitset *a, size_t p, bool b)
{
	size_t			i;
	size_t			j;

	i = p / 8;
	j = p % 8;
	if (b)
		a->data[i] |= (1 << j);
	else
		a->data[i] &= ~(1 << j);
}

int					bitset_set_safe(t_bitset *a, size_t i, bool b)
{
	if (i < a->pos)
	{
		bitset_set(a, i, b);
		return (OK);
	}
	return (ERR_SIZE);
}
