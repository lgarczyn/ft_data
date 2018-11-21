/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memalloc.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lgarczyn <lgarczyn@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2014/11/04 06:46:58 by lgarczyn          #+#    #+#             */
/*   Updated: 2018/10/10 03:30:22 by lgarczyn         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include <stdlib.h>

void		*ft_memalloc(size_t size)
{
	void	*str;

	if (size == 0)
		return (NULL);
	str = xmalloc(size);
	if (!str)
		return (NULL);
	return (ft_memset(str, '\0', size));
}
