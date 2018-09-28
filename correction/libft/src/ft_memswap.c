/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memswap.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lgarczyn <lgarczyn@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2014/11/03 19:14:18 by lgarczyn          #+#    #+#             */
/*   Updated: 2018/01/25 20:46:35 by lgarczyn         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void			*ft_memswap(void *dst, void *src, size_t len)
{
	size_t		i;
	char		*source;
	char		*destin;
	char		tmp;


	if (dst == NULL || src == NULL)
		return (dst);
	source = (char*)src;
	destin = (char*)dst;
	i = -1;
	while (++i < len)
	{
		tmp = destin[i];
		destin[i] = source[i];
		source[i] = tmp;
	}
	return (dst);
}