/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: maboye <maboye@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/08/06 18:33:31 by maboye            #+#    #+#             */
/*   Updated: 2019/08/06 19:10:28 by maboye           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/ft_printf.h"

static void		pf_parsing(const char *format, va_list list, int *i, int *res)
{
    (void)format;
	(void)list;
    (void)i;
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
            ++result;
			if (!format[i])
				break ;
			else
				pf_parsing(format, list, &i, &result);
		}
		else
        {
			write(1, &format[i++], 1);
		    ++result;
        }
	}
	return (result);
}
