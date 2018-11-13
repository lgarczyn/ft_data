/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_putnbr_64.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lgarczyn <lgarczyn@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2014/11/05 22:27:48 by lgarczyn          #+#    #+#             */
/*   Updated: 2018/01/26 14:25:01 by lgarczyn         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include <unistd.h>

void			ft_putnbr_64(size_t n)
{
	static char	buffer[20];
	int			i;
	int			len;

	len = ft_unumlen(n);
	i = len - 1;
	while (i >= 0)
	{
		buffer[i--] = '0' + (n % 10);
		n /= 10;
	}
	if (write(1, buffer, len) == -1)
		ft_perror(NULL);
}
