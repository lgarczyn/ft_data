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
** p is a pointer to a malloc_allocated pointer
** len is the current used part of the allocated pointer
** nlen is the new minimum usable size to allocate
** size will contain the actual new size after successful realloc
**
** if *ptr is null, it will always be allocated to nlen
** if not, its data will be transfered then the pointer freed
** if the data cannot fit, it is truncated
** the data is NOT automatically null terminated
** if malloc should fail, the data is unaffected, a non-zero value is returned
** value of *size is ignored, but should always be the old value of size
**   as it allows checking for useless realloc
**
** unlike the real realloc, a nlen of zero will never free the pointer,
** as *size will be set to a platform-adequate minimum allocation
*/

#include <stdio.h>

int				ft_realloc(void **p, size_t len, size_t nlen, size_t *size)
{
	void		*mem;
	size_t		real_size;

	real_size = ft_min_alloc(nlen);
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
** behaves like ft_realloc, except as nlen is less than len,
** both arguments are equivalent
*/

int				ft_realloc_down(void **ptr, size_t len, size_t *size)
{
	if (ft_realloc(ptr, len, len, size))
		return (ERR_ALLOC);
	return (0);
}
