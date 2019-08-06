/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: maboye <maboye@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/08/06 14:09:51 by maboye            #+#    #+#             */
/*   Updated: 2019/08/06 17:15:26 by maboye           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FT_PRINTF_H
# define FT_PRINTF_H

// https://cdn.intra.42.fr/pdf/pdf/20/ft_printf.fr.pdf
// https://github.com/pbondoer/42-ft_printf
// https://www.ljll.math.upmc.fr/courscpp/Sections/Sect06-G1.html
// https://www.ibisc.univ-evry.fr/~petit/Enseignement/Modelisation-en-C/printf-conversions-format.pdf
// https://www.commentcamarche.net/contents/121-langage-c-les-types-de-donnees
// http://www.open-std.org/jtc1/sc22/wg14/www/docs/n1570.pdf

# include <stdarg.h>
# include <stdio.h>
# include <stdlib.h>
# include <string.h>
# include <unistd.h>

typedef struct	s_string
{
	const char	*str;
	size_t		length;
}				t_string;

typedef struct	s_args
{
	size_t		pos;
	size_t		length;
	t_string	str;
}				t_args;

typedef struct	s_printf
{
	int			access;
	int			flags;
	int			width;
	int			w_access;
	int			precision;
	int			error;
	char		conversion;
	void		*value;
	t_string	str;
}				t_printf;

int				ft_printf(const char *format, ...);

int				pf_atoi(const char *str);
int				pf_get_base(char c);
char			*pf_itoa(int n);
size_t			pf_strlen(const char *s, size_t max);

int				pf_is_conversion(const char c);
int				pf_is_modifier(const char c);
int				pf_is_flag(const char c);
int				pf_is_precision(const char c);
int				pf_is_valid(const char c);

int				pf_isspace(int c);
int				pf_isdigit(int c);
int				pf_max(int a, int b);
void			*pf_memalloc(size_t size);
char			*pf_strchr(const char *s, int c);

int				pf_write(const char *str, size_t len);
int				pf_repeat(const char c, size_t len);

#endif
