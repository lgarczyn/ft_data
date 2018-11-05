/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   bitmap_stack.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lgarczyn <lgarczyn@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/09/13 22:02:52 by lgarczyn          #+#    #+#             */
/*   Updated: 2018/11/05 19:54:45 by lgarczyn         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include "bitmap_int.h"

int					bitmap_push(t_bitmap *a, bool b)
{
	if (a->pos + 1 >= a->size)
	{
		if (bitmap_set_size(a, (a->pos + 1) * 2))
			return (ERR_ALLOC);
	}
	bitmap_set(a, a->pos, b);
	a->pos++;
	return (OK);
}

int					bitmap_pop(t_bitmap *a, bool *data)
{
	size_t			new_pos;

	if (a->pos <= 0)
		return (ERR_ARG);

	new_pos = a->pos - 1;

	*data = bitmap_get(a, new_pos);

	//put back when you figure out the min alloc
	//if (new_pos <= a->size / 4)
	//	bitmap_set_size(a, a->size / 8);

	a->pos = new_pos;
	return (OK);
}
