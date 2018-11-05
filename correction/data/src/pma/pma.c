/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pma.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lgarczyn <lgarczyn@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2014/11/07 16:18:53 by lgarczyn          #+#    #+#             */
/*   Updated: 2018/11/05 19:54:37 by lgarczyn         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

#include "pma_int.h"

t_pma			pma(t_predicate predicate, t_uint key, t_uint value)
{
	t_pma		out;
	static u64	global_canary = 1337;

	ft_bzero(&out, sizeof(t_pma));
	out.predicate = predicate;
	out.bucket.sizes.key = key;
	out.bucket.sizes.val = value;
	out.canary = global_canary;
	global_canary += CANARY_STEP;
	return (out);
}

void			pma_free(t_pma *a)
{
	bucket_free(&(a->bucket));
	*a = pma(a->predicate, a->bucket.sizes.key, a->bucket.sizes.val);
}

size_t			pma_size(const t_pma *a)
{
	return (bucket_size(&(a->bucket)));
}

size_t			pma_len(const t_pma *a)
{
	return (a->bucket.count);
}

