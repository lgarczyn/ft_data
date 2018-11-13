/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   bitmap.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lgarczyn <lgarczyn@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/09/13 22:02:52 by lgarczyn          #+#    #+#             */
/*   Updated: 2018/11/05 19:54:44 by lgarczyn         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include "bitmap_int.h"

t_bitmap		bitmap(void)
{
	t_bitmap		out;

	ft_bzero(&out, sizeof(out));
	return (out);
}

void			bitmap_free(t_bitmap *a)
{
	free(a->data);
	*a = bitmap();
}

size_t			bitmap_len(const t_bitmap *a)
{
	return (a->pos);
}

void			bitmap_display(const t_bitmap *a)
{
	size_t		i;
	ft_putnbr_64(a->pos);
	ft_putstr(": [");
	i = 0;
	while (i < a->pos)
	{
		ft_putchar(bitmap_get(a, i++) ? 'X' : '_');
	}
	ft_putstr("]\n");
}

