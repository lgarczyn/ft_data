/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   types.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lgarczyn <lgarczyn@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2014/11/07 16:18:53 by lgarczyn          #+#    #+#             */
/*   Updated: 2018/03/28 23:47:55 by lgarczyn         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef _TYPES_H
# define _TYPES_H

# include <stdint.h>
# include <stdbool.h>
# include <stddef.h>

# define U8 typedef uint8_t u8;
# define U16 typedef uint16_t u16;
# define U32 typedef uint32_t u32;
# define U64 typedef uint64_t u64;
# define USIZE typedef size_t usize;
# define I8 typedef int8_t i8;
# define I16 typedef int16_t i16;
# define I32 typedef int32_t i32;
# define I64 typedef int64_t i64;
# define ISIZE typedef ptrdiff_t isize;
# define UINT typedef unsigned int uint;
# define UCHAR typedef unsigned char uchar;
# define ILLEGAL {}; U8 U16 U32 U64 USIZE I8 I16 I32 I64 ISIZE UINT UCHAR

static const int g_a[0] = ILLEGAL;

typedef unsigned int	t_uint;
typedef unsigned char	t_uchar;

#endif
