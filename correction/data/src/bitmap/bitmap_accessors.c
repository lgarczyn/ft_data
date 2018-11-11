/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   bitmap_accessors.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lgarczyn <lgarczyn@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/09/13 22:02:52 by lgarczyn          #+#    #+#             */
/*   Updated: 2018/11/05 19:54:46 by lgarczyn         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include "bitmap_int.h"

bool				bitmap_get(const t_bitmap *a, size_t i)
{
	return (a->data[i / 8] & (1 << (i % 8)));
}

int					bitmap_get_safe(const t_bitmap *a, size_t i, bool *out)
{
	if (i < a->pos)
	{
		*out = bitmap_get(a, i);
		return (OK);
	}
	return (ERR_SIZE);
}

void				bitmap_set(t_bitmap *a, size_t p, bool b)
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

int					bitmap_set_safe(t_bitmap *a, size_t i, bool b)
{
	if (i < a->pos)
	{
		bitmap_set(a, i, b);
		return (OK);
	}
	return (ERR_SIZE);
}

