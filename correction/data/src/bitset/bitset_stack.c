/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   bitset_stack.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lgarczyn <lgarczyn@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/09/13 22:02:52 by lgarczyn          #+#    #+#             */
/*   Updated: 2018/11/05 19:54:45 by lgarczyn         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include "bitset_int.h"

int					bitset_push(t_bitset *a, bool b)
{
	if (a->pos + 1 >= a->size)
	{
		if (bitset_reserve(a, (a->pos + 1) * 2))
			return (ERR_ALLOC);
	}
	bitset_set(a, a->pos, b);
	a->pos++;
	return (OK);
}

int					bitset_pop(t_bitset *a, bool *data)
{
	size_t			new_pos;

	if (a->pos <= 0)
		return (ERR_SIZE);

	new_pos = a->pos - 1;

	*data = bitset_get(a, new_pos);

	if (new_pos <= a->size / 4)
		ft_realloc_down((void*)&a->data, a->pos, &a->size);

	a->pos = new_pos;
	return (OK);
}
