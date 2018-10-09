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
#include "data.h"
#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <stdlib.h>
#include <time.h>

#define PRINT_ERR(a, b) do { printf("%s:%i (i=%i): %lu != %lu\n",\
	__FILE__, __LINE__, i, (size_t)a, (size_t)b);} while (0)

void			test_array(void)
{
	t_array		a;
	char		*str;
	char		ret[10];

	a = array();
	array_free(&a);
	a = array();
	array_free(&a);
	for (int i = 0; i < 10000; i++)
	{
		str = ft_itoa(i);
		array_push(&a, str, ft_intlen(i) + 1);
		free(str);

		str = ft_itoa(i + 1);
		array_push(&a, str, ft_intlen(i + 1) + 1);

		array_pop(&a, ret, ft_intlen(i + 1) + 1);
		if (ft_strcmp(str, ret))
		{
			ft_putnstr(a.data, a.pos);
			ft_putchar('\n');
			printf("a %lu/%lu\n", a.pos, a.size);
			PRINT_ERR(i, ft_strcmp(str, ret));
		}
		free(str);
	}
	for (int i = 9999; i >= 0; i--)
	{
		str = ft_itoa(i);
		array_pop(&a, ret, ft_intlen(i) + 1);
		if (ft_strcmp(str, ret))
		{
			printf("a %lu/%lu\n", a.pos, a.size);
			PRINT_ERR(i, ft_strcmp(str, ret));
		}
		free(str);
	}
	array_free(&a);
	for (int i = 0; i < 10000; i++)
	{
		str = ft_itoa(i);
		array_insert(&a, str, 0, ft_intlen(i) + 1);
		array_remove(&a, ret, 0, ft_intlen(i) + 1);
		if (ft_strcmp(str, ret))
			PRINT_ERR(i, ft_strcmp(str, ret));
		array_insert(&a, str, 0, ft_intlen(i) + 1);
	}
	for (int j = 9999; j >= 0; j--)
	{
		int i = 9999 - j;
		str = ft_itoa(i);
		array_pop(&a, ret, ft_intlen(i) + 1);
		if (ft_strcmp(str, ret))
			PRINT_ERR(i, ft_strcmp(str, ret));
		free(str);
	}
}

void			test_bitmap(void)
{
	t_bitmap	b;

	b = bitmap();
	bitmap_free(&b);
	bitmap_push(&b, true);
	bitmap_free(&b);
	b = bitmap();
	bitmap_free(&b);
	for (int i = 0; i < 10000; i++)
	{
		bitmap_push(&b, i % 2);
		bitmap_push(&b, i % 3);
		bitmap_push(&b, i % 4);
		bitmap_push(&b, i % 5);
	}
	for (int i = 0; i < 10000; i++)
	{
		if (bitmap_get(&b, i * 4) != !!(i % 2) ||
			bitmap_get(&b, i * 4 + 1) != !!(i % 3) ||
			bitmap_get(&b, i * 4 + 2) != !!(i % 4) ||
			bitmap_get(&b, i * 4 + 3) != !!(i % 5))
		{
			PRINT_ERR(!!(i % 2), bitmap_get(&b, i * 4));
			PRINT_ERR(!!(i % 3), bitmap_get(&b, i * 4 + 1));
			PRINT_ERR(!!(i % 4), bitmap_get(&b, i * 4 + 2));
			PRINT_ERR(!!(i % 5), bitmap_get(&b, i * 4 + 3));
		}
	}
	for (int i = (10000 * 4) - 1; i >= 0; i--)
	{
		bool o_a;
		bool o_b;

		//o_a = bitmap_get(&b, i * 4);
		o_a = bitmap_get(&b, b.pos - 1);
		bitmap_pop(&b, &o_b);

		if (o_a != o_b)
			PRINT_ERR(i, (o_a << 1) | o_b);
	}

	bitmap_free(&b);
}

