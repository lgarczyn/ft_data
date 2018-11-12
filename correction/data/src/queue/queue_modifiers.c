/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   queue_modifiers.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lgarczyn <lgarczyn@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/09/13 22:02:52 by lgarczyn          #+#    #+#             */
/*   Updated: 2018/11/05 19:54:35 by lgarczyn         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include "queue_int.h"

int					queue_realloc(t_queue *a, size_t new_size)
{
	void			*new_data;
	size_t			first_half;

	if (new_size < a->pos)
		return (ERR_SIZE);
	new_data = ft_memalloc(new_size);
	if (new_data == NULL)
		return (ERR_ALLOC);
	if (a->start + a->pos < a->size)
		ft_memmove(new_data, a->data + a->start, a->pos);
	else
	{
		first_half = a->size - a->start;
		ft_memmove(new_data, a->data + a->start, first_half);
		ft_memmove(new_data + first_half, a->data, a->pos - first_half);
	}
	a->start = 0;
	free(a->data);
	a->data = new_data;
	a->size = new_size;
	return (OK);
}

int					queue_push_back(t_queue *a, const void *data)
{
	size_t			new_pos;

	new_pos = a->pos + a->word;
	if (new_pos > a->size)
	{
		if (queue_realloc(a, new_pos * 2))
			return (ERR_ALLOC);
	}
	if (a->start + new_pos <= a->size)
		ft_memcpy(a->data + a->start + a->pos, data, a->word);
	else
		ft_memcpy(a->data + a->start - a->size + a->pos, data, a->word);
	a->pos = new_pos;
	return (OK);
}

int					queue_push_front(t_queue *a, const void *data)
{
	size_t			new_pos;

	new_pos = a->pos + a->word;
	if (new_pos > a->size)
	{
		if (queue_realloc(a, new_pos * 2))
			return (ERR_ALLOC);
	}
	if (a->start >= a->word)
		a->start = a->start - a->word;
	else
		a->start = a->size - a->word;
	ft_memcpy(a->data + a->start, data, a->word);
	a->pos = new_pos;
	return (OK);
}

int					queue_pop_back(t_queue *a, void *data)
{
	size_t			new_pos;
	size_t			index;

	if (a->pos < a->word)
		return (ERR_SIZE);
	new_pos = a->pos - a->word;
	index = a->start + new_pos;
	if (index >= a->size)
		index -= a->size;
	ft_memcpy(data, a->data + index, a->word);
	if (new_pos <= a->size / 4)
	{
		queue_realloc(a, a->size / 4);
	}
	a->pos = new_pos;
	return (OK);
}

int					queue_pop_front(t_queue *a, void *data)
{
	if (a->pos < a->word)
		return (ERR_SIZE);
	ft_memcpy(data, a->data + a->start, a->word);
	a->start = a->start + a->word;
	if (a->start >= a->size)
		a->start = 0;
	a->pos -= a->word;
	if (a->pos <= a->size / 4)
	{
		queue_realloc(a, a->size / 4);
	}
	return (OK);
}
