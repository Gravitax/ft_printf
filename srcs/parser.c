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

static void		pf_parsing(const char *format, t_printf *data, int *i, int *res)
{
    (void)format;
	(void)data;
    (void)i;
	(void)res;
	pf_handler(data);
}

int				pf_parser(const char *format, t_printf *data)
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
				pf_parsing(format, data, &i, &result);
		}
		else
        {
			write(1, &format[i++], 1);
		    ++result;
        }
	}
	return (result);
}
