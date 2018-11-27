/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_min_alloc.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lgarczyn <lgarczyn@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2014/12/17 16:19:51 by lgarczyn          #+#    #+#             */
/*   Updated: 2018/01/25 20:46:19 by lgarczyn         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include <stdlib.h>

#include <printf.h>

/*
**  #include <malloc/malloc.h>
**  void		check_min_alloc(void)
**  {
**  	size_t	i;
**  	void	*ptr;
**  	size_t	a;
**  	size_t	b;
**
**  	i = 1;
**  	ptr = (void*)1;
**  	while (i < 0xFFFFFFFFFF)
**  	{
**  		ptr = malloc(i);
**  		if (!ptr)
**  			break ;
**  		a = malloc_size(ptr);
**  		b = ft_min_alloc(i);
**  		if (a != b)
**  			printf("0x%lx 0x%lx != 0x%lx\n", i, a, b);
**  		i += 1000;
**  		free(ptr);
**  	}
**  }
*/

/*
**	MAC OS min_alloc
*/

size_t		ft_min_alloc(size_t size)
{
	if (size > 0xFFFFFFFFFFFFFF)
		return ((size_t)-1);
	if (size > 0x1fc00)
	{
		if (size <= 0x20000)
			return (0x20000);
		return (ROUND_UP(size, 0x1000));
	}
	if (size > 1024)
	{
		if (size <= 0x600)
			return (0x600);
		return (ROUND_UP(size, 0x200));
	}
	if (size == 0)
		size = 1;
	return (ROUND_UP(size, 16));
}

/*
**	Linux min_alloc
*/

/*
**  size_t		ft_min_alloc(size_t size)
**  {
**  	if (size > 0xFFFFFFFFFFFFFF)
**  		return ((size_t)-1);
**  	return (ROUND_UP(size - 24, 16) + 24);
**  }
*/
