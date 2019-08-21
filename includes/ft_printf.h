/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: maboye <maboye@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/08/06 14:09:51 by maboye            #+#    #+#             */
/*   Updated: 2019/08/21 15:55:49 by maboye           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FT_PRINTF_H
# define FT_PRINTF_H

// https://cdn.intra.42.fr/pdf/pdf/20/ft_printf.fr.pdf
// https://github.com/mpaland/printf/blob/master/printf.c
// https://github.com/pbondoer/42-ft_printf
// https://www.ljll.math.upmc.fr/courscpp/Sections/Sect06-G1.html
// https://www.ibisc.univ-evry.fr/~petit/Enseignement/Modelisation-en-C/printf-conversions-format.pdf
// https://www.commentcamarche.net/contents/121-langage-c-les-types-de-donnees
// http://www.open-std.org/jtc1/sc22/wg14/www/docs/n1570.pdf

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
# define ASTE	32 // asterisk
# define DOLL	64
# define APOST	128 // apostrophe

# define B_SIZE	4096

typedef struct	s_printf
{
	int			count;
	int			flags;
	size_t		width;
	int			precision;
	int			i_conv;
	char		conversion;
	va_list		list;
	char		buf[B_SIZE];
	int			i;
	char		*str;
	int			len;
	void		*value;
}				t_printf;

typedef enum	e_flags
{
	NO,
	L,
	LL,
	H,
	HH,
	LF
}				t_flags;

int				ft_printf(const char *format, ...);

void            pf_handler(t_printf *data);
void            pf_get_type(t_printf *data);

void			pf_parser(const char *format, t_printf *data);
void			pf_validate_flags(t_printf *data, int *res);
void			pf_parse_flag(const char *format, t_printf *data, int *i);
void			pf_parse_width(const char *format, t_printf *data, int *i);
void			pf_parse_precision(const char *format, t_printf *data, int *i);
void			pf_parse_size(const char *format, t_printf *data, int *i);
void			pf_parse_conversion(const char *format, t_printf *data, int *i);

char			*ft_itoa_base(intmax_t nb, int base);
char			*ft_uitoa_base(uintmax_t nb, int base);

int				pf_is_conversion(const char c);
int				pf_is_modifier(const char c);
int				pf_is_flag(const char c);
int				pf_is_precision(const char c);
int				pf_is_valid(const char c);

intmax_t		pf_abs(intmax_t nb);
int				pf_get_base(char c);
int				pf_isdigit(int c);
int				pf_isspace(int c);
int				pf_max(int a, int b);

int				pf_atoi(const char *str, int x);
intmax_t		pf_intlen(intmax_t nb);
void			*pf_memalloc(size_t size);
char			*pf_strchr(const char *s, int c);
// char			*pf_strdup(const char *src);
size_t			pf_strlen(const char *s, size_t max);

void			pf_buffer(t_printf *data, char c);
void	        pf_bufferstr(t_printf *data, char *str);
void			pf_print_buffer(t_printf *data, int len);

#endif
