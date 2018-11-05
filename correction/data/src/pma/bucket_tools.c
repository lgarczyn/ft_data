/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   bucket_tools.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lgarczyn <lgarczyn@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2014/11/07 16:18:53 by lgarczyn          #+#    #+#             */
/*   Updated: 2018/11/05 19:54:40 by lgarczyn         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

#include "pma_int.h"

void			bucket_free(t_bucket *b)
{
	t_sizes		sizes;

	bitmap_free(&(b->flags));
	array_free(&(b->values));
	sizes = b->sizes;
	ft_bzero(b, sizeof(t_bucket));
	b->sizes = sizes;
}

void			*bucket_at(t_bucket *b, size_t index)
{
	return (b->values.data + (index * (b->sizes.key + b->sizes.val)));
}

const void		*bucket_cat(const t_bucket *b, size_t index)
{
	return (b->values.data + (index * (b->sizes.key + b->sizes.val)));
}

size_t			bucket_word(const t_bucket *b)
{
	return (b->sizes.key + b->sizes.val);
}

size_t			bucket_size(const t_bucket *b)
{
	return (bitmap_len(&(b->flags)));
}

