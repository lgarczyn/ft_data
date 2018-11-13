/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   bitmap.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lgarczyn <lgarczyn@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/09/13 22:02:52 by lgarczyn          #+#    #+#             */
/*   Updated: 2018/11/05 19:54:44 by lgarczyn         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include "bitmap_int.h"

static int		bitmap_realloc(t_bitmap *a, size_t new_size)
{
	size_t		real_new_size;
	size_t		real_pos;

	real_pos = DIV_RDUP(a->pos, 8);
	real_new_size = ft_min_alloc(DIV_RDUP(new_size, 8));
	if (ft_realloc((void**)&a->data, real_pos, real_new_size))
		return (ERR_ALLOC);
	a->size = real_new_size * 8;
	return (OK);
}

int				bitmap_set_len(t_bitmap *a, size_t new_size)
{
	size_t		i;

	if (bitmap_realloc(a, new_size))
		return (ERR_ALLOC);
	i = new_size;
	while (i < a->pos && i < ROUND_UP(new_size, 8))
		bitmap_set(a, i++, false);
	a->pos = new_size;
	return (OK);
}

int				bitmap_reserve(t_bitmap *a, size_t new_size)
{
	if (new_size <= a->size)
		return (OK);
	if (bitmap_realloc(a, new_size))
		return (ERR_ALLOC);
	return (OK);
}
