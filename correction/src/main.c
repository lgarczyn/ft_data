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
#include "data.h"

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

#define TEST_ARRAY
#define TEST_ARRAY_BONUS
#define TEST_BITSET
#define TEST_BITSET_BONUS
#define TEST_QUEUE
#define TEST_SORTED
#define TEST_SORTED_BONUS
#define TEST_PMA
#define TEST_PMA_BONUS_STACK
#define TEST_PMA_BONUS_IT
#define TEST_PMA_BONUS_IT_BACK

#define BUFFER_SIZE 12

#ifdef TEST_ARRAY

# define ARRAY_TESTS 200000
# define ARRAY_INC_TESTS (ARRAY_TESTS - 1)

void			test_array(void)
{
	t_array		a;
	char		ret[BUFFER_SIZE];
	char		buf[BUFFER_SIZE];
	int			len;
	int			i = 0;
	size_t		count = 0;

	a = array();
	CHECK_EQ(array_len(&a), 0);
	array_free(&a);
	CHECK_EQ(array_len(&a), 0);
	a = array();
	array_free(&a);
	//CHECK_EQ(array_reserve(&a, (size_t)-1), ERR_ALLOC);
	CHECK_EQ(array_reserve(&a, ARRAY_TESTS * 11), OK);
	CHECK_EQ(array_len(&a), 0);
	for (i = 0; i < ARRAY_TESTS; i++)
	{
		len = sprintf(buf, "%d", i) + 1;
		array_push(&a, buf, len);
		count += len;
		CHECK_EQ(count, array_len(&a));

		len = sprintf(buf, "%d", i + 1) + 1;
		array_push(&a, buf, len + 1);

		array_pop(&a, ret, len + 1);
		if (strcmp(buf, ret))
		{
			printf("%*.*s\n", (int)a.pos, (int)a.pos, (char*)a.data);
			printf("a %lu/%lu\n", a.pos, a.size);
			PRINT_ERR(i, strcmp(buf, ret));
		}
	}
	for (i = ARRAY_INC_TESTS; i >= 0; i--)
	{
		len = sprintf(buf, "%d", i) + 1;
		array_pop(&a, ret, len);
		if (strcmp(buf, ret))
		{
			printf("a %lu/%lu\n", a.pos, a.size);
			PRINT_ERR(0, strcmp(buf, ret));
		}
	}
	CHECK_EQ(array_len(&a), 0);
	array_free(&a);
	CHECK_EQ(array_len(&a), 0);
}

# ifdef TEST_ARRAY_BONUS

#  define ARRAY_B_TESTS 3000

