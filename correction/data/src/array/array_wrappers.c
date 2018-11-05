/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   array_wrappers.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lgarczyn <lgarczyn@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/09/13 22:02:52 by lgarczyn          #+#    #+#             */
/*   Updated: 2018/11/05 19:54:47 by lgarczyn         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include "array_int.h"

int				array_push(t_array *a, const void *data, size_t size)
{
	check_array(a);
	return (array_insert(a, data, a->pos, size));
}

int				array_pop(t_array *a, void *data, size_t size)
{
	check_array(a);
	if (size > a->pos)
		return (ERR_ARG);
	return (array_remove(a, data, a->pos - size, size));
}
