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