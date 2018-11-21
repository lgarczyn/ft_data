/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   array.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lgarczyn <lgarczyn@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/09/13 22:02:52 by lgarczyn          #+#    #+#             */
/*   Updated: 2018/11/05 19:54:46 by lgarczyn         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include "array_int.h"

void			check_array(const t_array *a)
{
	if (a->warning || a->pos > a->size || (!a->size != !a->data))
	{
		ft_perror("CORRUPTED ARRAY\n");
	}
}

t_array			array(void)
{
	t_array		out;

	ft_bzero(&out, sizeof(out));
	return (out);
}

void			array_free(t_array *a)
{
	check_array(a);
	xfree(a->data);
	*a = array();
}

size_t			array_len(const t_array *a)
{
	check_array(a);
	return (a->pos);
}
