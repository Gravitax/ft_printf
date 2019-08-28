/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: maboye <maboye@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/08/06 14:09:51 by maboye            #+#    #+#             */
/*   Updated: 2019/08/27 15:05:44 by maboye           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FT_PRINTF_H
# define FT_PRINTF_H

/*
** https://cdn.intra.42.fr/pdf/pdf/20/ft_printf.fr.pdf
*/

# include <limits.h>
# include <stdarg.h>
# include <stdio.h>
# include <stdlib.h>
# include <string.h>
# include <unistd.h>

# define NONE	0
# define HASH	1
# define ZERO	2
# define LESS	4
# define MORE	8
# define SPC	16

# define B_SIZE	4096

/*
** # define 	intmax_t	intptr_t
** # define 	uintmax_t	intptr_t
*/

typedef struct	s_printf
{
	int			count;
	int			flags;
	int			i;
	int			i_conv;
	int			len;
	int			neg;
	int			p_token;
	int			precision;
	int			width;
	char		buf[B_SIZE];
	char		conversion;
	char		*str;
	va_list		list;
}				t_printf;

typedef enum	e_flags
{
	L = 1,
	LL,
	H,
	HH,
	LF,
	J,
	Z
}				t_flags;

int				ft_printf(const char *format, ...);

void			pf_handler(t_printf *data);
void			pf_get_type(t_printf *data);
void			pf_handle_float(t_printf *data);

void			pf_parser(const char *format, t_printf *data);

char			*ft_itoa_base(t_printf *data, intmax_t nb, int base);
char			*ft_uitoa_base(t_printf *data, uintmax_t nb, int base);

intmax_t		pf_abs(intmax_t nb);
int				pf_isdigit(int c);
int				pf_isspace(int c);
char			*pf_strdup(const char *src);
void			pf_strtolower(char *str);

void			*pf_memalloc(size_t size);
void			*pf_memset(void *ptr, int c, size_t len);
char			*pf_strchr(const char *ptr, int c);
size_t			pf_strlen(const char *str);

void			pf_buffer(t_printf *data, char c);
void			pf_bufferstr(t_printf *data, char *str);
void			pf_print_buffer(t_printf *data, int len);

#endif
