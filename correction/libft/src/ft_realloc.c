/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_realloc.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lgarczyn <lgarczyn@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2014/12/17 16:19:51 by lgarczyn          #+#    #+#             */
/*   Updated: 2018/01/25 20:46:19 by lgarczyn         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include <stdlib.h>


size_t		ft_min_alloc(size_t size)
{
	return (((size - 24) + 15) / 16 * 16 + 24);
}

/*
** if *ptr is null, it will always be allocated to new size
** if not, its data will be transfered, and freed
** if the data cannot fit, it is truncated
** the data is NOT automatically null terminated
** if malloc should fail, the data is unaffected, a non-zero value is returned
*/

int			ft_realloc(void **ptr, size_t old_size, size_t new_size)
{
	void		*mem;

	if (*ptr == NULL)
	{
		*ptr = ft_memalloc(new_size);
		if (!*ptr)
			return (ERR_ALLOC);
	}
	mem = ft_memalloc(new_size);
	if (mem == NULL)
		return (ERR_ALLOC);
	ft_memmove(mem, *ptr, MIN(new_size, old_size));
	free(*ptr);
	*ptr = mem;
	return (0);
}

/*
** if *ptr is null, it will always be allocated to at least *old_size * 2
** if *old_size is 0 it will be set to at least 24
** if malloc should fail, the data is unaffected, a non-zero value is returned
*/

int			ft_realloc_double(void **ptr, size_t *old_size)
{
	size_t	new_size;

	new_size = ft_min_alloc(*old_size * REALLOC_GROWTH_FACTOR);
	if (ft_realloc(ptr, *old_size, new_size))
		return (ERR_ALLOC);
	*old_size = new_size;
	return (0);
}

/*
** if *ptr is null, it will always be allocated to at least *size * 2
** if *size is 0 it will be set to at least 24
** if malloc should fail, the data is unaffected, a non-zero value is returned
*/

int			ft_realloc_array(void **ptr, size_t pos, size_t *size)
{
	size_t	new_size;

	new_size = ft_min_alloc(*size * REALLOC_GROWTH_FACTOR);
	if (ft_realloc(ptr, pos, new_size))
		return (ERR_ALLOC);
	*size = new_size;
	return (0);
}

/*
** if *ptr is null, it will always be allocated to at least *size * 2
** if *size is 0 it will be set to at least 24
** if malloc should fail, the data is unaffected, a non-zero value is returned
*/

int			ft_realloc_down(void **ptr, size_t pos, size_t *size)
{
	size_t	new_size;

	new_size = ft_min_alloc(pos);
	if (new_size >= *size)
		return (0);
	if (ft_realloc(ptr, pos, new_size))
		return (ERR_ALLOC);
	*size = new_size;
	return (0);
}
