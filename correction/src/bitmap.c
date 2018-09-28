/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   bitmap.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lgarczyn <lgarczyn@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/09/13 22:02:52 by lgarczyn          #+#    #+#             */
/*   Updated: 2018/09/14 01:10:53 by lgarczyn         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

t_bitmap			bitmap(void)
{
	t_bitmap			out;

	ft_bzero(&out, sizeof(out));
	return (out);
}

void				bitmap_free(t_bitmap *a)
{
	free(a->data);
	*a = bitmap();
}

int					bitmap_realloc(t_bitmap *a, size_t new_size)
{
	if (new_size < a->pos)
		return (ERR_ARG);
	if (ft_realloc((void**)&a->data,
		(a->size + 7) / 8,
		(new_size + 7) / 8))
		return (ERR_ALLOC);
	a->size = new_size;
	return (OK);
}

int					bitmap_push(t_bitmap *a, bool b)
{
	size_t			new_size;
	size_t			i;
	size_t			j;

	if (a->pos + 1 >= a->size)
	{
		new_size = MAX(a->size * 2, 64);
		if (bitmap_realloc(a, new_size))
			return (ERR_ALLOC);
	}
	i = a->pos / 8;
	j = a->pos % 8;
	if (b)
		a->data[i] |= (1 << j);
	else
		a->data[i] &= ~(1 << j);
	a->pos++;
	return (OK);
}

int					bitmap_pop(t_bitmap *a, bool *data)
{
	size_t			new_pos;

	if (a->pos <= 0)
		return (ERR_ARG);
	
	new_pos = a->pos - 1;

	*data = a->data[new_pos / 8] & (1 << (new_pos % 8));

	if (new_pos <= a->size / 4)
		bitmap_realloc(a, a->size / 8);
	
	a->pos = new_pos;
	return (OK);
}

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
	return (ERR_ARG);
}

size_t				bitmap_len(const t_bitmap *a)
{
	return (a->pos);
}