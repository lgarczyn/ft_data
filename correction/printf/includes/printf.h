/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   printf.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lgarczyn <lgarczyn@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/08/08 16:31:19 by lgarczyn          #+#    #+#             */
/*   Updated: 2018/03/23 20:42:00 by lgarczyn         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PRINTF_H
# define PRINTF_H

int						print(const char *format, ...);
int						printerr(const char *format, ...);
int						printind(const char *format, ...);
int						printfd(int fd, const char *format, ...);

#endif
