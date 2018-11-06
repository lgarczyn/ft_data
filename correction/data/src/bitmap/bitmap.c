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

t_bitmap		bitmap(void)
{
	t_bitmap		out;

	ft_bzero(&out, sizeof(out));
	return (out);
}

void			bitmap_free(t_bitmap *a)
{
	free(a->data);
	*a = bitmap();
}

int				bitmap_set_size(t_bitmap *a, size_t new_size)
{
	size_t		real_size;
	size_t		real_pos;

	real_pos = (a->pos + 7) / 8;
	real_size = ft_min_alloc((new_size + 7) / 8);

	if (ft_realloc((void**)&a->data, real_pos, real_size))
		return (ERR_ALLOC);
	a->size = real_size * 8;
	a->pos = MIN(a->pos, new_size);
	return (OK);
}

int				bitmap_reserve(t_bitmap *a, size_t new_size)
{
	//WHAT THE HELL AM I EVEN DOING
	new_size = MAX(new_size, a->pos);
	if (new_size <= a->size)
		return (OK);
	bitmap_set_size(a, new_size);
	return (OK);
}

size_t			bitmap_len(const t_bitmap *a)
{
	return (a->pos);
}

