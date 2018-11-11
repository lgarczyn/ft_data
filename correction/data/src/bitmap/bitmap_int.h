/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   bitmap_int.h                                       :+:      :+:    :+:   */
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
** bitmap.c
*/
t_bitmap	bitmap(void);
void		bitmap_free(t_bitmap *a);
int			bitmap_set_len(t_bitmap *a, size_t new_size);
int			bitmap_reserve(t_bitmap *a, size_t new_size);
size_t		bitmap_len(const t_bitmap *a);
/*
** bitmap_accessors.c
*/
bool		bitmap_get(const t_bitmap *a, size_t i);
int			bitmap_get_safe(const t_bitmap *a, size_t i, bool *out);
void		bitmap_set(t_bitmap *a, size_t p, bool b);
int			bitmap_set_safe(t_bitmap *a, size_t i, bool b);
/*
** bitmap_stack.c
*/
int		bitmap_push(t_bitmap *a, bool b);
int		bitmap_pop(t_bitmap *a, bool *data);
#endif
