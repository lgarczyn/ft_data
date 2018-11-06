/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sorted_delete.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lgarczyn <lgarczyn@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/09/13 22:02:52 by lgarczyn          #+#    #+#             */
/*   Updated: 2018/11/06 00:06:13 by lgarczyn         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include "sorted_int.h"

void			sorted_delete_index(t_sorted *a, size_t index, void *out)
{
	size_t		new_pos;
	size_t		prev_len;
	size_t		next_len;
	void		*array_data;

	new_pos = a->pos - a->word;
	prev_len = index * a->word;
	next_len = new_pos - prev_len;
	array_data = a->data + prev_len;
	if (out)
		ft_memcpy(out, array_data, a->word);
	if (next_len)
		ft_memmove(array_data, array_data + a->word, next_len);
	if (a->pos <= a->size / 4)
		ft_realloc_down(&a->data, a->pos, &a->size);
	a->pos = new_pos;
}

t_searchres		sorted_delete(t_sorted *a, const void *data, void *out)
{
	t_searchres	res;

	res = sorted_search(a, data);
	if (res.found)
	{
		sorted_delete_index(a, res.index, out);
	}
	return (res);
}
