/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sorted_int.h                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lgarczyn <lgarczyn@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/09/13 22:02:52 by lgarczyn          #+#    #+#             */
/*   Updated: 2018/11/05 19:54:33 by lgarczyn         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */


#ifndef _SORTED_INT_H
# define _SORTED_INT_H

# include "libft.h"
# include "data.h"

/*
** sorted.c
*/
t_sorted	sorted(t_predicate predicate, size_t word);
void		sorted_free(t_sorted *a);
size_t		sorted_len(const t_sorted *a);
int			sorted_reserve(t_sorted *a, size_t s);
/*
** sorted_accessors.c
*/
void		*sorted_get(t_sorted	*a, size_t index);
const	void	*sorted_cget(const t_sorted *a, size_t index);
int			sorted_pop(t_sorted	*a, void *data);
/*
** sorted_search.c
*/
t_searchres		sorted_search_range( const t_sorted *a, const void *ptr, size_t start, size_t end);
t_searchres		sorted_search(const t_sorted *a, const void *ptr);
/*
** sorted_modifiers.c
*/
int				sorted_insert_hint(t_sorted *a, const void *data, size_t hint);
int				sorted_insert(t_sorted *a, const void *data);
void			sorted_delete_index(t_sorted *a, size_t index, void *out);
t_searchres		sorted_delete(t_sorted *a, const void *data, void *out);
/*
** sorted_replace.c
*/
t_searchres		sorted_replace(t_sorted *a, void *data);
t_searchres		sorted_replace_hint(t_sorted *a, void *data, size_t hint);

#endif
