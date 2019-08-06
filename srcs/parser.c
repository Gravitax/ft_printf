/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: maboye <maboye@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/08/06 18:33:31 by maboye            #+#    #+#             */
/*   Updated: 2019/08/06 19:05:34 by maboye           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/ft_printf.h"

static void		pf_parsing(const char *format, va_list list, int *i, int *res)
{
	while (format[*i] && !pf_isspace(format[*i]))
		++(*i);
	(void)list;
	(void)res;
}

int				pf_parser(const char *format, va_list list)
{
	int	result;
	int	i;

	result = 0;
	i = 0;
	while (format && format[i])
	{
		if (format[i] == '%')
		{
			++i;
			if (!format[i])
				return (++result);
			else
				pf_parsing(format, list, &i, &result);
		}
		else
			write(1, &format[i++], 1);
		++result;
	}
	return (result);
}