void			test_queue_spe(bool push_back, bool pop_back)
{
	t_queue		a;
	int			ret;

	a = queue(sizeof(int));
	queue_free(&a);
	a = queue(sizeof(int));
	queue_free(&a);
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

	max = 20000;

	a = sorted(&lt, sizeof(int));
	sorted_free(&a);
	if (less_pred)
	{
		a = sorted(&lt, sizeof(int));
		max = 20000;
	}
	else
	{
		a = sorted(&gt, sizeof(int));
		max = -20000;
	}
	sorted_free(&a);
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
		//printf("i: %i\n", i);
		// for (size_t i = 0; i < sorted_len(&a); i++)
		// 	printf("%i ", *(int*)sorted_cget(&a, i));
		// printf("\n");
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
		
		res = sorted_search(&a, &max);
		if (res.index != sorted_len(&a) || res.found != false)
			PRINT_ERR(res.index, sorted_len(&a));

		sorted_insert(&a, &max);
		
		res = sorted_search(&a, &max);
		if (res.index != sorted_len(&a) - 1 || res.found != true)
			PRINT_ERR(res.index, sorted_len(&a));
		
		sorted_pop(&a, &ret);
		if (ret != max)
			PRINT_ERR(ret, max);
		
		res = sorted_delete(&a, &max, NULL);
		if (res.found != true && res.index != sorted_len(&a))
			PRINT_ERR(res.index, sorted_len(&a));
		
		res = sorted_search(&a, &max);
		if (res.index != sorted_len(&a) || res.found != false)
			PRINT_ERR(res.index, sorted_len(&a));
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

int				bucket_rebalance(t_bucket *b);

void			pma_display(t_pma *a)
{
	size_t		i;
	bool		b;
	int			n;
	char		c;

	printf("\n%lu==%lu: [",
		bitmap_len(&(a->bucket.flags)),
		array_len(&(a->bucket.values), a->sizes.key + a->sizes.val));
	i = 0;
	while (bitmap_get_safe(&(a->bucket.flags), i, &b))
	{
		printf("%c", b ? 'X' : '_');
		i++;
	}
	
	printf("]\n%lu==%lu: {", pma_len(a), a->bucket.count);

	t_pma_it	it;

	it = pmait_first(a);
	while (pmait_next(&it, &n, &c)) {
		printf("%i:%c ", n, c);
		i++;
	}
	printf("}\n");
}


void			test_pma(void)
{
	//reproduce test_sorted
	//reproduce test_queue

	t_pma		a;
	int			n;
	char		s;
	int			out_key;
	char		out_val;
	bool		to_update;

	a = pma(&lt, sizeof(int), sizeof(char));
	srand(clock());
	to_update = true;
	while (1) {
		if (to_update)
			pma_display(&a);
		to_update = true;
		switch (getchar()) {
			case 'q': return ;
			case 'f': pma_free(&a); break;
			case 's':
				scanf ("%d",&n);
				printf("a[%lu] == %i\n", pma_search(&a, &n).it.id, n);
				to_update = false;
				break;
			case 'd': scanf ("%d",&n); pma_delete(&a, &n, &out_key, &out_val); break;
			case 'i': scanf ("%d%c",&n,&s); pma_insert(&a, &n, &s); break;
			case 'r': 
				n = rand();
				s = rand() % 26 + 'A';
				pma_insert(&a, &n, &s);
				to_update = false;
				break;
			case 'm':
				for (int i = 0; i < 1000000; i++)
				{	
					n = rand();
					s = rand() % 26 + 'A';
					if (rand() % 13 == 0)
						pma_delete(&a, &n, &n, &s);
					else
						pma_insert(&a, &n, &s);

				}

				break;
			default : to_update = false;

			// pma_replace(&a, void *key, void *val);
			// size_t				pma_len(const &a);
			// pmait_get(t_pma_it *i, void *key, void *val);
			// pmait_next(t_pma_it *i, void *key, void *val);
			// pmait_prev(t_pma_it *i, void *key, void *val);
			// pmait_delete(t_pma_it *i, void *key, void *val);
			// pma_ensure(t_pma_en *en, const void *data);
			// pmait_first(&a);
			// pmait_last(&a);
		}
	}
}

int		main(void)
{
// 	test_array();
// 	test_bitmap();
// 	test_queue();
// 	test_sorted();
	test_pma();
	printf("All checks done, press enter after checking for leaks\n");
	getchar();
	return (0);
}
