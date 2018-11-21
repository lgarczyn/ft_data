/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sorted.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lgarczyn <lgarczyn@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/09/13 22:02:52 by lgarczyn          #+#    #+#             */
/*   Updated: 2018/11/05 19:54:31 by lgarczyn         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include "sorted_int.h"

t_sorted		sorted(t_predicate predicate, t_uint word)
{
	t_sorted	out;

	ft_bzero(&out, sizeof(out));
	out.predicate = predicate;
	out.word = MAX(word, 1);
	return (out);
}

void			sorted_free(t_sorted *a)
{
	xfree(a->data);
	*a = sorted(a->predicate, a->word);
}

size_t			sorted_len(const t_sorted *a)
{
	return (a->pos / a->word);
}

int				sorted_reserve(t_sorted *a, size_t s)
{
	s *= a->word;
	if (s > a->size)
	{
		if (ft_realloc(&a->data, a->size, s))
			return (ERR_ALLOC);
		a->size = s;
	}
	return (OK);
}
