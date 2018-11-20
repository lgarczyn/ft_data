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

t_bitset		bitset(void)
{
	t_bitset		out;

	ft_bzero(&out, sizeof(out));
	return (out);
}

void			bitset_free(t_bitset *a)
{
	free(a->data);
	*a = bitset();
}

size_t			bitset_len(const t_bitset *a)
{
	return (a->pos);
}

void			bitset_display(const t_bitset *a)
{
	size_t		i;

	ft_putnbr_64(a->pos);
	ft_putstr(": [");
	i = 0;
	while (i < a->pos)
	{
		ft_putchar(bitset_get(a, i++) ? 'X' : '_');
	}
	ft_putstr("]\n");
}
