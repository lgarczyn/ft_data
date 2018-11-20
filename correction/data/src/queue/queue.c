/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   queue.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lgarczyn <lgarczyn@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/09/13 22:02:52 by lgarczyn          #+#    #+#             */
/*   Updated: 2018/11/05 19:54:34 by lgarczyn         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include "queue_int.h"

t_queue				queue(t_uint word)
{
	t_queue			out;

	ft_bzero(&out, sizeof(out));
	out.word = MAX(word, 1);
	return (out);
}

void				queue_free(t_queue *a)
{
	free(a->data);
	*a = queue(a->word);
}

size_t				queue_len(const t_queue *a)
{
	return (a->pos / a->word);
}

int					queue_reserve(t_queue *a, size_t new_size)
{
	new_size *= a->word;
	if (new_size > a->size)
	{
		new_size = ft_min_alloc(new_size);
		return (queue_realloc(a, new_size));
	}
	return (OK);
}