void			test_array_bonus(void)
{
	t_array		a;
	char		ret[BUFFER_SIZE];
	char		buf[BUFFER_SIZE];
	int			len;
	int			i = 0;

	a = array();
	for (i = 0; i < ARRAY_B_TESTS; i++)
	{
		len = sprintf(buf, "%d", i) + 1;
		array_insert(&a, buf, 0, len);
		array_remove(&a, ret, 0, len);
		CHECK_EQ(strcmp(buf, ret), 0);
		array_insert(&a, buf, 0, len);
	}
	for (i = 0; i < ARRAY_B_TESTS; i++)
	{
		len = sprintf(buf, "%d", i) + 1;
		array_pop(&a, ret, len);
		CHECK_EQ(strcmp(buf, ret), 0);
	}
	CHECK_EQ(array_len(&a), 0);
	for (i = 1; i < ARRAY_B_TESTS; i++)
	{
		array_push(&a, &i, sizeof(int));
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
	int			i = 0;

	b = bitset();
	CHECK_EQ(bitset_len(&b), 0);
	bitset_free(&b);
	CHECK_EQ(bitset_set_len(&b, BITSET_TESTS), OK);
	CHECK_EQ(bitset_len(&b), BITSET_TESTS);
	for (i = 0; i < BITSET_TESTS; i++)
	{
		bitset_set(&b, i, i % 3 || i % 7);
	}
	for (i = 0; i < BITSET_TESTS; i++)
	{
		CHECK_EQ((int)bitset_get(&b, i), (int)((i % 3) || (i % 7)));
	}
	CHECK_EQ(bitset_set_len(&b, 0), OK);
	CHECK_EQ(bitset_set_len(&b, 8), OK);
	bitset_set(&b, 7, true);
	CHECK_EQ(bitset_set_len(&b, 7), OK);
	CHECK_EQ(bitset_set_len(&b, 8), OK);
	CHECK_EQ((int)bitset_get(&b, 7), (int)false);
}

# ifdef TEST_BITSET_BONUS

# define BITSET_TESTS_B 1000000

void			test_bitset_bonus(void)
{
	t_bitset	b;
	int			i = 0;

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
	for (i = 0; i < BITSET_TESTS_B; i++)
	{
		bitset_push(&b, i % 2);
		bitset_push(&b, i % 3);
		bitset_push(&b, i % 4);
		bitset_push(&b, i % 5);
		CHECK_EQ(bitset_set_safe(&b, i * 4 + 3, i % 6), OK);
	}
	bool o_b;
	for (i = 0; i < BITSET_TESTS_B; i++)
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
	for (i = BITSET_TESTS_B - 1; i >= 0; i--)
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
	int			i = 0;

	a = queue(sizeof(int));
	queue_free(&a);
	a = queue(sizeof(int));
	queue_free(&a);
	if (reserve)
	{
		CHECK_EQ(queue_reserve(&a, QUEUE_TESTS), OK);
		CHECK_EQ(queue_len(&a), 0);
	}
	for (i = 0; i < QUEUE_TESTS; i++)
	{
		if (push_back)
			queue_push_back(&a, &i);
		else
			queue_push_front(&a, &i);
		CHECK_EQ(queue_len(&a), (unsigned int)i + 1);
	}
	for (i = 0; i < QUEUE_TESTS; i++)
	{
		if (pop_back)
			queue_pop_back(&a, &ret);
		else
			queue_pop_front(&a, &ret);
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
		queue_pop_back(&a, &ret);
		queue_push_front(&a, &ret);
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

#define SORTED_TESTS (1 << 9)
#define SORTED_TESTS_INC (SORTED_TESTS - 1)

#ifdef TEST_SORTED

void			sorted_check(t_sorted *a, t_reverse r, bool reversed)
{
	int			i = 0;

	CHECK_EQ(sorted_len(a), SORTED_TESTS);
	for (i = 0; i < SORTED_TESTS; i++)
	{
		int j = reversed ? SORTED_TESTS_INC - i : i;
		
		int got = r(sorted_cget(a, i));
		CHECK_EQ(j, got);
	}
}

void			sorted_check_delete(t_sorted *a, t_order o, t_reverse r)
{
	char		buffer1[BUFFER_SIZE];
	char		buffer2[BUFFER_SIZE];
	t_sorteden	res;
	size_t		index;
	t_uint		i = 0;

	for (; i < SORTED_TESTS; i++)
	{
		o(buffer1, i, SORTED_TESTS);

		res = sorted_search(a, buffer1);
		CHECK_EQ(res.found, true);
		index = res.index;
		CHECK_EQ(strncmp((char*)sorted_get(a, index), buffer1, BUFFER_SIZE), 0);
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
	int			i = 0;

	CHECK_EQ(sorted_reserve(a, (size_t)-1), ERR_ALLOC);
	CHECK_EQ(sorted_reserve(a, SORTED_TESTS / 10), OK);
	CHECK_EQ(sorted_len(a), 0);
	for (i = 0; i < SORTED_TESTS; i++)
	{
		o(buffer, i, SORTED_TESTS);
		CHECK_EQ(sorted_insert(a, buffer), OK);
	}
}

void			sorted_fill_delete(t_sorted *a, t_order o, t_reverse r)
{
	char		buffer1[BUFFER_SIZE];
	char		buffer2[BUFFER_SIZE];
	int			i = 0;

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

void			sorted_fill_hint(t_sorted *a, t_order o)
{
	char		buffer[BUFFER_SIZE];
	int			i = 0;
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

	for (i = 2; i < SORTED_TESTS; i++)
	{
		o(buffer, i, SORTED_TESTS);
		CHECK_EQ(sorted_insert_hint(a, buffer, start ? 0 : i), OK);
	}
}

void			sorted_check_pop(t_sorted *a, t_reverse r, bool reversed)
{
	char		buffer[BUFFER_SIZE];
	t_uint		i = 0;

	for (;i < SORTED_TESTS; i++)
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
	t_uint		i = 0;

	for (; i < SORTED_TESTS; i++)
	{
		o(buffer1, i, SORTED_TESTS);

		res = sorted_search(a, buffer1);
		CHECK_EQ(res.found, true);
		index = res.index;
		CHECK_EQ(strncmp((char*)sorted_get(a, index), buffer1, BUFFER_SIZE), 0);
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
	sorted_fill_hint(&a, o);
	sorted_free(&a);
	sorted_fill_hint(&a, o);
	sorted_free(&a);
	sorted_fill_hint(&a, o);
	sorted_free(&a);
	sorted_fill_hint(&a, o);
	sorted_free(&a);
	sorted_fill_hint(&a, o);
	sorted_free(&a);
	sorted_fill_hint(&a, o);
	sorted_free(&a);
	sorted_fill_hint(&a, o);
	sorted_free(&a);
	sorted_fill_hint(&a, o);
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
	int			i = 0;

	CHECK_EQ(pma_len(a), PMA_TESTS);
	for (i = 0; i < PMA_TESTS; i++)
	{
		o(key_search_buf, i, PMA_TESTS);
		//val_inserted = reversed ? PMA_TESTS_INC - i : i;
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
	CHECK_EQ(pma_len(a), 0);
}

void			pma_check_get(t_pma *a, t_order o, t_reverse r)
{
	char		key_search_buf[BUFFER_SIZE];
	char		key_found_buf[BUFFER_SIZE];
	int			val_found;
	int			i = 0;

	CHECK_EQ(pma_len(a), PMA_TESTS);
	for (i = 0; i < PMA_TESTS; i++)
	{
		o(key_search_buf, i, PMA_TESTS);
		//val_inserted = reversed ? PMA_TESTS_INC - i : i;
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
	int			i = 0;

	for (i = 0; i < PMA_TESTS_INC; i++)
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
	pma_check_delete(&a, o, rev);
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

void			pmait_check_search(t_pma *a, t_order o, t_reverse r)
{
	char		key_search_buf[BUFFER_SIZE];
	char		key_found_buf[BUFFER_SIZE];
	int			val_found;
	int			i = 0;
	t_pmaen		entry;

	CHECK_EQ(pma_len(a), PMA_TESTS);
	for (i = 0; i < PMA_TESTS; i++)
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
	int			i = 0;

	o = asc;
	a = pma(&lt, sizeof(int), sizeof(int));
	pma_fill(&a, o);
	first = 0;

	t_pmaen en = pma_search(&a, &first);
	CHECK_EQ(en.found, true);
	if (en.found)
		pmait_cmp(pmait(&a), en.it);
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
	int			i = 0;

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
		pmait_cmp(pma_range(&a, &mid, NULL), en.it);
		pmait_cmp_back(pma_range(&a, &mid, NULL), en.it);
		pmait_cmp(pma_range(&a, &mid, &last), en.it);
		pmait_cmp_back(pma_range(&a, &mid, &last), en.it);
	}

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

	for (i = 0; i < PMA_TESTS; i += 2)
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

void			test_pmait_manual(t_pmait it)
{
	bool		to_update;
	int			out_key;
	char		out_val;

	to_update = true;
	while (1)
	{
		if (to_update)
		{
			putchar('\n');
			pmait_display(&it, (t_printer)print_int, (t_printer)print_char);
		}
		to_update = true;

		switch (getchar())
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
#ifdef TEST_PMA_BONUS_IT_BACK
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
#endif // TEST_PMA_BONUS_IT_BACK
			case 'q': return ;
			default : to_update = false;
		}
	}
}

void			test_pma_manual(void)
{
	t_pma		a;
	int			n;
	int			m;
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
		{
			putchar('\n');
			pma_display(&a, (t_printer)print_int, (t_printer)print_char);
		}
		to_update = true;
		switch (getchar())
		{
			case 'q': return ;
			case 'f': pma_free(&a); break ;
			case 's':
				scanf ("%d",&n);
				printf("a[%lu] == %i\n", pma_search(&a, &n).it.id, n);
				to_update = false;
				break ;
			case 'd': scanf ("%d",&n); pma_delete(&a, &n, &out_key, &out_val); break ;
			case 'i': scanf ("%d",&n); s = rand() / ((1 << 5) - 1); pma_insert(&a, &n, &s); break ;
			case 'j': scanf ("%d %c",&n,&s); pma_insert(&a, &n, &s); break ;

			case 'r': 
				n = rand() / ((1 << 20) - 1);
				s = rand() % 26;
				pma_insert(&a, &n, &s);
				break ;
			case 'm':
				for (int i = 0; i < 1000000; i++)
				{	
					n = rand() / ((1 << 5) - 1);
					s = rand() % 26;
					if (rand() % 13 == 0)
						pma_delete(&a, &n, &n, &s);
					else
						pma_insert(&a, &n, &s);

				}
				break ;
#ifdef TEST_PMA_BONUS_IT
			case '^': scanf ("%d",&n); test_pmait_manual(pma_search(&a, &n).it); break ;
			case '>': test_pmait_manual(pmait(&a)); break ;
#ifdef TEST_PMA_BONUS_IT_BACK
			case 'x': scanf ("%d %d",&n,&m); test_pmait_manual(pma_range(&a, &n, &m)); break ;
#endif // TEST_PMA_BONUS_IT_BACK
#endif // TEST_PMA_BONUS_IT
			default : to_update = false;

			// pma_get
			// pma_ensure(t_pmaen *en, const void *data);
			// pma_range(const t_pma *a, void *key_a, void *key_b); break ;
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

void		check(char *name, void (*fn)(), bool all)
{
	clock_t	begin;
	clock_t	end;

	if (all || check_test(name))
	{
		begin = clock();

		fn();

		end = clock();
		printf("%s: %fs\n", name, (double)(end - begin) / CLOCKS_PER_SEC);
	}
}

int			main(void)
{
	bool	all;

	all = true;//heck_test("all");

#ifdef TEST_ARRAY
	check("array", &test_array, all);
# ifdef TEST_ARRAY_BONUS
	check("array bonus", &test_array_bonus, all);
# endif // TEST_ARRAY_BONUS
#endif // TEST_ARRAY

#ifdef TEST_BITSET
	check("bitset", &test_bitset, all);
# ifdef TEST_BITSET_BONUS
	check("bitset bonus", &test_bitset_bonus, all);
# endif // TEST_BITSET_BONUS
#endif // TEST_BITSET

#ifdef TEST_QUEUE
	check("queue", &test_queue, all);
#endif

#ifdef TEST_SORTED
 	check("sorted", &test_sorted, all);
# ifdef TEST_SORTED_BONUS
 	check("sorted bonus", &test_sorted_bonus, all);
# endif // TEST_SORTED_BONUS
#endif // TEST_SORTED

#ifdef TEST_PMA
	check("pma", &test_pma, all);
# ifdef TEST_PMA_BONUS_IT
	check("pmait", &test_pmait, all);
#  ifdef TEST_PMA_BONUS_IT_BACK
	check("pmait_back", &test_pmait_back, all);
#  endif // TEST_PMA_BONUS_IT
# endif // TEST_PMA_BONUS_IT
	check("pma manipulator", &test_pma_manual, all);
#endif // TEST_PMA

	printf("All checks done, press enter after checking for leaks\n");
	getchar();
	getchar();
	return (0);
}
