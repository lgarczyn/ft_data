/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   libft.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lgarczyn <lgarczyn@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2014/11/07 16:18:53 by lgarczyn          #+#    #+#             */
/*   Updated: 2018/03/28 23:47:55 by lgarczyn         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef _LIBFT_H
# define _LIBFT_H

# include <string.h>
# include <errno.h>
# include <stdlib.h>
# include <sys/types.h>

# include "types.h"

# define MIN(a,b)			(((a)<(b))?(a):(b))
# define MAX(a,b)			(((a)>(b))?(a):(b))
# define CLAMP(x,lo,hi)		MIN(hi, MAX(lo,x))
# define DIV_RDUP(x, y)		(((x) % (y)) ? (x) / (y) + 1 : (x) / (y))
# define ROUND_UP(a, b)		(DIV_RDUP(a, b) * (b))
# define STDIN				0
# define STDOUT				1
# define STDERR				2

# define OK					(0)
# define ERR_ALLOC			(-1)
# define ERR_SIZE			(-2)
# define ERR_MISSING		(-3)

# define REALLOC_GROWTH_FACTOR 2

char			*ft_strerror(int err);
void			ft_perror(const char *str);
void			ft_perror_file(const char *str, const char *file);
void			ft_perror_buf(const char *str);
void			ft_perror_file_buf(const char *str, const char *file);

t_buffer		*ft_buf(char *buffer, size_t size, int fd);
t_buffer		*ft_get_buf(void);
int				ft_flush_buf(void);
int				ft_flush_total(void);
void			ft_flush_overflow(void);
void			ft_putchar_buf(char c);
void			ft_putnchar_buf(char c, int n);
void			ft_putwchar_buf(wchar_t wc);
void			ft_putendl_buf(const char *str);
void			ft_putnendl_buf(const char *str, size_t n);
void			ft_putnbr_buf(int n);
void			ft_putspace_buf(size_t len);
void			ft_putnstr_buf(const char *str, size_t len);
void			ft_putmstr_buf(const char *str, size_t len);
void			ft_putstr_buf(const char *str);
void			ft_putnwstr_buf(wchar_t *str, size_t len);
void			ft_putwstr_buf(wchar_t *str);
void			ft_putrnstr_buf(const char *str, size_t len);
void			ft_putrstr_buf(const char *str);
void			ft_reset_buf(int fd);
void			ft_setfd_buf(int fd);

char			**ft_strsplit(char const *s, char c);
char			*ft_itoa(int n);
char			*ft_strcat(char *s1, const char *s2);
char			*ft_strchr(const char *s, int c);
char			*ft_strcpy(char *dst, const char *src);
char			*ft_strdup(const char *s1);
char			*ft_strndup(const char *s1, int len);
char			*ft_strndupwhile(const char *m, size_t n, int (*p)(int c));
char			*ft_strdupwhile(const char *m, int (*pred)(int c));
char			*ft_strjoin(char const *s1, char const *s2);
char			*ft_strmap(char const *s, char (*f)(char));
char			*ft_strmapi(char const *s, char (*f)(unsigned int, char));
char			*ft_strncat(char *s1, const char *s2, size_t n);
char			*ft_strncpy(char *dst, const char *src, size_t n);
char			*ft_strnew(size_t size);
char			*ft_strnstr(const char *s1, const char *s2, size_t n);
char			*ft_strrchr(const char *s, int c);
char			*ft_strstr(const char *s1, const char *s2);
char			*ft_strsub(char const *s, unsigned int start, size_t len);
char			*ft_strtrim(char const *s);
int				ft_atoi(const char *str);
unsigned int	ft_pure_atoi(const char *str);
int				ft_intlen(int num);
int				ft_unumlen(ssize_t i);
int				ft_numlen(size_t i);
int				ft_isalnum(int c);
int				ft_isalpha(int c);
int				ft_isascii(int c);
int				ft_isdigit(int c);
int				ft_isempty(int c);
int				ft_isprint(int c);
int				ft_isspace(int c);
int				ft_memcmp(const void *s1, const void *s2, size_t n);
int				ft_strcmp(const char *s1, const char *s2);
int				ft_strcmp_fast(const char *s1, const char *s2, int len);
int				ft_strequ(char const *s1, char const *s2);
int				ft_strncmp(const char *s1, const char *s2, size_t n);
int				ft_strnequ(char const *s1, char const *s2, size_t n);
int				ft_tolower(int c);
int				ft_toupper(int c);
size_t			ft_strlcat(char *dst, const char *src, size_t size);
size_t			ft_strlen(const char *s);
size_t			ft_wstrlen(const wchar_t *s);
size_t			ft_strlen_fast(const char *s);
t_list			*ft_lstmap(t_list *lst, t_list *(*f)(t_list *elem));
t_list			*ft_lstnew(void const *content, size_t content_size);
void			*ft_memalloc(size_t size);
void			*ft_memccpy(void *dst, const void *src, int c, size_t n);
void			*ft_memchr(const void *s, int c, size_t n);
void			*ft_memcpy(void *dst, const void *src, size_t n);
void			*ft_memmove(void *dst, const void *src, size_t n);
void			*ft_memswap(void *dst, void *src, size_t len);
void			*ft_memset(void *b, int c, size_t len);
void			ft_bzero(void *s, size_t n);
void			ft_lstadd(t_list **alst, t_list *n);
void			ft_lstdel(t_list **alst, void (*del)(void *, size_t));
void			ft_lstdelone(t_list **alst, void (*del)(void *, size_t));
void			ft_lstiter(t_list *lst, void (*f)(t_list *elem));
void			ft_memdel(void **ap);
void			ft_putchar(char c);
void			ft_putchar_fd(char c, int fd);
void			ft_putendl(char const *s);
void			ft_putendl_fd(char const *s, int fd);
void			ft_putnbr(int n);
void			ft_putnbr_fd(int n, int fd);
void			ft_putnbr_64(size_t n);
void			ft_putnstr(char const *s, int n);
void			ft_putnstr_fd(char const *s, int fd, int n);
void			ft_putspace(int n);
void			ft_putstr(char const *s);
void			ft_putstr_fd(char const *s, int fd);
void			ft_strclr(char *s);
void			ft_strdel(char **as);
void			ft_striter(char *s, void (*f)(char *));
void			ft_striteri(char *s, void (*f)(unsigned int, char *));

void			check_min_alloc();
size_t			ft_min_alloc(size_t size);
int				ft_realloc(void **p, size_t len, size_t nlen, size_t *size);
int				ft_realloc_down(void **p, size_t len, size_t *size);


void			xfree(void *ptr);
void			*xmalloc(size_t size);

#endif
