/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pma_tools.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lgarczyn <lgarczyn@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2014/11/07 16:18:53 by lgarczyn          #+#    #+#             */
/*   Updated: 2018/11/05 19:54:38 by lgarczyn         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

#include "pma_int.h"

void		*pma_at(t_pma *a, size_t index)
{
	return (bucket_at(&(a->bucket), index));
}

const void	*pma_cat(const t_pma *a, size_t index)
{
	return (bucket_cat(&(a->bucket), index));
}

void		pma_display(t_pma *a, t_printer print_key, t_printer print_val)
{
	size_t	i;
	char	key[12];
	int		val;
	t_pmait	it;

	bitset_display(&a->bucket.flags);
	ft_putnbr_64(pma_len(a));
	ft_putstr(": {");
	it = pmait(a);
	i = 0;
	while (pmait_next(&it, &key, &val))
	{
		print_key(&key);
		ft_putchar(':');
		print_val(&val);
		if (++i < pma_len(a))
			ft_putchar(' ');
	}
	ft_putstr("}\n");
}

void		pmait_display(t_pmait *it, t_printer print_key, t_printer print_val)
{
	size_t	i;

	ft_putspace(ft_unumlen(pma_size(it->pma)) + 3);
	i = 0;
	while (i < pma_size(it->pma))
	{
		if (i == it->id && i == it->end - 1)
			ft_putchar('x');
		else if (i == it->id)
			ft_putchar('>');
		else if (i == it->end - 1)
			ft_putchar('<');
		else if (i > it->id && i < it->end)
			ft_putchar('-');
		else
			ft_putchar(' ');
		i++;
	}
	ft_putchar('\n');
	pma_display(it->pma, print_key, print_val);
}
