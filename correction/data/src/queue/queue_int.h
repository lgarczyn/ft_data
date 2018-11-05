/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   queue_int.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lgarczyn <lgarczyn@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/09/13 22:02:52 by lgarczyn          #+#    #+#             */
/*   Updated: 2018/11/05 19:54:35 by lgarczyn         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef _QUEUE_INT_H
# define _QUEUE_INT_H

# include "libft.h"
# include "data.h"

/*
** queue.c
*/
t_queue		queue(size_t word);
void		queue_free(t_queue *a);
/*
** queue_modifiers.c
*/
int		queue_realloc(t_queue *a, size_t new_size);
int		queue_push_back(t_queue *a, const void *data);
int		queue_push_front(t_queue *a, const void *data);
int		queue_pop_back(t_queue *a, void *data);
int		queue_pop_front(t_queue *a, void *data);

#endif
