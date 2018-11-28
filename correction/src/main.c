/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lgarczyn <lgarczyn@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/09/20 12:12:22 by lgarczyn          #+#    #+#             */
/*   Updated: 2018/10/11 00:00:28 by lgarczyn         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <unistd.h>
#include <time.h>
#include <strings.h>
#include <fcntl.h>
#include "data.h"

int i = 42;

void	print_err(ssize_t a, ssize_t b, int line, int i)
{
	printf("line:%i i:%i %li!=%li\n", line, i, a, b);
}

#define PRINT_ERR(a, b) do {\
	print_err((ssize_t)a, (ssize_t)b, __LINE__, i);\
} while (0)

#define CHECK_EQ(a, b) do {\
	if ((a) != (b)) PRINT_ERR(a, b);\
} while(0)

#define MEM_TEST_COUNT			1000
#define GET_MEM_TEST_SPREAD(x)	(x * x / MEM_TEST_COUNT)

#define TEST_ARRAY
#define TEST_ARRAY_BONUS
#define TEST_BITSET
#define TEST_BITSET_BONUS
#define TEST_QUEUE
#define TEST_SORTED
#define TEST_SORTED_BONUS
#define TEST_PMA
#define TEST_PMA_BONUS_IT
#define TEST_PMA_BONUS_IT_BACK
#define TEST_PMA_BONUS_MULTI

#define BUFFER_SIZE 12

//#define TARGET_LINUX

#ifdef TARGET_LINUX
#include <malloc.h>
size_t	get_allocated_size(void *ptr)
{
	return (malloc_usable_size(ptr));
}
#else
#include <malloc/malloc.h>
size_t	get_allocated_size(void *ptr)
{
	return (malloc_size(ptr));
}
#endif

typedef struct				s_mem_report
{
	size_t					current;
	size_t					max;
}							t_mem_report;

static t_mem_report			modify_mem_score(size_t score, bool increment, bool reset)
{
	static _Atomic size_t	mem_count = 0;
	static _Atomic size_t	mem_max = 0;
	t_mem_report			mem;

	if (score)
	{
		if (increment)
		{
			mem_count += score;
			if (mem_count > mem_max)
				mem_max = mem_count;
		}
		else
			mem_count -= score;
	}
	mem.current = mem_count;
	mem.max = mem_max;
	if (reset)
	{
		mem_count = 0;
		mem_max = 0;
	}
	return (mem);
}

#define CHECK_LEAKS(RESET) do {\
	CHECK_EQ(modify_mem_score(0, false, RESET).current, 0);\
} while(0)

static void		print_score(int percent)
{
	int			color;
	char		colors[] = {123, 122, 121, 120, 119, 118, 112, 106, 100, 94, 88};

	color = CLAMP(percent / 20, 0, 10);
	printf("\x1b[30;48;5;%dm%d%%\e[0m", colors[color], percent);
}

static void		print_max_memory(char *name, size_t baseline)
{
	size_t		max;
	int			percent;

	max = modify_mem_score(0, false, true).max;
	percent = max * 100 / baseline;
	printf("%s: %luB ", name, max);
	print_score(percent);
	printf("\n");
}

static void		print_used_time(char *name, double score, double baseline)
{
	int			percent;

	percent = (int)(score * 100.0 / baseline);
	printf("%s: %fs ", name, score);
	print_score(percent);
	printf("\n");
}

void			xfree(void *ptr)
{
	modify_mem_score((ssize_t)get_allocated_size(ptr), false, false);
	free(ptr);
}

void			*xmalloc(size_t size)
{
	void		*ptr;

	ptr = malloc(size);
	modify_mem_score((ssize_t)get_allocated_size(ptr), true, false);
	return (ptr);
}

#ifdef TEST_ARRAY

# define ARRAY_TESTS 200000
# define ARRAY_INC_TESTS (ARRAY_TESTS - 1)

void			test_array(void)
{
	t_array		a;
	char		ret[BUFFER_SIZE];
	char		buf[BUFFER_SIZE];
	int			len;
		size_t		count = 0;

	a = array();
	CHECK_EQ(array_len(&a), 0);
	array_free(&a);
	CHECK_LEAKS(false);
	CHECK_EQ(array_len(&a), 0);
	a = array();
	array_free(&a);
	CHECK_LEAKS(false);
	CHECK_EQ(array_reserve(&a, (size_t)-1), ERR_ALLOC);
	CHECK_EQ(array_reserve(&a, ARRAY_TESTS * 11), OK);
	array_free(&a);
	CHECK_LEAKS(false);
	CHECK_EQ(array_reserve(&a, ARRAY_TESTS * 11), OK);
	CHECK_EQ(array_len(&a), 0);
	for (int i = 0; i < ARRAY_TESTS; i++)
	{
		len = sprintf(buf, "%d", i) + 1;
		CHECK_EQ(array_push(&a, buf, len), OK);
		count += len;
		CHECK_EQ(count, array_len(&a));

		len = sprintf(buf, "%d", i + 1) + 1;
		CHECK_EQ(array_push(&a, buf, len + 1), OK);

		CHECK_EQ(array_pop(&a, ret, len + 1), OK);
		CHECK_EQ(strcmp(buf, ret), 0);
	}
	for (int i = ARRAY_INC_TESTS; i >= 0; i--)
	{
		len = sprintf(buf, "%d", i) + 1;
		CHECK_EQ(array_pop(&a, ret, len), OK);
		CHECK_EQ(strcmp(buf, ret), 0);
	}
	CHECK_EQ(array_len(&a), 0);
	array_free(&a);
	CHECK_EQ(array_len(&a), 0);
}

void			test_array_mem()
{
	t_array		a;
	t_array		b;
	int			j;
	int			j_max;

	a = array();
	for (int i = 0; i < MEM_TEST_COUNT; i++)
	{
		b = array();
		j_max = GET_MEM_TEST_SPREAD(i);
		for (j = 0; j < j_max; j++)
		{
			CHECK_EQ(array_push(&b, &j, sizeof(int)), OK);
		}
		CHECK_EQ(array_push(&a, &b, sizeof(t_array)), OK);
	}
	
	for (int i = MEM_TEST_COUNT - 1; i >= 0; i--)
	{
		CHECK_EQ(array_pop(&a, &b, sizeof(t_array)), OK);
		j_max = GET_MEM_TEST_SPREAD(i);
		for (j = j_max - 1; j >= 0 ; j--)
		{
			CHECK_EQ(array_pop(&b, &j, sizeof(int)), OK);
		}
		array_free(&b);
	}
	array_free(&a);
}

# ifdef TEST_ARRAY_BONUS

#  define ARRAY_B_TESTS 3000

void			test_array_bonus(void)
{
	t_array		a;
	char		ret[BUFFER_SIZE];
	char		buf[BUFFER_SIZE];
	int			len;
	
	a = array();
	for (int i = 0; i < ARRAY_B_TESTS; i++)
	{
		len = sprintf(buf, "%d", i) + 1;
		CHECK_EQ(array_insert(&a, buf, 0, len), OK);
		CHECK_EQ(array_remove(&a, ret, 0, len), OK);
		CHECK_EQ(strcmp(buf, ret), 0);
		CHECK_EQ(array_insert(&a, buf, 0, len), OK);
	}
	for (int i = 0; i < ARRAY_B_TESTS; i++)
	{
		len = sprintf(buf, "%d", i) + 1;
		CHECK_EQ(array_pop(&a, ret, len), OK);
		CHECK_EQ(strcmp(buf, ret), 0);
	}
	CHECK_EQ(array_len(&a), 0);
	for (int i = 1; i < ARRAY_B_TESTS; i++)
	{
		CHECK_EQ(array_push(&a, &i, sizeof(int)), OK);
		CHECK_EQ(array_len(&a) / sizeof(int), (t_uint)i);
	}
	CHECK_EQ(array_set_len(&a, 700 * sizeof(int)), OK);
	CHECK_EQ(array_len(&a) / sizeof(int), 700);
	CHECK_EQ(array_set_len(&a, ARRAY_B_TESTS * sizeof(int)), OK);
	CHECK_EQ(array_pop(&a, &i, sizeof(int)), OK);
	CHECK_EQ(i, 0);

	array_free(&a);
}
# endif
#endif

#ifdef TEST_BITSET

# define BITSET_TESTS 10000000

void			test_bitset()
{
	t_bitset	b;
	
	b = bitset();
	CHECK_EQ(bitset_len(&b), 0);
	bitset_free(&b);
	CHECK_EQ(bitset_set_len(&b, BITSET_TESTS), OK);
	CHECK_EQ(bitset_len(&b), BITSET_TESTS);
	for (int i = 0; i < BITSET_TESTS; i++)
	{
		bitset_set(&b, i, i % 3 || i % 7);
	}
	for (int i = 0; i < BITSET_TESTS; i++)
	{
		CHECK_EQ((int)bitset_get(&b, i), (int)((i % 3) || (i % 7)));
	}
	CHECK_EQ(bitset_set_len(&b, 0), OK);
	CHECK_EQ(bitset_set_len(&b, 8), OK);
	bitset_set(&b, 7, true);
	CHECK_EQ(bitset_set_len(&b, 7), OK);
	CHECK_EQ(bitset_set_len(&b, 8), OK);
	CHECK_EQ((int)bitset_get(&b, 7), (int)false);
	bitset_free(&b);
}

void			test_bitset_mem()
{
	t_bitset	b[MEM_TEST_COUNT];
		int			j;
	int			j_max;

	for (int i = 0; i < MEM_TEST_COUNT; i++)
	{
		b[i] = bitset();
		j_max = GET_MEM_TEST_SPREAD(i);
		CHECK_EQ(bitset_set_len(b + i, j_max), OK);
		for (j = 0; j < j_max; j++)
		{
			bitset_set(b + i, j, (j + i) % 3 == 0);
		}
	}

	for (int i = 0; i < MEM_TEST_COUNT; i++)
	{
		j_max = GET_MEM_TEST_SPREAD(i);
		for (j = 0; j < j_max; j++)
		{
			CHECK_EQ(bitset_get(b + i, j), (j + i) % 3 == 0);
		}
		bitset_free(b + i);
	}
}

# ifdef TEST_BITSET_BONUS

# define BITSET_TESTS_B 1000000

void			test_bitset_bonus(void)
{
	t_bitset	b;
	
	b = bitset();
	CHECK_EQ(bitset_len(&b), 0);
	bitset_free(&b);
	CHECK_EQ(bitset_len(&b), 0);
	bitset_push(&b, true);
	CHECK_EQ(bitset_len(&b), 1);
	bitset_free(&b);
	b = bitset();
	bitset_free(&b);
	CHECK_EQ(bitset_reserve(&b, BITSET_TESTS_B / 100), OK);
	CHECK_EQ(bitset_len(&b), 0);
	for (int i = 0; i < BITSET_TESTS_B; i++)
	{
		bitset_push(&b, i % 2);
		bitset_push(&b, i % 3);
		bitset_push(&b, i % 4);
		bitset_push(&b, i % 5);
		CHECK_EQ(bitset_set_safe(&b, i * 4 + 3, i % 6), OK);
	}
	bool o_b;
	for (int i = 0; i < BITSET_TESTS_B; i++)
	{
		CHECK_EQ(bitset_get(&b, i * 4 + 0), !!(i % 2));
		CHECK_EQ(bitset_get(&b, i * 4 + 1), !!(i % 3));
		CHECK_EQ(bitset_get(&b, i * 4 + 2), !!(i % 4));
		CHECK_EQ(bitset_get(&b, i * 4 + 3), !!(i % 6));

		CHECK_EQ(bitset_get_safe(&b, i * 4 + 0, &o_b), OK);
		CHECK_EQ(o_b, !!(i % 2));
		CHECK_EQ(bitset_get_safe(&b, i * 4 + 1, &o_b), OK);
		CHECK_EQ(o_b, !!(i % 3));
		CHECK_EQ(bitset_get_safe(&b, i * 4 + 2, &o_b), OK);
		CHECK_EQ(o_b, !!(i % 4));
		CHECK_EQ(bitset_get_safe(&b, i * 4 + 3, &o_b), OK);
		CHECK_EQ(o_b, !!(i % 6));
	}
	CHECK_EQ(bitset_get_safe(&b, BITSET_TESTS_B * 4, &o_b), ERR_SIZE);
	CHECK_EQ(bitset_set_safe(&b, BITSET_TESTS_B * 4, false), ERR_SIZE);
	for (int i = BITSET_TESTS_B - 1; i >= 0; i--)
	{
		CHECK_EQ(bitset_pop(&b, &o_b), OK);
		CHECK_EQ(o_b, !!(i % 6));
		CHECK_EQ(bitset_pop(&b, &o_b), OK);
		CHECK_EQ(o_b, !!(i % 4));
		CHECK_EQ(bitset_pop(&b, &o_b), OK);
		CHECK_EQ(o_b, !!(i % 3));
		CHECK_EQ(bitset_pop(&b, &o_b), OK);
		CHECK_EQ(o_b, !!(i % 2));
	}
	CHECK_EQ(bitset_pop(&b, &o_b), ERR_SIZE);
	bitset_free(&b);
}

# endif
#endif

#ifdef			TEST_QUEUE

#define QUEUE_TESTS 100000
#define QUEUE_TESTS_INC (QUEUE_TESTS - 1)

void			test_queue_spe(bool push_back, bool pop_back, bool reserve)
{
	t_queue		a;
	int			ret;
	
	a = queue(sizeof(int));
	queue_free(&a);
	a = queue(sizeof(int));
	queue_free(&a);
	if (reserve)
	{
		CHECK_EQ(queue_reserve(&a, QUEUE_TESTS), OK);
		CHECK_EQ(queue_len(&a), 0);
	}
	for (int i = 0; i < QUEUE_TESTS; i++)
	{
		if (push_back)
			CHECK_EQ(queue_push_back(&a, &i), OK);
		else
			CHECK_EQ(queue_push_front(&a, &i), OK);
		CHECK_EQ(queue_len(&a), (unsigned int)i + 1);
	}
	for (int i = 0; i < QUEUE_TESTS; i++)
	{
		if (pop_back)
			CHECK_EQ(queue_pop_back(&a, &ret), OK);
		else
			CHECK_EQ(queue_pop_front(&a, &ret), OK);
		CHECK_EQ(queue_len(&a), QUEUE_TESTS_INC - (unsigned int)i);
		CHECK_EQ(ret, (push_back == pop_back ? QUEUE_TESTS_INC - i : i));
	}
	queue_free(&a);
}

void			test_queue_perf()
{
	t_queue		a;
	int			ret;
	
	a = queue(sizeof(int));
	queue_free(&a);
	a = queue(sizeof(int));
	queue_free(&a);
	for (int i = 0; i < 1000; i++)
		CHECK_EQ(queue_push_back(&a, &i), 0);
	
	for (int i = 0; i < QUEUE_TESTS * 10; i++)
	{
		CHECK_EQ(queue_pop_back(&a, &ret), OK);
		CHECK_EQ(queue_push_front(&a, &ret), OK);
	}

	for (int i = 0; i < 1000; i++)
	{
		CHECK_EQ(queue_pop_front(&a, &ret), 0);
		CHECK_EQ(ret, i);
	}
		
	queue_free(&a);
}

void			test_queue(void)
{
	test_queue_spe(false, false, false);
	test_queue_spe(false, true, false);
	test_queue_spe(true, false, false);
	test_queue_spe(true, true, false);


	test_queue_spe(false, false, true);
	test_queue_spe(false, true, true);
	test_queue_spe(true, false, true);
	test_queue_spe(true, true, true);

	test_queue_perf();
}

void			test_queue_mem()
{
	t_queue		a;
	t_queue		b;
		int			j;
	int			j_max;

	a = queue(sizeof(t_queue));
	for (int i = 0; i < MEM_TEST_COUNT; i++)
	{
		b = queue(sizeof(int));
		j_max = GET_MEM_TEST_SPREAD(i);
		for (j = 0; j < j_max; j++)
		{
			CHECK_EQ(queue_push_back(&b, &j), OK);
		}
		CHECK_EQ(queue_push_back(&a, &b), OK);
	}
	
	for (int i = 0; i < MEM_TEST_COUNT; i++)
	{
		CHECK_EQ(queue_pop_front(&a, &b), OK);
		j_max = GET_MEM_TEST_SPREAD(i);
		for (j = 0; j < j_max; j++)
		{
			CHECK_EQ(queue_pop_front(&b, &j), OK);
		}
		queue_free(&b);
	}
	queue_free(&a);

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
	bzero(buffer, BUFFER_SIZE);
	*(int*)buffer = i;
	(void)max;
}

void			desc(char *buffer, int i, int max)
{
	bzero(buffer, BUFFER_SIZE);
	*(int*)buffer = max - 1 - i;
}

void			gray(char *buffer, int i, int max)
{
	bzero(buffer, BUFFER_SIZE);
	if ((max & (max - 1)) != 0)
		printf("max is not a power of 2\n");
	*(int*)buffer = i ^ (i >> 1);
}

void			asc_str(char *buffer, int i, int max)
{
	bzero(buffer, BUFFER_SIZE);
	sprintf(buffer, "%i", i);
	(void)max;
}

void			desc_str(char *buffer, int i, int max)
{
	bzero(buffer, BUFFER_SIZE);
	sprintf(buffer, "%i", max - 1 - i);
}

void			gray_str(char *buffer, int i, int max)
{
	bzero(buffer, BUFFER_SIZE);
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

#define SORTED_TESTS (1 << 10)
#define SORTED_TESTS_INC (SORTED_TESTS - 1)

#ifdef TEST_SORTED

void			sorted_check(t_sorted *a, t_reverse r, bool reversed)
{
	CHECK_EQ(sorted_len(a), SORTED_TESTS);
	for (int i = 0; i < SORTED_TESTS; i++)
	{
		int j = reversed ? SORTED_TESTS_INC - i : i;
		
		int got = r(sorted_get(a, i));
		CHECK_EQ(j, got);
	}
}

void			sorted_check_delete(t_sorted *a, t_order o, t_reverse r)
{
	char		buffer1[BUFFER_SIZE];
	char		buffer2[BUFFER_SIZE];
	t_sorteden	res;
	size_t		index;

	for (int i = 0; i < SORTED_TESTS; i++)
	{
		o(buffer1, i, SORTED_TESTS);

		res = sorted_search(a, buffer1);
		CHECK_EQ(res.found, true);
		index = res.index;
		CHECK_EQ(strncmp((const char*)sorted_get(a, index), buffer1, BUFFER_SIZE), 0);
		res = sorted_delete(a, buffer1, buffer2);
		CHECK_EQ(res.found, true);
		CHECK_EQ(res.index, index);
		res = sorted_search(a, buffer1);
		CHECK_EQ(res.found, false);
		CHECK_EQ(res.index, index);
		CHECK_EQ(r(buffer1), r(buffer2));
	}
	o(buffer1, SORTED_TESTS, SORTED_TESTS);
	CHECK_EQ(sorted_search(a, buffer1).found, false);
	CHECK_EQ(sorted_len(a), 0);
}

void			sorted_fill(t_sorted *a, t_order o)
{
	char		buffer[BUFFER_SIZE];
	
	CHECK_EQ(sorted_reserve(a, (size_t)-1), ERR_ALLOC);
	CHECK_EQ(sorted_reserve(a, SORTED_TESTS / 10), OK);
	CHECK_EQ(sorted_len(a), 0);
	for (int i = 0; i < SORTED_TESTS; i++)
	{
		o(buffer, i, SORTED_TESTS);
		CHECK_EQ(sorted_insert(a, buffer), OK);
	}
}

void			sorted_fill_delete(t_sorted *a, t_order o, t_reverse r)
{
	char		buffer1[BUFFER_SIZE];
	char		buffer2[BUFFER_SIZE];
	
	for (; i < SORTED_TESTS_INC; i++)
	{
		o(buffer1, i, SORTED_TESTS);
		CHECK_EQ(sorted_insert(a, buffer1), OK);
		o(buffer1, i + 1, SORTED_TESTS);
		CHECK_EQ(sorted_insert(a, buffer1), OK);
		CHECK_EQ(sorted_delete(a, buffer1, NULL).found, true);
		CHECK_EQ(sorted_insert(a, buffer1), OK);
		sorted_delete(a, buffer1, buffer2);

		CHECK_EQ(r(buffer1), r(buffer2));
	}
	o(buffer1, SORTED_TESTS_INC, SORTED_TESTS);
	CHECK_EQ(sorted_insert(a, buffer1), OK);
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
		size = sizeof(char) * BUFFER_SIZE;
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
	sorted_fill(&a, o);
	sorted_fill_delete(&a, o, rev);
	sorted_check(&a, rev, less_pred == false);
	sorted_check_delete(&a, o, rev);
	sorted_fill_delete(&a, o, rev);
	sorted_free(&a);
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

int				sorted_less(t_sorted *a, t_sorted *b)
{
	return (sorted_len(a) < sorted_len(b));
}

void			test_sorted_mem()
{
	t_sorted		a;
	t_sorted		b;
	const t_sorted	*b_ptr;
		int				j;
	int				j_max;
	const int		*j_ptr;

	a = sorted((t_predicate)sorted_less, sizeof(t_sorted));
	for (int i = 0; i < 1000; i++)
	{
		b = sorted(lt, sizeof(int));
		j_max = i;
		for (j = 0; j < j_max; j++)
		{
			CHECK_EQ(sorted_insert(&b, &j), OK);
		}
		CHECK_EQ(sorted_insert(&a, &b), OK);
	}
	
	for (int i = 0; i < 1000; i++)
	{
		b_ptr = sorted_get(&a, 0);
		j_max = i;
		for (j = 0; j < j_max; j++)
		{
			j_ptr = sorted_get(b_ptr, j);
			CHECK_EQ(*j_ptr, j);
		}
		if (sorted_delete_index(&a, 0, &b) == OK)
			sorted_free(&b);
		else
			PRINT_ERR(ERR_MISSING, OK);
	}
	sorted_free(&a);

}

# ifdef TEST_SORTED_BONUS

void			sorted_fill_hint(t_sorted *a, t_order o)
{
	char		buffer[BUFFER_SIZE];
		t_uint		index;
	bool		start;

	o(buffer, 0, SORTED_TESTS);
	CHECK_EQ(sorted_insert(a, buffer), OK);

	index = sorted_search(a, buffer).index;

	o(buffer, 1, SORTED_TESTS);
	CHECK_EQ(sorted_insert(a, buffer), OK);

	if (index == sorted_search(a, buffer).index)
		start = true;
	else
		start = false;

	for (int i = 2; i < SORTED_TESTS; i++)
	{
		o(buffer, i, SORTED_TESTS);
		CHECK_EQ(sorted_insert_hint(a, buffer, start ? 0 : i), OK);
	}
}

void			sorted_check_pop(t_sorted *a, t_reverse r, bool reversed)
{
	char		buffer[BUFFER_SIZE];

	for (t_uint i = 0;i < SORTED_TESTS; i++)
	{
		int j = reversed ? i : SORTED_TESTS_INC - i;
		CHECK_EQ(sorted_pop(a, buffer), OK);
		int got = r(buffer);
		CHECK_EQ(j, got);
		CHECK_EQ(sorted_len(a), SORTED_TESTS_INC - i);
	}
	CHECK_EQ(sorted_len(a), 0);
}

void			sorted_check_delete_index(t_sorted *a, t_order o, t_reverse r)
{
	char		buffer1[BUFFER_SIZE];
	char		buffer2[BUFFER_SIZE];
	t_sorteden	res;
	size_t		index;

	for (t_uint i = 0; i < SORTED_TESTS; i++)
	{
		o(buffer1, i, SORTED_TESTS);

		res = sorted_search(a, buffer1);
		CHECK_EQ(res.found, true);
		index = res.index;
		CHECK_EQ(strncmp((const char*)sorted_get(a, index), buffer1, BUFFER_SIZE), 0);
		CHECK_EQ(sorted_delete_index(a, index, buffer2), OK);
		res = sorted_search(a, buffer1);
		CHECK_EQ(res.found, false);
		CHECK_EQ(res.index, index);
		CHECK_EQ(r(buffer1), r(buffer2));
	}
	o(buffer1, SORTED_TESTS, SORTED_TESTS);
	CHECK_EQ(sorted_delete_index(a, 0, NULL), ERR_SIZE);
	CHECK_EQ(sorted_len(a), 0);
}

void			test_sorted_bonus_spe(bool less_pred, bool str, t_order o)
{
	t_sorted	a;
	t_uint		size;
	t_predicate	pred;
	t_reverse	rev;

	a = sorted(&lt, sizeof(int));
	sorted_free(&a);
	if (str)
	{
		size = sizeof(char) * BUFFER_SIZE;
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
	sorted_free(&a);
	sorted_fill_hint(&a, o);
	sorted_check(&a, rev, less_pred == false);
	sorted_check_pop(&a, rev, less_pred == false);
	sorted_fill_hint(&a, o);
	sorted_check_delete_index(&a, o, rev);
	sorted_free(&a);
}

void			test_sorted_bonus(void)
{
	test_sorted_bonus_spe(false, false, asc);
	test_sorted_bonus_spe(false, false, desc);
	test_sorted_bonus_spe(false, false, gray);
	test_sorted_bonus_spe(true, false, asc);
	test_sorted_bonus_spe(true, false, desc);
	test_sorted_bonus_spe(true, false, gray);

	test_sorted_bonus_spe(false, true, asc_str);
	test_sorted_bonus_spe(false, true, desc_str);
	test_sorted_bonus_spe(false, true, gray_str);
	test_sorted_bonus_spe(true, true, asc_str);
	test_sorted_bonus_spe(true, true, desc_str);
	test_sorted_bonus_spe(true, true, gray_str);
}

# endif
#endif

#ifdef TEST_PMA

# define PMA_TESTS (1 << 11)
# define PMA_TESTS_INC (PMA_TESTS - 1)

void			pma_check_pop(t_pma *a, t_reverse r, bool reversed)
{
	char		buf_key[BUFFER_SIZE];
	char		buf_val[BUFFER_SIZE];

	for (int i = 0; i < PMA_TESTS / 2; i++)
	{
		int j = reversed ? i : PMA_TESTS_INC - i;
		if (pma_pop_back(a, buf_key, buf_val) != OK)
			printf("pop returned err before time\n");
		int got = r(buf_key);
		CHECK_EQ(got, j);
	}

	for (int i = 0; i < PMA_TESTS / 2; i++)
	{
		int j = reversed ? PMA_TESTS_INC - i : i;
		if (pma_pop_front(a, buf_key, buf_val) != OK)
			printf("pop returned err before time\n");
		int got = r(buf_key);
		CHECK_EQ(got, j);
	}

	if (pma_len(a) != 0)
		printf("check pop non-empty\n");
	if (pma_pop_back(a, NULL, NULL) != ERR_SIZE)
		printf("pop returned OK when it should be empty\n");
	if (pma_pop_front(a, NULL, NULL) != ERR_SIZE)
		printf("pop returned OK when it should be empty\n");
}

void			pma_check_delete(t_pma *a, t_order o, t_reverse r)
{
	char		key_search_buf[BUFFER_SIZE];
	char		key_found_buf[BUFFER_SIZE];
	int			val_found;
	
	for (int i = 0; i < PMA_TESTS; i++)
	{
		o(key_search_buf, i, PMA_TESTS);
		if (pma_delete(a, key_search_buf, key_found_buf, &val_found) != OK)
		{
			printf("error: %i not found\n", i);
			PRINT_ERR(PMA_TESTS - i, pma_len(a));
			continue;
		}
		int key_inserted = r(key_search_buf);
		int key_found = r(key_found_buf);
		CHECK_EQ(key_inserted, key_found);
		CHECK_EQ(i, val_found);
	}
}

void			pma_check_get(t_pma *a, t_order o, t_reverse r)
{
	char		key_search_buf[BUFFER_SIZE];
	char		key_found_buf[BUFFER_SIZE];
	int			val_found;
	
	CHECK_EQ(pma_len(a), PMA_TESTS);
	for (int i = 0; i < PMA_TESTS; i++)
	{
		o(key_search_buf, i, PMA_TESTS);
		if (pma_get(a, key_search_buf, key_found_buf, &val_found) != OK)
		{
			printf("error: %i not found\n", i);
			PRINT_ERR(PMA_TESTS - i, pma_len(a));
			continue;
		}
		int key_inserted = r(key_search_buf);
		int key_found = r(key_found_buf);
		CHECK_EQ(key_inserted, key_found);
		CHECK_EQ(i, val_found);
	}
	o(key_search_buf, PMA_TESTS, PMA_TESTS);
	CHECK_EQ(pma_get(a, key_search_buf, NULL, NULL), ERR_MISSING);
	CHECK_EQ(pma_len(a), PMA_TESTS);
}

void			pma_fill(t_pma *a, t_order o)
{
	char		buffer[BUFFER_SIZE];

	for (int i = 0; i < PMA_TESTS; i++)
	{
		o(buffer, i, PMA_TESTS);
		CHECK_EQ(pma_insert(a, buffer, &i), OK);
	}
}

void			pma_fill_delete(t_pma *a, t_order o, t_reverse r)
{
	char		key_inserted_buf[BUFFER_SIZE];
	int			val_inserted;
	char		key_found_buf[BUFFER_SIZE];
	int			val_found;
	
	for (int i = 0; i < PMA_TESTS_INC; i++)
	{
		o(key_inserted_buf, i, PMA_TESTS);
		val_inserted = i;

		CHECK_EQ(pma_insert(a, key_inserted_buf, &val_inserted), OK);
		o(key_inserted_buf, i + 1, PMA_TESTS);
		CHECK_EQ(pma_insert(a, key_inserted_buf, &val_inserted), OK);
		CHECK_EQ(pma_delete(a, key_inserted_buf, NULL, NULL), OK);
		CHECK_EQ(pma_insert(a, key_inserted_buf, &val_inserted), OK);
		pma_delete(a, key_inserted_buf, key_found_buf, &val_found);
		pma_len(a);
		int key_inserted = r(key_inserted_buf);
		int key_found = r(key_found_buf);
		CHECK_EQ(key_inserted, key_found);
		CHECK_EQ(val_inserted, val_found);
	}
	o(key_inserted_buf, PMA_TESTS_INC, PMA_TESTS);
	val_inserted = PMA_TESTS_INC;
	CHECK_EQ(pma_insert(a, key_inserted_buf, &val_inserted), OK);
}

void			test_pma_spe(bool reversed, bool str, t_order o)
{
	t_pma		a;
	t_uint		size;
	t_predicate	pred;
	t_reverse	rev;

	a = pma(&lt, sizeof(int), sizeof(int));
	pma_free(&a);
	if (str)
	{
		size = sizeof(char) * BUFFER_SIZE;
		pred = reversed ? &gt_str : &lt_str;
		rev = &reverse_str;
	}
	else
	{
		size = sizeof(int);
		pred = reversed ? &gt : &lt;
		rev = &reverse_int;
	}
	a = pma(pred, size, sizeof(int));
	pma_fill(&a, o);
	pma_check_get(&a, o, rev);
	pma_fill_delete(&a, o, rev);
	pma_check_get(&a, o, rev);
	CHECK_EQ(pma_len(&a), PMA_TESTS);
	pma_check_delete(&a, o, rev);
	CHECK_EQ(pma_len(&a), 0);
	pma_free(&a);
}

void			test_pma(void)
{
	test_pma_spe(false, false, asc);
	test_pma_spe(false, false, desc);
	test_pma_spe(false, false, gray);
	test_pma_spe(true, false, asc);
	test_pma_spe(true, false, desc);
	test_pma_spe(true, false, gray);

	test_pma_spe(false, true, asc_str);
	test_pma_spe(false, true, desc_str);
	test_pma_spe(false, true, gray_str);
	test_pma_spe(true, true, asc_str);
	test_pma_spe(true, true, desc_str);
	test_pma_spe(true, true, gray_str);
}

int				pma_less(t_pma *a, t_pma *b)
{
	return (pma_len(a) < pma_len(b));
}

void				print_int(int*ptr);

void				print_pma(t_pma *a)
{
	ft_putnbr(pma_len(a));
}

void				test_pma_mem()
{
	t_pma			a;
	t_pma			b;
		int				j;
	int				j_max;
	int				k;

	a = pma((t_predicate)lt, sizeof(int), sizeof(t_pma));
	for (int i = 0; i < MEM_TEST_COUNT; i++)
	{
		b = pma(lt, sizeof(int), 0);
		j_max = i;
		for (j = 0; j < j_max; j++)
		{
			pma_insert(&b, &j, NULL);
		}
		pma_insert(&a, &i, &b);
	}
	
	for (int i = 0; i < MEM_TEST_COUNT; i++)
	{
		j_max = i;
		CHECK_EQ(pma_get(&a, &i, NULL, &b), OK);
		for (j = 0; j < j_max; j++)
		{
			CHECK_EQ(pma_get(&b, &j, &k, NULL), OK);
			CHECK_EQ(j, k);
		}
		if (pma_delete(&a, &i, NULL, &b) == OK)
			pma_free(&b);
		else
			PRINT_ERR(ERR_MISSING, OK);
	}
	pma_free(&a);

}

# ifdef TEST_PMA_BONUS_IT

void			pmait_check_search(t_pma *a, t_order o, t_reverse r)
{
	char		key_search_buf[BUFFER_SIZE];
	char		key_found_buf[BUFFER_SIZE];
	int			val_found;
		t_pmaen		entry;

	CHECK_EQ(pma_len(a), PMA_TESTS);
	for (int i = 0; i < PMA_TESTS; i++)
	{
		o(key_search_buf, i, PMA_TESTS);
		entry = pma_search(a, key_search_buf);
		if (entry.found != true)
		{
			printf("error: %i not found\n", i);
			PRINT_ERR(PMA_TESTS - i, pma_len(a));
			continue;
		}
		pmait_next(&entry.it, key_found_buf, &val_found);
		int key_inserted = r(key_search_buf);
		int key_found = r(key_found_buf);
		CHECK_EQ(key_inserted, key_found);
		CHECK_EQ(i, val_found);
	}
	o(key_search_buf, PMA_TESTS, PMA_TESTS);
	CHECK_EQ(pma_search(a, key_search_buf).found, false);
	CHECK_EQ(pma_len(a), PMA_TESTS);
}

void			pmait_check(t_pma *a, t_reverse r, bool reversed)
{
	t_pmait	it;
	char		buffer[BUFFER_SIZE];
	int			val;
	int			i;

	i = 0;
	it = pmait(a);
	while (pmait_next(&it, buffer, &val))
	{
		int j = reversed ? PMA_TESTS_INC - i : i;
		int got = r(buffer);
		CHECK_EQ(j, got);
		i++;
	}
	CHECK_EQ(i, PMA_TESTS);
}

void			pmait_check_delete(t_pma *a, t_reverse r, bool reversed)
{
	t_pmait	it;
	char		buffer[BUFFER_SIZE];
	int			val;
	int			i;

	i = 0;
	it = pmait(a);
	while (pmait_delete(&it, buffer, &val))
	{
		int j = reversed ? PMA_TESTS_INC - i : i;
		int got = r(buffer);
		CHECK_EQ(j, got);
		i++;
	}
	CHECK_EQ(i, PMA_TESTS);
}

bool			pmait_cmp_one(t_pmait *a, t_pmait *b, int i)
{
	char		key_a[BUFFER_SIZE];
	char		key_b[BUFFER_SIZE];
	char		val_a[BUFFER_SIZE];
	char		val_b[BUFFER_SIZE];

	bzero(key_a, BUFFER_SIZE);
	bzero(key_b, BUFFER_SIZE);
	bzero(val_a, BUFFER_SIZE);
	bzero(val_b, BUFFER_SIZE);
	bool a_found = pmait_next(a, key_a, val_a);
	bool b_found = pmait_next(b, key_b, val_b);
	CHECK_EQ(a_found, b_found);
	if (a_found == false || b_found == false)
		return false;
	CHECK_EQ(memcmp(key_a, key_b, BUFFER_SIZE), 0);
	CHECK_EQ(memcmp(val_a, val_b, BUFFER_SIZE), 0);
	return (true);
}

void			pmait_cmp(t_pmait a, t_pmait b)
{
	int			i = 0;

	while (pmait_cmp_one(&a, &b, i))
	{
		i++;
	}
}

void			test_pmait_more()
{
	t_pma		a;
	t_order		o;
	int			first;
	t_pmait		found;
	t_pmait		all;

	o = asc;
	a = pma(&lt, sizeof(int), sizeof(int));
	pma_fill(&a, o);
	first = 0;

	t_pmaen en = pma_search(&a, &first);
	CHECK_EQ(en.found, true);
	if (en.found)
	{
		found = en.it;
		all = pmait(&a);
		pmait_cmp_one(&found, &all, 0);
	}
	pma_free(&a);
}

void			test_pmait_spe(bool reversed, bool str, t_order o)
{
	t_pma		a;
	t_uint		size;
	t_predicate	pred;
	t_reverse	rev;

	a = pma(&lt, sizeof(int), sizeof(int));
	pma_free(&a);
	if (str)
	{
		size = sizeof(char) * BUFFER_SIZE;
		pred = reversed ? &gt_str : &lt_str;
		rev = &reverse_str;
	}
	else
	{
		size = sizeof(int);
		pred = reversed ? &gt : &lt;
		rev = &reverse_int;
	}
	a = pma(pred, size, sizeof(int));
	pma_fill(&a, o);
	pmait_check(&a, rev, reversed);
	pmait_check_search(&a, o, rev);
	pmait_check_delete(&a, rev, reversed);
	pma_fill_delete(&a, o, rev);	
	pma_check_pop(&a, rev, reversed);
	pma_free(&a);
}

void			test_pmait(void)
{
	test_pmait_spe(false, false, asc);
	test_pmait_spe(false, false, desc);
	test_pmait_spe(false, false, gray);
	test_pmait_spe(true, false, asc);
	test_pmait_spe(true, false, desc);
	test_pmait_spe(true, false, gray);

	test_pmait_spe(false, true, asc_str);
	test_pmait_spe(false, true, desc_str);
	test_pmait_spe(false, true, gray_str);
	test_pmait_spe(true, true, asc_str);
	test_pmait_spe(true, true, desc_str);
	test_pmait_spe(true, true, gray_str);

	test_pmait_more();
}

#  ifdef TEST_PMA_BONUS_IT_BACK

void			pmait_back_check(t_pma *a, t_reverse r, bool reversed)
{
	t_pmait	it;
	char		buffer[BUFFER_SIZE];
	int			val;
	int			i;

	i = 0;
	it = pmait(a);
	while (pmait_next_back(&it, buffer, &val))
	{
		int j = !reversed ? PMA_TESTS_INC - i : i;
		int got = r(buffer);
		CHECK_EQ(j, got);
		i++;
	}
	CHECK_EQ(i, PMA_TESTS);
}

void			pmait_back_check_delete(t_pma *a, t_reverse r, bool reversed)
{
	t_pmait	it;
	char		buffer[BUFFER_SIZE];
	int			val;
	int			i;

	i = 0;
	it = pmait(a);
	while (pmait_delete_back(&it, buffer, &val))
	{
		int j = !reversed ? PMA_TESTS_INC - i : i;
		int got = r(buffer);
		CHECK_EQ(j, got);
		i++;
	}
	CHECK_EQ(i, PMA_TESTS);
}

bool			pmait_cmp_one_back(t_pmait *a, t_pmait *b, int i)
{
	char		key_a[BUFFER_SIZE];
	char		key_b[BUFFER_SIZE];
	char		val_a[BUFFER_SIZE];
	char		val_b[BUFFER_SIZE];

	bzero(key_a, BUFFER_SIZE);
	bzero(key_b, BUFFER_SIZE);
	bzero(val_a, BUFFER_SIZE);
	bzero(val_b, BUFFER_SIZE);
	bool a_found = pmait_next_back(a, key_a, val_a);
	bool b_found = pmait_next_back(b, key_b, val_b);
	CHECK_EQ(a_found, b_found);
	if (a_found == false || b_found == false)
		return false;
	CHECK_EQ(memcmp(key_a, key_b, BUFFER_SIZE), 0);
	CHECK_EQ(memcmp(val_a, val_b, BUFFER_SIZE), 0);
	return (true);
}

bool			pmait_cmp_one_front_back(t_pmait *front, t_pmait *back, int i)
{
	char		key_a[BUFFER_SIZE];
	char		key_b[BUFFER_SIZE];
	char		val_a[BUFFER_SIZE];
	char		val_b[BUFFER_SIZE];

	bzero(key_a, BUFFER_SIZE);
	bzero(key_b, BUFFER_SIZE);
	bzero(val_a, BUFFER_SIZE);
	bzero(val_b, BUFFER_SIZE);
	bool a_found = pmait_next(front, key_a, val_a);
	bool b_found = pmait_next_back(back, key_b, val_b);
	CHECK_EQ(a_found, b_found);
	if (a_found == false || b_found == false)
		return false;
	CHECK_EQ(memcmp(key_a, key_b, BUFFER_SIZE), 0);
	CHECK_EQ(memcmp(val_a, val_b, BUFFER_SIZE), 0);
	return (true);
}

void			pmait_cmp_back(t_pmait a, t_pmait b)
{
	int			i = 0;

	while (pmait_cmp_one_back(&a, &b, i))
	{
		i++;
	}
}

void			test_pmait_back_more()
{
	t_pma		a;
	t_order		o;
	int			first;
	int			mid;
	int			last;
	
	o = asc;
	a = pma(&lt, sizeof(int), sizeof(int));
	pma_fill(&a, o);
	first = 0;
	mid = PMA_TESTS / 2;
	last = PMA_TESTS_INC;

	t_pmaen en = pma_search(&a, &mid);
	CHECK_EQ(en.found, true);
	if (en.found)
	{
		t_pmait it_a = pma_range(&a, &mid, NULL);
		t_pmait it_b = en.it;
		pmait_cmp_one(&it_a, &it_b, 0);
	}

	pmait_cmp(pma_range(&a, &mid, &last), pma_range(&a, &mid, NULL));
	pmait_cmp_back(pma_range(&a, &mid, &last), pma_range(&a, &mid, NULL));

	pmait_cmp(pma_range(&a, &first, &last), pmait(&a));
	pmait_cmp(pma_range(&a, NULL, &last), pmait(&a));
	pmait_cmp(pma_range(&a, &first, NULL), pmait(&a));
	pmait_cmp(pma_range(&a, NULL, NULL), pmait(&a));

	pmait_cmp(pma_range(&a, &mid, &last), pma_range(&a, &mid, NULL));
	pmait_cmp(pma_range(&a, &first, &mid), pma_range(&a, NULL, &mid));

	t_pmait it = pma_range(&a, &last, &first);
	CHECK_EQ(pmait_next(&it, NULL, NULL), false);
	CHECK_EQ(pmait_next_back(&it, NULL, NULL), false);
	
	char		key_buf_i[BUFFER_SIZE];
	char		key_buf_j[BUFFER_SIZE];

	for (int i = 0; i < PMA_TESTS; i += 2)
	{
		o(key_buf_i, i, PMA_TESTS);
		for (int j = i; j < PMA_TESTS; j += 2)
		{
			o(key_buf_j, j, PMA_TESTS);

			t_pmait it_r_i = pma_range(&a, key_buf_i, key_buf_j);
			t_pmait it_r_j = it_r_i;
			t_pmaen en_i = pma_search(&a, key_buf_i);
			t_pmaen en_j = pma_search(&a, key_buf_j);

			if (en_i.found && en_j.found)
			{
				t_pmait it_i = en_i.it;
				t_pmait it_j = en_j.it;

				pmait_cmp_one(&it_i, &it_r_i, i);
				pmait_cmp_one_front_back(&it_j, &it_r_j, i);
			}
			else
			{
				CHECK_EQ(en_i.found, true);
				CHECK_EQ(en_j.found, true);
			}
		}
	}
	pma_free(&a);
}

void			test_pmait_back_spe(bool reversed, bool str, t_order o)
{
	t_pma		a;
	t_uint		size;
	t_predicate	pred;
	t_reverse	rev;

	a = pma(&lt, sizeof(int), sizeof(int));
	pma_free(&a);
	if (str)
	{
		size = sizeof(char) * BUFFER_SIZE;
		pred = reversed ? &gt_str : &lt_str;
		rev = &reverse_str;
	}
	else
	{
		size = sizeof(int);
		pred = reversed ? &gt : &lt;
		rev = &reverse_int;
	}
	a = pma(pred, size, sizeof(int));
	pma_fill(&a, o);
	pmait_back_check(&a, rev, reversed);
	pmait_back_check_delete(&a, rev, reversed);
	pma_free(&a);
}

void			test_pmait_back(void)
{
	test_pmait_back_spe(false, false, asc);
	test_pmait_back_spe(false, false, desc);
	test_pmait_back_spe(false, false, gray);
	test_pmait_back_spe(true, false, asc);
	test_pmait_back_spe(true, false, desc);
	test_pmait_back_spe(true, false, gray);

	test_pmait_back_spe(false, true, asc_str);
	test_pmait_back_spe(false, true, desc_str);
	test_pmait_back_spe(false, true, gray_str);
	test_pmait_back_spe(true, true, asc_str);
	test_pmait_back_spe(true, true, desc_str);
	test_pmait_back_spe(true, true, gray_str);

	test_pmait_back_more();
}

#  endif // TEST_PMA_BONUS_IT_BACK
# endif // TEST_PMA_BONUS_IT


void			putnbr(int n)
{
	printf("%i", n);
	fflush(NULL);
}

void			print_int(int *i)
{
	putnbr(*i);
}

void			print_char(char *i)
{
	putnbr(*i);
}

# ifdef TEST_PMA_BONUS_IT

int				ft_getch()
{
	int			c;
	static bool	failed;

	if (failed == false)
		fcntl(0, F_SETFL, fcntl(0, F_GETFL) | O_NONBLOCK);
	
	c = getchar();

	fcntl(0, F_SETFL, fcntl(0, F_GETFL) & ~O_NONBLOCK);

	failed = c < 0;
	return (c);
}

void			test_pmait_manual(t_pmait it)
{
	bool		to_update;
	int			out_key;
	int			out_val;

	to_update = false;
	while (1)
	{
		switch (ft_getch())
		{
			case 'r': it = pmait(it.pma); break ;
			case 'n':
				if (pmait_next(&it, &out_key, &out_val))
					printf("%i:%i\n", out_key, out_val);
				else
					printf("it reached end\n");
				break ;
			case 'd':
				if (pmait_delete(&it, &out_key, &out_val))
					printf("%i:%i\n", out_key, out_val);
				else
					printf("it reached end\n");
				break ;
#  ifdef TEST_PMA_BONUS_IT_BACK
			case 'p':
				if (pmait_next_back(&it, &out_key, &out_val))
					printf("%i:%i\n", out_key, out_val);
				else
					printf("it reached end\n");
				break ;
			case 'b':
				if (pmait_delete_back(&it, &out_key, &out_val))
					printf("%i:%i\n", out_key, out_val);
				else
					printf("it reached end\n");
				break ;
#  endif // TEST_PMA_BONUS_IT_BACK
			case 'q': return ;
			case -1: to_update = true;
		}
		if (to_update)
		{
			to_update = false;
			printf("\n\
%2$s r %1$s:reset \
%2$s n %1$s:next \
%2$s d %1$s:delete \
%3$s p %1$s:next_back \
%3$s b %1$s:delete_back \
%4$s q %1$s:quit\n", "\e[0m", "\e[1;42;39m", "\e[1;37;43m", "\e[1;41;39m");
			pmait_display(&it, (t_printer)print_int, (t_printer)print_int);
		}
	}
}

# endif // TEST_PMA_BONUS_IT

# ifdef TEST_PMA_BONUS_MULTI

void			test_pma_bonus_multi_spe(bool reversed, bool str, t_order o)
{
	t_pma		a;
	t_uint		size;
	t_predicate	pred;
	t_reverse	rev;

	a = pma(&lt, sizeof(int), sizeof(int));
	pma_free(&a);
	if (str)
	{
		size = sizeof(char) * BUFFER_SIZE;
		pred = reversed ? &gt_str : &lt_str;
		rev = &reverse_str;
	}
	else
	{
		size = sizeof(int);
		pred = reversed ? &gt : &lt;
		rev = &reverse_int;
	}
	a = pma(pred, size, sizeof(int));
	pma_fill(&a, o);
	pma_check_get(&a, o, rev);
	pma_fill_delete(&a, o, rev);
	pma_check_get(&a, o, rev);
	CHECK_EQ(pma_len(&a), PMA_TESTS);
	pma_check_delete(&a, o, rev);
	CHECK_EQ(pma_len(&a), 0);
	pma_fill(&a, o);
	pma_fill_delete(&a, o, rev);
	pma_fill(&a, o);
	pma_fill_delete(&a, o, rev);
	CHECK_EQ(pma_len(&a), PMA_TESTS * 4);
	pma_check_delete(&a, o, rev);
	pma_check_delete(&a, o, rev);
	pma_check_delete(&a, o, rev);
	pma_check_delete(&a, o, rev);
	CHECK_EQ(pma_len(&a), 0);
	pma_free(&a);
}

void			test_pma_bonus_multi(void)
{
	test_pma_spe(false, false, asc);
	test_pma_spe(false, false, desc);
	test_pma_spe(false, false, gray);
	test_pma_spe(true, false, asc);
	test_pma_spe(true, false, desc);
	test_pma_spe(true, false, gray);

	test_pma_spe(false, true, asc_str);
	test_pma_spe(false, true, desc_str);
	test_pma_spe(false, true, gray_str);
	test_pma_spe(true, true, asc_str);
	test_pma_spe(true, true, desc_str);
	test_pma_spe(true, true, gray_str);
}

# endif // TEST_PMA_BONUS_MULTI

void			test_pma_manual(void)
{
	t_pma		a;
	int			key;
	int			key_b;
	int			val;
	int			out_key;
	int			out_val;
	bool		to_update;
	int			c;

	a = pma(&lt, sizeof(int), sizeof(int));
	srand(clock());
	to_update = false;
	while (1)
	{
		c = ft_getch();
		switch (c)
		{
			case 'r': pma_free(&a); a = pma(&lt, sizeof(int), sizeof(int)); break;
# ifdef TEST_PMA_BONUS_MULTI
			case 'm': pma_free(&a); a = multi_pma(&lt, sizeof(int), sizeof(int)); break;
# endif // TEST_PMA_BONUS_MULTI
			case 'g':
				scanf ("%d", &key);
				if (pma_get(&a, &key, &out_key, &out_val) == OK)
					printf("pma[%i] == %i\n", key, val);
				else
					printf("not found: %i\n", key);
				to_update = false;
				break ;
			case 'd':
				scanf ("%d", &key);
				if (pma_delete(&a, &key, &out_key, &out_val) == OK)
					printf("deleted {%i: %i}\n", out_key, out_val);
				else
					printf("not found: %i\n", key);
				break ;
			case 'i':
				scanf ("%d", &key);
				val = rand() / ((1 << 18) - 1);
				pma_insert(&a, &key, &val);
				break ;
			case 'j':
				scanf ("%d %d", &key, &val);
				pma_insert(&a, &key, &val);
				break ;
			case 'k': 
				key = rand() / ((1 << 18) - 1);
				val = rand() % 26;
				pma_insert(&a, &key, &val);
				break ;
			case 'o':
				for (int i = 0; i < 1000000; i++)
				{
					key = rand() / ((1 << 20) - 1);
					val = rand() % 26;
					if (rand() % 13 < 6)
						pma_delete(&a, &key, &key, &val);
					else
						pma_insert(&a, &key, &val);
				}
				break ;
			case '?':
				scanf("%i", &i);
				printf("changed i to %i\n", i);
				break;
# ifdef TEST_PMA_BONUS_IT
			case 'p':
				if (pma_pop_front(&a, &out_key, &out_val) == OK)
					printf("deleted {%i: %i}\n", out_key, out_val);
				else
					printf("empty\n");
				break ;
			case 'b':
				if (pma_pop_back(&a, &out_key, &out_val) == OK)
					printf("deleted {%i: %i}\n", out_key, out_val);
				else
					printf("empty\n");
				break ;
			case 's':
				scanf ("%d", &key);
				test_pmait_manual(pma_search(&a, &key).it);
				break ;
			case 't':
				test_pmait_manual(pmait(&a));
				break ;
#  ifdef TEST_PMA_BONUS_IT_BACK
			case 'x':
				scanf ("%d %d", &key, &key_b);
				test_pmait_manual(pma_range(&a, &key, &key_b));
				break ;
#  endif // TEST_PMA_BONUS_IT_BACK
# endif // TEST_PMA_BONUS_IT
			case 'q': return ;
			case -1: to_update = true;
		}
		if (to_update)
		{
			to_update = false;
			printf("\n\
%2$s r %1$s:reset  %3$s m %1$s:multi  \
%2$s g %1$s:get(key)          \
%2$s d %1$s:delete(key)\n\
%2$s i %1$s:insert(key, rand) \
%2$s j %1$s:insert(key, val)  \
%2$s k %1$s:insert(rand, rand)\n\
%2$s o %1$s:stress test       \
%3$s p %1$s:pop front         \
%3$s b %1$s:pop back\n\
%3$s s %1$s:search(key)       \
%3$s t %1$s:pmait             \
%3$s x %1$s:range(low, high)\n\
%4$s q %1$s:quit\n", "\e[0m", "\e[1;42;39m", "\e[1;37;43m", "\e[1;41;39m");
			pma_display(&a, (t_printer)print_int, (t_printer)print_int);
			printf("\n");
		}
	}
}

#endif // TEST_PMA

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

void		check_time(char *name, void (*fn)(), bool all, double baseline)
{
	clock_t	begin;
	clock_t	end;

	if (all || check_test(name))
	{
		begin = clock();

		fn();

		end = clock();
		print_used_time(name, (double)(end - begin) / CLOCKS_PER_SEC, baseline);
		CHECK_LEAKS(true);
	}
}

void		check_mem(char *name, void (*fn)(), bool all, size_t baseline)
{
	if (all || check_test(name))
	{
		fn();
		CHECK_LEAKS(false);
		print_max_memory(name, baseline);
	}
}

int			main(void)
{
	bool	all;

	all = check_test("all");
	
#ifdef TEST_ARRAY
	check_time("array", &test_array, all, 0.134236);
	check_mem("array mem", &test_array_mem, all, 1865680);
# ifdef TEST_ARRAY_BONUS
	check_time("array bonus", &test_array_bonus, all, 0.128956);
# endif // TEST_ARRAY_BONUS
#endif // TEST_ARRAY

#ifdef TEST_BITSET
	check_time("bitset", &test_bitset, all, 0.091664);
	check_mem("bitset mem", &test_bitset_mem, all, 57168);
# ifdef TEST_BITSET_BONUS
	check_time("bitset bonus", &test_bitset_bonus, all, 0.126755);
# endif // TEST_BITSET_BONUS
#endif // TEST_BITSET

#ifdef TEST_QUEUE
	check_time("queue", &test_queue, all, 0.110551);
	check_mem("queue mem", &test_queue_mem, all, 1873872);
#endif

#ifdef TEST_SORTED
 	check_time("sorted", &test_sorted, all, 0.224660);
	check_mem("sorted mem", &test_sorted_mem, all, 3014336);
# ifdef TEST_SORTED_BONUS
 	check_time("sorted bonus", &test_sorted_bonus, all, 0.167893);
# endif // TEST_SORTED_BONUS
#endif // TEST_SORTED

#ifdef TEST_PMA
	check_time("pma", &test_pma, all, 1.037202);
	check_mem("pma mem", &test_pma_mem, all, 6589456);
# ifdef TEST_PMA_BONUS_IT
	check_time("pmait", &test_pmait, all, 0.456048);
#  ifdef TEST_PMA_BONUS_IT_BACK
	check_time("pmait back", &test_pmait_back, all, 0.897609);
#  endif // TEST_PMA_BONUS_IT
# endif // TEST_PMA_BONUS_IT
# ifdef TEST_PMA_BONUS_MULTI
	check_time("pma multi", &test_pma_bonus_multi, all, 0.976539);
# endif // TEST_PMA_BONUS_MULTI
	if (check_test("pma manual"))
		test_pma_manual();
#endif // TEST_PMA

	printf("All checks done, press enter after checking for leaks\n");
	getchar();
	getchar();
	return (0);
}
