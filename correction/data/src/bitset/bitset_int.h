/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   bitset_int.h                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lgarczyn <lgarczyn@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/09/13 22:02:52 by lgarczyn          #+#    #+#             */
/*   Updated: 2018/11/05 19:54:45 by lgarczyn         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef _BITMAP_INT_H
# define _BITMAP_INT_H

# include "libft.h"
# include "data.h"

/*
** bitset.c
*/
t_bitset	bitset(void);
void		bitset_free(t_bitset *a);
size_t		bitset_len(const t_bitset *a);
void		bitset_display(const t_bitset *a);
/*
** bitset_alloc.c
*/
int			bitset_set_len(t_bitset *a, size_t new_size);
int			bitset_reserve(t_bitset *a, size_t new_size);
/*
** bitset_accessors.c
*/
bool		bitset_get(const t_bitset *a, size_t i);
int			bitset_get_safe(const t_bitset *a, size_t i, bool *out);
void		bitset_set(t_bitset *a, size_t p, bool b);
int			bitset_set_safe(t_bitset *a, size_t i, bool b);
/*
** bitset_stack.c
*/
int			bitset_push(t_bitset *a, bool b);
int			bitset_pop(t_bitset *a, bool *data);
#endif
