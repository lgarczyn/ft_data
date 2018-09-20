/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lgarczyn <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/09/20 12:12:22 by lgarczyn          #+#    #+#             */
/*   Updated: 2018/09/20 12:12:23 by lgarczyn         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include <stdio.h>

void		test_array(void)
{
	t_array	a;
	char	*str;
	char	ret[10];

	a = array();
	for (int i = 0; i < 10000; i++)
	{
		str = ft_itoa(i);
		array_push(&a, str, ft_intlen(i) + 1);
		free(str);
	}
	for (int i = 9999; i >= 0; i--)
	{
		str = ft_itoa(i);
		array_pop(&a, ret, ft_intlen(i) + 1);
		if (ft_strcmp(str, ret))
			printf("bug: %i: %i\n", i, ft_strcmp(str, ret));
	}
}

void		test_queue(void)
{
	t_queue	a;
	int		ret;

	a = queue(sizeof(int));
	for (int i = 0; i < 10000; i++)
	{
		queue_push_back(&a, &i);
	}
	for (int i = 0; i < 10000; i++)
	{
		queue_pop_front(&a, &ret);
		if (ret != i)
			printf("bug: %i: %i\n", i, ret);
	}
	a = queue(sizeof(int));
	for (int i = 0; i < 10000; i++)
	{
		queue_push_front(&a, &i);
	}
	for (int i = 0; i < 10000; i++)
	{
		queue_pop_back(&a, &ret);
		if (ret != i)
			printf("bug: %i: %i\n", i, ret);
	}

	a = queue(sizeof(int));
	for (int i = 0; i < 10000; i++)
	{
		queue_push_back(&a, &i);
	}
	for (int i = 9999; i >= 0; i--)
	{
		queue_pop_back(&a, &ret);
		if (ret != i)
			printf("bug: %i: %i\n", i, ret);
	}
	a = queue(sizeof(int));
	for (int i = 0; i < 10000; i++)
	{
		queue_push_front(&a, &i);
	}
	for (int i = 9999; i >= 0; i--)
	{
		queue_pop_front(&a, &ret);
		if (ret != i)
			printf("bug: %i: %i\n", i, ret);
	}
}

int		main(void)
{
	test_array();
	test_queue();
	return (0);
}
