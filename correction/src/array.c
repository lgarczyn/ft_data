/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   array.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lgarczyn <lgarczyn@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/09/13 22:02:52 by lgarczyn          #+#    #+#             */
/*   Updated: 2018/09/14 01:10:53 by lgarczyn         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include "data.h"

t_array				array(void)
{
	t_array			out;

	ft_bzero(&out, sizeof(out));
	return (out);
}

void				array_free(t_array *a)
{
	free(a->data);
	*a = array();
}

int					array_push(t_array *a, const void *data, size_t size)
{
	size_t			new_pos;

	new_pos = a->pos + size;
	if (new_pos > a->size)
	{
		if (ft_realloc(&a->data, a->size, new_pos * 2))
			return (ERR_ALLOC);
		a->size = new_pos * 2;
	}
	ft_memcpy(a->data + a->pos, data, size);
	a->pos = new_pos;
	return (OK);
}

int					array_pop(t_array *a, void *data, size_t size)
{
	size_t			new_pos;

	if (a->pos < size)
		return (ERR_ARG);
	new_pos = a->pos - size;
	ft_memcpy(data, a->data + new_pos, size);
	if (new_pos <= a->size / 4)
	{
		if (ft_realloc(&a->data, a->size, a->size / 4) == OK)
		{
			a->size = a->size / 4;
		}
	}
	a->pos = new_pos;
	return (OK);
}

int					array_reserve(t_array *a, size_t s)
{
	if (s > a->size)
	{
		if (ft_realloc(&a->data, a->size, s))
			return (ERR_ALLOC);
	}
	return (OK);
}

size_t				array_len(const t_array *a, size_t word)
{
	return (a->pos / word);
}
