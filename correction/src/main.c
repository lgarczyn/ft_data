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
#include <stdlib.h>
#include <stdbool.h>

#define PRINT_ERR(i, j) do { printf("%s() %s:%i : %lu != %lu\n",\
	__func__, __FILE__, __LINE__, (size_t)i, (size_t)j);} while (0)

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
		free(str);
	}
	array_free(&a);
}

void			test_queue_spe(bool push_back, bool pop_back)
{
	t_queue		a;
	int			ret;

	a = queue(sizeof(int));
	for (int i = 0; i < 10000; i++)
	{
		if (push_back)
			queue_push_back(&a, &i);
		else
			queue_push_front(&a, &i);
	}
	for (int i = 0; i < 10000; i++)
	{
		if (pop_back)
			queue_pop_back(&a, &ret);
		else
			queue_pop_front(&a, &ret);
		if (ret != (push_back == pop_back ? 9999 - i : i))
			PRINT_ERR(i, ret);
	}
	queue_free(&a);
}

void			test_queue(void)
{
	test_queue_spe(false, false);
	test_queue_spe(false, true);
	test_queue_spe(true, false);
	test_queue_spe(true, true);
}

int				lt(const void *a, const void *b)
{
	return (*((int*)a) < *((int*)b));
}

int				gt(const void *a, const void *b)
{
	return (*((int *)a)> *((int *)b));
}

void			test_sorted_spe(bool less_pred, bool asc, bool split)
{
	t_sorted	a;
	t_searchres	res;
	int			i;
	int			j;
	int			k;
	int			ret;
	int			max;

	max = 10000;

	if (less_pred)
		a = sorted(&lt, sizeof(int));
	else
		a = sorted(&gt, sizeof(int));

	for (i = 0; i < 10000; i++)
	{
		j = 9999 - i;
		k = i + 1;

		if (split)
			if (asc)
			{
				sorted_insert(&a, &j);
				sorted_insert(&a, &i);
			}
			else
			{
				sorted_insert(&a, &i);
				sorted_insert(&a, &j);
			}
		else
		{
			if (asc)
				sorted_insert(&a, &i);
			else
				sorted_insert(&a, &j);
		}
		res = sorted_search(&a, &i);
		if (asc == false && split == false && less_pred)
		{
			if ((i < 5000 && res.index != 0 && res.found) ||
				(i >= 5000 && res.index != (size_t)i - 5000 && res.found == false))
				PRINT_ERR(0, res.index);
		}
		else if (less_pred)
		{
			if (res.index != (size_t)i || res.found != true)
				PRINT_ERR(0, res.index);
		}
		if (asc && split == false)
		{
			res = sorted_search(&a, &k);
			if (res.index != (size_t)k && res.index != false)
				PRINT_ERR(k, res.index);
		}
		/*sorted_insert(&a, &max);
		j = sorted_search(&a, &max).index;
		if (j != sorted_len(&a) - 1)
			PRINT_ERR(j, sorted_len(&a) - 1);
		sorted_pop(&a, &res);
		if (res != max)
			PRINT_ERR(res, max);*/
	}
	for (i = 0; i < 10000; i++)
	{
		sorted_pop(&a, &ret);
		if (ret != (less_pred ? 9999 - i : i))
			PRINT_ERR(i, ret);
	}
	sorted_free(&a);
}

void			test_sorted(void)
{
	test_sorted_spe(false, false, false);
	test_sorted_spe(false, true, false);
	test_sorted_spe(true, false, false);
	test_sorted_spe(true, true, false);
	test_sorted_spe(false, false, true);
	test_sorted_spe(false, true, true);
	test_sorted_spe(true, false, true);
	test_sorted_spe(true, true, true);
}

int		main(void)
{
	test_array();
	test_queue();
	test_sorted();
	printf("All checks done, press enter after checking for leaks\n");
	getchar();
	return (0);
}
