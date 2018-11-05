/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   array_int.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lgarczyn <lgarczyn@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/09/13 22:02:52 by lgarczyn          #+#    #+#             */
/*   Updated: 2018/11/05 19:54:24 by lgarczyn         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef _ARRAY_INT_H
# define _ARRAY_INT_H

# include "libft.h"
# include "data.h"

/*
** array.c
*/
void		check_array(const t_array *a);
t_array		array(void);
void		array_free(t_array *a);
size_t		array_len(const t_array *a, size_t word);
/*
** array_modifiers.c
*/
int		array_move(t_array *a, size_t from, size_t to, size_t size);
int		array_insert(t_array *a, const void *data, size_t i, size_t size);
int		array_remove(t_array *a, void *data, size_t i, size_t size);
int		array_reserve(t_array *a, size_t s);
/*
** array_wrappers.c
*/
int		array_push(t_array *a, const void *data, size_t size);
int		array_pop(t_array *a, void *data, size_t size);
#endif
