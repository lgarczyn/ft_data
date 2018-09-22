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

#define PRINT_ERR(i, j) do { printf("%s() %s:%i : %i != %i\n", __func__, __FILE__, __LINE__, i, j);} while (0)

void			test_array(void)
{
	t_array		a;
	char		*str;
	char		ret[10];

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
			PRINT_ERR(i, ft_strcmp(str, ret));
	}
	array_free(&a);
}

void			test_queue(void)
{
	t_queue		a;
	int			ret;

	a = queue(sizeof(int));
	for (int i = 0; i < 10000; i++)
	{
		queue_push_back(&a, &i);
	}
	for (int i = 0; i < 10000; i++)
	{
		queue_pop_front(&a, &ret);
		if (ret != i)
			PRINT_ERR(i, ret);
	}
	queue_free(&a);
	a = queue(sizeof(int));
	for (int i = 0; i < 10000; i++)
	{
		queue_push_front(&a, &i);
	}
	for (int i = 0; i < 10000; i++)
	{
		queue_pop_back(&a, &ret);
		if (ret != i)
			PRINT_ERR(i, ret);
	}
	queue_free(&a);
	a = queue(sizeof(int));
	for (int i = 0; i < 10000; i++)
	{
		queue_push_back(&a, &i);
	}
	for (int i = 9999; i >= 0; i--)
	{
		queue_pop_back(&a, &ret);
		if (ret != i)
			PRINT_ERR(i, ret);
	}
	queue_free(&a);
	a = queue(sizeof(int));
	for (int i = 0; i < 10000; i++)
	{
		queue_push_front(&a, &i);
	}
	for (int i = 9999; i >= 0; i--)
	{
		queue_pop_front(&a, &ret);
		if (ret != i)
			PRINT_ERR(i, ret);
	}
	queue_free(&a);
}

int				lt(const void *a, const void *b)
{
	return (*((int*)a) < *((int*)b));
}

int				gt(const void *a, const void *b)
{
	return (*((int*)a)> *((int*)b));
}

void			test_sorted(void)
{
	t_sorted	a;
	int			ret;

	//decreasing order check
	a = sorted(&gt, sizeof(int));
	for (int i = 9999; i >= 0; i--)
	{
		sorted_insert(&a, &i);
	}
	for (int i = 0; i < 10000; i++)
	{
		sorted_pop(&a, &ret);
		if (ret != i)
			PRINT_ERR(i, ret);
	}
	sorted_free(&a);
	a = sorted(&gt, sizeof(int));
	for (int i = 0; i < 10000; i++)
	{
		sorted_insert(&a, &i);
	}
	for (int i = 0; i < 10000; i++)
	{
		sorted_pop(&a, &ret);
		if (ret != i)
			PRINT_ERR(i, ret);
	}
	sorted_free(&a);

	//increasing order check
	a = sorted(&lt, sizeof(int));
	for (int i = 9999; i >= 0; i--)
	{
		sorted_insert(&a, &i);
	}
	for (int i = 9999; i >= 0; i--)
	{
		sorted_pop(&a, &ret);
		if (ret != i)
			PRINT_ERR(i, ret);
	}
	sorted_free(&a);
	a = sorted(&lt, sizeof(int));
	for (int i = 0; i < 10000; i++)
	{
		sorted_insert(&a, &i);
	}
	for (int i = 9999; i >= 0; i--)
	{
		sorted_pop(&a, &ret);
		if (ret != i)
			PRINT_ERR(i, ret);
	}
	sorted_free(&a);
	//varied insertion check
	a = sorted(&lt, sizeof(int));
	for (int i = 0; i < 5000; i++)
	{
		int j = 9999 - i;
		sorted_insert(&a, &i);
		sorted_insert(&a, &j);
	}
	for (int i = 9999; i >= 0; i--)
	{
		sorted_pop(&a, &ret);
		if (ret != i)
			PRINT_ERR(i, ret);
	}
	sorted_free(&a);
	a = sorted(&lt, sizeof(int));
	for (int i = 0; i < 10000; i++)
	{
		int j = i + 1;
		int k;
		sorted_insert(&a, &i);
		sorted_insert(&a, &j);
		sorted_pop(&a, &k);
		if (k != j)
			PRINT_ERR(j, k);
	}
	for (int i = 9999; i >= 0; i--)
	{
		sorted_pop(&a, &ret);
		if (ret != i)
			PRINT_ERR(i, ret);
	}
	sorted_free(&a);
	a = sorted(&lt, sizeof(int));
	for (int i = 0; i < 10000; i++)
	{
		int j = i + 1;

		sorted_insert(&a, &i);

		t_searchres r = sorted_search(&a, &i);
		if (r.index != (size_t)i || r.found == 0)
			PRINT_ERR(i, (int)r.index);

		r = sorted_search(&a, &j);
		if (r.index != (size_t)j || r.found)
			PRINT_ERR(j, (int)r.index);
	}
	sorted_free(&a);
}

int		main(void)
{
	test_array();
	test_queue();
	test_sorted();
	return (0);
}
