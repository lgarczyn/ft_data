/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   btree.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lgarczyn <lgarczyn@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/09/13 22:02:52 by lgarczyn          #+#    #+#             */
/*   Updated: 2018/09/14 01:10:53 by lgarczyn         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include "data.h"

t_btree				btree(t_predicate predicate, t_uint word)
{
	t_btree			out;

	ft_bzero(&out, sizeof(out));
	out.word = word;
	out.predicate = predicate;
	return (out);
}

static				branch_free(t_btree *a, t_branch *branch)
{
	
}

void				btree_free(t_btree *a);
t_btree_it			btree_search(const t_btree *a, const void *d);
int					btree_insert(t_btree *a, const void *data);
t_searchres			btree_replace(t_btree *a, void *data);
t_searchres			btree_delete(t_btree *a, const void *data, void *out);
int					btree_pop(t_btree *a, void *data);
size_t				btree_len(const t_btree *a);

bool				btree_get(t_btree_it *i, void *data);
bool				btree_next(t_btree_it *i, void *data);
int					btree_insert_it(t_btree_it *i, const void *date);
t_searchres			btree_replace_it(t_btree_it *i, void *data);
void				btree_delete_it(t_btree_it *i, void *out);

t_btree		btree(t_predicate predicate, t_uint word)
{
	t_btree out;

	ft_bzer (&out, sizeof(out));
	out.predicate = predicate;
	out.word  = MAX(word, 1);
	return (out);
}

static void branch_free(t_branch b)
{
    size_t      i;

    if (b.children)
    {
        i = 0;
        while (i < b.count)
        {
            branch_free(b.children[i]);
            i++;
        }
        free(b.children);
    }
    free (b.data);
}

void			btree_free(t_btree *a)
{
	free_branch(a->data);
	*a = btree(a->predicate, a->word);
}

t_searchres		btree_search_range(const t_btree *a, const t_branch *b, const void *ptr)
{
	t_searchres	res;
    t_uint      start;
    t_uint      end;

    start = 0;
    end = b->count;
	res.index = start + (end - start) / 2;
	res.found = 0;
	while (start < end)
	{
		if (res.index == start)
		{
			if (a->predicate(ptr, btree_cget(a, res.index)) == 0)
			{
				if (a->predicate(btree_cget(a, res.index), ptr) == 0)
					res.found = 1;
				else
					res.index++;
			}
            break ;
		}
		else if (a->predicate(ptr, btree_cget(a, res.index)))
			end = res.index;
		else
			start = res.index;
	}
	return (res);
}

t_searchres		btree_search(const t_btree *a, const void *ptr)
{
	return (btree_search_range(a, ptr, 0, btree_len(a)));
}

static int		btree_insert_index(t_btree *a, const void *data, size_t i)
{
	size_t		new_pos;
	size_t		prev_len;
	size_t		next_len;

	new_pos = a->pos + a->word;
	if (new_pos > a->size)
	{
		if (ft_realloc(&a->data, a->size, new_pos * 2))
			return (ERR_ALLOC);
		a->size = new_pos * 2;
	}
	prev_len = i * a->word;
	next_len = a->pos - prev_len;
	if (a->pos - prev_len)
		ft_memmove(btree_get(a, i + 1), btree_cget(a, i), next_len);
	ft_memcpy(btree_get(a, i), data, a->word);
	a->pos = new_pos;
	return (OK);
}

int				btree_insert_hint(t_btree *a, const void *data, size_t hint)
{
	size_t		index_prev;
	size_t		index_self;

	index_prev = (hint - 1) * a->word;
	index_self = hint * a->word;
	if (hint == 0 || a->predicate(a->data + index_prev, data))
		if (hint >= btree_len(a) || a->predicate(data, a->data + index_self))
			return (btree_insert_index(a, data, hint));
	return (btree_insert(a, data));
}

int				btree_insert(t_btree *a, const void *data)
{
	t_searchres	res;

	res = btree_search(a, data);
	if (res.found)
		ft_memcpy(a->data + res.index * a->word, data, a->word);
	else
	{
		return (btree_insert_index(a, data, res.index));
	}
	return (OK);
}

static void		shrink_to_fit(t_btree *a)
{
	if (ft_realloc(&a->data, a->size, a->pos) == OK)
	{
		a->size = a->pos;
	}
}

void			btree_delete_index(t_btree *a, size_t index, void *out)
{
	size_t		new_pos;
	size_t		prev_len;
	size_t		next_len;
	void		*array_data;

	new_pos = a->pos - a->word;
	prev_len = index * a->word;
	next_len = new_pos - prev_len;
	array_data = a->data + prev_len;
	if (out)
		ft_memcpy(out, array_data, a->word);
	if (next_len)
		ft_memmove(array_data, array_data + a->word, next_len);
	if (a->pos <= a->size / 4)
		shrink_to_fit(a);
	a->pos = new_pos;
}


t_searchres		btree_delete(t_btree *a, const void *data, void *out)
{
	t_searchres	res;

	res = btree_search(a, data);
	if (res.found)
	{
		btree_delete_index(a, res.index, out);
	}
	return (res);
}


t_searchres		btree_replace(t_btree *a, void *data)
{
	t_searchres	res;

	res = btree_search(a, data);
	if (res.found)
	{
		ft_memswap(btree_get(a, res.index), data, a->word);
	}
	else 
	{
		btree_insert_index(a, data, res.index);
	}
	return (res);
}

t_searchres		btree_replace_hint(t_btree *a, void *data, size_t hint)
{
	if (hint == 0 || a->predicate(btree_get(a, hint - 1), data))
		if (hint >= btree_len(a) || a->predicate(data, btree_get(a, hint)))
		{
			ft_memswap(btree_get(a, hint), data, a->word);
		}
	return (btree_replace(a, data));
}

int				btree_pop(t_btree *a, void *data)
{
	if (btree_len(a) <= 0)
		return (ERR_ARG);
	btree_delete_index(a, btree_len(a) - 1, data);
	return (OK);
}

int				btree_reserve(t_btree *a, size_t s)
{
	s *= a->word;
	if (s > a->size)
	{
		if (ft_realloc(&a->data, a->size, s))
			return (ERR_ALLOC);
	}
	return (OK);
}

size_t			btree_len(const t_btree *a)
{
	return (a->pos / a->word);
}
