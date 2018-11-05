/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   array_modifiers.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lgarczyn <lgarczyn@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/09/13 22:02:52 by lgarczyn          #+#    #+#             */
/*   Updated: 2018/11/05 19:54:26 by lgarczyn         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include "array_int.h"

int				array_move(t_array *a, size_t from, size_t to, size_t size)
{
	size_t		new_pos;

	check_array(a);
	if (from == to)
		return (OK);
	if (from + size > a->pos)
		return (ERR_ARG);
	new_pos = MAX(to + size, a->pos);
	if (new_pos > a->size)
	{
		if (ft_realloc(&a->data, a->pos, new_pos * 2))
			return (ERR_ALLOC);
		a->size = new_pos * 2;
	}
	ft_memmove(a->data + to, a->data + from, size);
	a->pos = new_pos;
	return (OK);
}

int				array_insert(t_array *a, const void *data,
	size_t i, size_t size)
{
	size_t		next_len;
	int			r;

	check_array(a);
	next_len = a->pos - i;
	if ((r = array_move(a, i, i + size, next_len)))
		return (r);

	ft_memcpy(a->data + i, data, size);
	return (OK);
}

int				array_remove(t_array *a, void *data,
	size_t i, size_t size)
{
	size_t		new_pos;
	size_t		next_len;

	check_array(a);
	if (i + size > a->pos)
		return (ERR_ARG);
	new_pos = a->pos - size;
	if (data)
		ft_memcpy(data, a->data + i, size);
	next_len = a->pos - (i + size);
	ft_memmove(a->data + i, a->data + i + size, next_len);
	if (new_pos <= a->size / 4)
	{
		if (ft_realloc(&a->data, a->pos, a->size / 4) == OK)
		{
			a->size = a->size / 4;
		}
	}
	a->pos = new_pos;
	return (OK);
}

int				array_reserve(t_array *a, size_t s)
{
	check_array(a);
	if (s > a->size)
	{
		if (ft_realloc(&a->data, a->pos, s))
			return (ERR_ALLOC);
		a->size = s;
	}
	return (OK);
}

