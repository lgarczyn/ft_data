/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   bitset.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lgarczyn <lgarczyn@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/09/13 22:02:52 by lgarczyn          #+#    #+#             */
/*   Updated: 2018/11/05 19:54:44 by lgarczyn         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include "bitset_int.h"

static int		bitset_realloc(t_bitset *a, size_t new_size)
{
	size_t		real_new_size;
	size_t		real_pos;

	real_pos = DIV_RDUP(a->pos, 8);
	real_new_size = ft_min_alloc(DIV_RDUP(new_size, 8));
	if (a->size == real_new_size * 8)
		return (OK);
	if (ft_realloc((void**)&a->data, real_pos, real_new_size, &real_new_size))
		return (ERR_ALLOC);
	a->size = real_new_size * 8;
	return (OK);
}

int				bitset_set_len(t_bitset *a, size_t new_size)
{
	size_t		i;

	if (bitset_realloc(a, new_size))
		return (ERR_ALLOC);
	i = new_size;
	while (i < a->pos && i < ROUND_UP(new_size, 8))
		bitset_set(a, i++, false);
	a->pos = new_size;
	return (OK);
}

int				bitset_reserve(t_bitset *a, size_t new_size)
{
	if (new_size <= a->size)
		return (OK);
	if (bitset_realloc(a, new_size))
		return (ERR_ALLOC);
	return (OK);
}
