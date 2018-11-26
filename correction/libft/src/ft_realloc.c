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

/*
** if *ptr is null, it will always be allocated to new size
** if not, its data will be transfered, and freed
** if the data cannot fit, it is truncated
** the data is NOT automatically null terminated
** if malloc should fail, the data is unaffected, a non-zero value is returned
*/

#include <stdio.h>

int				ft_realloc(void **p, size_t len, size_t nlen, size_t *size)
{
	void		*mem;
	size_t		real_size;

	real_size = ft_min_alloc(nlen);
	// if (real_size == *size)
	// 	printf("useless fucking realloc\n");
		//bzero(*p + MIN(nlen, len), *size - MIN(nlen, len));
	if (*p == NULL)
	{
		*p = ft_memalloc(real_size);
		if (*p == NULL)
			return (ERR_ALLOC);
	}
	else
	{
		mem = ft_memalloc(real_size);
		if (mem == NULL)
			return (ERR_ALLOC);
		ft_memmove(mem, *p, MIN(nlen, len));
		xfree(*p);
		*p = mem;
	}
	*size = real_size;
	return (OK);
}

/*
** if *ptr is null, it will always be allocated to at least *size * 2
** if *size is 0 it will be set to at least 24
** if malloc should fail, the data is unaffected, a non-zero value is returned
*/

int			ft_realloc_down(void **ptr, size_t len, size_t *size)
{
	if (ft_realloc(ptr, len, len, size))
		return (ERR_ALLOC);
	return (0);
}
