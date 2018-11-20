/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sorted_accessors.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lgarczyn <lgarczyn@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/09/13 22:02:52 by lgarczyn          #+#    #+#             */
/*   Updated: 2018/11/05 19:54:34 by lgarczyn         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include "sorted_int.h"

void			*sorted_get(t_sorted *a, size_t index)
{
	return (a->data + (index * a->word));
}

const void		*sorted_cget(const t_sorted *a, size_t index)
{
	return (a->data + (index * a->word));
}

int				sorted_pop(t_sorted *a, void *data)
{
	if (sorted_len(a) <= 0)
		return (ERR_SIZE);
	sorted_delete_index(a, sorted_len(a) - 1, data);
	return (OK);
}
