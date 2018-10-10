/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lgarczyn <lgarczyn@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/09/20 12:12:22 by lgarczyn          #+#    #+#             */
/*   Updated: 2018/10/10 22:49:53 by lgarczyn         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include "data.h"
#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <stdlib.h>
#include <time.h>

#define PRINT_ERR(a, b) do { printf("line:%i i:%i %lu!=%lu\n",\
	__LINE__, i, (size_t)a, (size_t)b);} while (0)

// #define TEST_ARRAY
// #define TEST_BITMAP
// #define TEST_QUEUE
#define TEST_SORTED
#define TEST_PMA

#ifdef TEST_ARRAY

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

#endif

#ifdef TEST_BITMAP

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

#endif

#ifdef			TEST_QUEUE

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

#endif

int				lt(const void *a, const void *b)
{
	return (*((int*)a) < *((int*)b));
}

int				gt(const void *a, const void *b)
{
	return (*((int *)a) > *((int *)b));
}

int				lt_str(const void *a, const void *b)
{
	size_t		strla = strlen(a);
	size_t		strlb = strlen(b);
	
	if (strla != strlb)
		return (strla < strlb);
	return (strcmp(a, b) < 0);
}

int				gt_str(const void *a, const void *b)
{
	size_t		strla = strlen(a);
	size_t		strlb = strlen(b);
	
	if (strla != strlb)
		return (strla > strlb);
	return (strcmp(a, b) > 0);
}

typedef void	(*t_order)(char *buffer, int i, int max);

void			asc(char *buffer, int i, int max)
{
	*(int*)buffer = i;
	buffer[sizeof(int)] = '\0';
	(void)max;
}

void			desc(char *buffer, int i, int max)
{
	*(int*)buffer = max - 1 - i;
	buffer[sizeof(int)] = '\0';
}

void			gray(char *buffer, int i, int max)
{
	if ((max & (max - 1)) != 0)
		printf("max is not a power of 2\n");
	*(int*)buffer = i ^ (i >> 1);
	buffer[sizeof(int)] = '\0';
}

void			asc_str(char *buffer, int i, int max)
{
	sprintf(buffer, "%i", i);
	(void)max;
}

void			desc_str(char *buffer, int i, int max)
{
	sprintf(buffer, "%i", max - 1 - i);
}

void			gray_str(char *buffer, int i, int max)
{
	if ((max & (max - 1)) != 0)
		printf("max is not a power of 2\n");
	sprintf(buffer, "%i", i ^ (i >> 1));
}

typedef int		(*t_reverse)(const char *buffer);

int				reverse_int(const char *buffer)
{
	return (*(int*)buffer);
}

int				reverse_str(const char *buffer)
{
	return (atoi(buffer));
}

#define TEST_NUM (1 << 11)
#define TEST_NUM_INC (TEST_NUM - 1)

#ifdef TEST_SORTED


void			check(t_sorted *a, t_reverse r, bool reversed)
{
	for (int i = 0; i < TEST_NUM; i++)
	{
		int j = reversed ? TEST_NUM_INC - i : i;
		
		int got = r(sorted_cget(a, i));
		if (got != j)
			PRINT_ERR(j, got);
	}
}

void			check_pop(t_sorted *a, t_reverse r, bool reversed)
{
	char		buffer[12];

	for (int i = 0; i < TEST_NUM; i++)
	{
		int j = reversed ? i : TEST_NUM_INC - i;
		if (sorted_pop(a, &buffer))
			printf("pop returned non-zero\n");
		int got = r(buffer);
		if (got != j)
			PRINT_ERR(j, got);
	}
	if (sorted_len(a) != 0)
		printf("check pop non-empty\n");
}

void			check_delete(t_sorted *a, t_order o, t_reverse r)
{
	char		buffer1[12];
	char		buffer2[12];

	for (int i = 0; i < TEST_NUM; i++)
	{
		o(buffer1, i, TEST_NUM);
		if (sorted_delete(a, &buffer1, &buffer2).found == false)
		{
			PRINT_ERR(0, 1);
			continue;
		}
		int a = r(buffer1);
		int b = r(buffer2);
		if (a != b)
			PRINT_ERR(a, b);
	}
	if (sorted_len(a) != 0)
		printf("error check_delete 2 %lu!=0\n", sorted_len(a));
}

void			fill(t_sorted *a, t_order o)
{
	char		buffer[12];

	for (int i = 0; i < TEST_NUM; i++)
	{
		o(buffer, i, TEST_NUM);
		if (sorted_insert(a, &buffer))
			printf("sorted returned non-zero\n");
	}
}

void			fill_delete(t_sorted *a, t_order o, t_reverse r)
{
	char		buffer1[12];
	char		buffer2[12];

	for (int i = 0; i < TEST_NUM_INC; i++)
	{
		o(buffer1, i, TEST_NUM);
		if (sorted_insert(a, &buffer1))
			printf("sorted insert returned non-zero\n");
		o(buffer1, i + 1, TEST_NUM);
		if (sorted_insert(a, &buffer1))
			printf("sorted insert returned non-zero\n");
		sorted_delete(a, &buffer1, NULL);
		if (sorted_insert(a, &buffer1))
			printf("sorted insert returned non-zero\n");
		sorted_delete(a, &buffer1, &buffer2);
		int a = r(buffer1);
		int b = r(buffer2);
		if (a != b)
			PRINT_ERR(a, b);
	}
	o(buffer1, TEST_NUM_INC, TEST_NUM);
	if (sorted_insert(a, &buffer1))
		printf("sorted insert returned non-zero\n");
}

void			test_sorted_spe(bool less_pred, bool str, t_order o)
{
	t_sorted	a;
	t_uint		size;
	t_predicate	pred;
	t_reverse	rev;

	a = sorted(&lt, sizeof(int));
	sorted_free(&a);
	if (str)
	{
		size = sizeof(char) * 12;
		pred = less_pred ? &lt_str : &gt_str;
		rev = &reverse_str;
	}
	else
	{
		size = sizeof(int);
		pred = less_pred ? &lt : &gt;
		rev = &reverse_int;
	}
	a = sorted(pred, size);
	fill(&a, o);
	fill_delete(&a, o, rev);
	check(&a, rev, less_pred == false);
	check_delete(&a, o, rev);
	fill_delete(&a, o, rev);
	check_pop(&a, rev, less_pred == false);
}

void			test_sorted(void)
{
	test_sorted_spe(false, false, asc);
	test_sorted_spe(false, false, desc);
	test_sorted_spe(false, false, gray);
	test_sorted_spe(true, false, asc);
	test_sorted_spe(true, false, desc);
	test_sorted_spe(true, false, gray);

	test_sorted_spe(false, true, asc_str);
	test_sorted_spe(false, true, desc_str);
	test_sorted_spe(false, true, gray_str);
	test_sorted_spe(true, true, asc_str);
	test_sorted_spe(true, true, desc_str);
	test_sorted_spe(true, true, gray_str);
}

#endif

#ifdef TEST_PMA

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
	t_pma		a;
	int			n;
	char		s;
	int			out_key;
	char		out_val;
	bool		to_update;

	a = pma(&lt, sizeof(int), sizeof(char));
	srand(clock());
	to_update = true;
	while (1)
	{
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

#endif

bool		check_test(char *str)
{
	char	c;
	printf("check %s? [y/n]\n", str);
	while (1)
	{
		c = getchar();
		if (c == 'y')
			return (true);
		if (c == 'n')
			return (false);
	}
}

int			main(void)
{
	#ifdef TEST_ARRAY
	if (check_test("array"))
	 	test_array();
	#endif
	#ifdef TEST_BITMAP
	if (check_test("bitmap"))
		test_bitmap();
	#endif
	#ifdef TEST_QUEUE
	if (check_test("queue"))
		test_queue();
	#endif
	#ifdef TEST_SORTED
 	if (check_test("sorted"))
 		test_sorted();
	#endif
	#ifdef TEST_PMA
	if (check_test("pma"))
		test_pma();
	#endif
	printf("All checks done, press enter after checking for leaks\n");
	getchar();
	return (0);
}
