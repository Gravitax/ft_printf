/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: maboye <maboye@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/08/06 18:33:31 by maboye            #+#    #+#             */
/*   Updated: 2019/08/22 23:05:18 by maboye           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/ft_printf.h"

static void		pf_parse_flag(const char *format, t_printf *data, int *i)
{
	while (pf_strchr("'#0-+ ", format[*i]) != NULL)
	{
		if ((format[*i] == '#') && !(data->flags & HASH))
			data->flags += HASH;
		else if ((format[*i] == '0') && !(data->flags & ZERO))
			data->flags += ZERO;
		else if ((format[*i] == '-') && !(data->flags & LESS))
			data->flags += LESS;
		else if ((format[*i] == '+') && !(data->flags & MORE))
			data->flags += MORE;
		else if ((format[*i] == ' ') && !(data->flags & SPC))
			data->flags += SPC;
		else if ((format[*i] == 39) && !(data->flags & APOST))
			data->flags += APOST;
		else
			printf("will add EXIT\n");
		(*i)++;
	}
}

static void		pf_parse_width(const char *format, t_printf *data, int *i)
{
	long long	width;

	width = 0;
	while (pf_isdigit(format[*i]) && width <= 2147483647)
	{
		width = (10 * width) + (format[*i] - '0');
		(*i)++;
	}
	if (width > 2147483647)
		width = 2147283647;
	data->width = width;
}

static void		pf_parse_precision(const char *format, t_printf *data, int *i)
{
	long long	precision;

	if (format[*i] == '.')
	{
		(*i)++;
		precision = 0;
		while (pf_isdigit(format[*i]) && precision <= 2147483647)
		{
			precision = (10 * precision) + (format[*i] - '0');
			(*i)++;
		}
		if (precision > 2147483647)
			precision = 2147283647;
		data->precision = precision;
		data->p_token = 1;
	}
}

static void		pf_parse_size(const char *format, t_printf *data, int *i)
{
	if (format[*i] == 'l' || format[*i] == 'h' || format[*i] == 'L')
	{
		if (format[*i] == 'L')
			data->i_conv = LF;
		else
			data->i_conv = (format[*i] == 'l') ? L : H;
		(*i)++;
	}
	if ((format[*i] == 'l' || format[*i] == 'h') && (data->i_conv != LF))
	{
		data->i_conv = (format[*i] == 'l') ? LL : HH;
		(*i)++;
	}
}

static void		pf_validate_flags(t_printf *data)
{
	if ((data->flags & HASH) && pf_strchr("cdius", data->conversion))
		printf("Invalid according to the last flag check\n");
	if (((data->flags & ZERO) && (data->flags & LESS))
	|| ((data->flags & SPC) && (data->flags & MORE)))
		printf("Invalid according to the last flag check\n");
	if (data->precision >= 0 && (data->flags & ZERO)
	&& pf_strchr("iouxX", data->conversion))
		printf("Invalid according to the last flag check\n");
	if ((data->flags & APOST) && (data->conversion != 'u'
	&& data->conversion != 'd' && data->conversion != 'f'))
		printf("Invalid according to the last flag check\n");
}

static void		pf_parse_conversion(const char *format, t_printf *data, int *i)
{
	if (pf_strchr("diouxX", format[*i]) && data->i_conv != LF)
		data->conversion = format[(*i)++];
	else if ((data->i_conv != LL && data->i_conv != H && data->i_conv != HH)
	&& format[*i] == 'f')
		data->conversion = format[(*i)++];
	else if (format[*i] == 'c' || format[*i] == 's' || format[*i] == 'p')
		data->conversion = format[(*i)++];
	else
		printf("conversion is not valid\n");
	pf_validate_flags(data);
}

static void		pf_parsing(const char *format, t_printf *data, int *i)
{
	data->precision = -1;
	data->p_token = 0;
	pf_parse_flag(format, data, i);
	pf_parse_width(format, data, i);
	pf_parse_precision(format, data, i);
	pf_parse_size(format, data, i);
	pf_parse_conversion(format, data, i);
	pf_handler(data);
}

/*
**	printf("\n------------------------------------\n");
**	printf("flags value is 		 [%d]\n", data->flags);
**	printf("final width is:		 [%d]\n", data->width);
**	printf("final precision is:  [%d]\n", data->precision);
**	printf("final size is:		 [%d]\n", data->i_conv);
**	printf("final conversion is: [%c]\n", data->conversion);
**	printf("------------------------------------\n");
*/

void			pf_parser(const char *format, t_printf *data)
{
	int	i;

	i = 0;
	while (format && format[i])
	{
		if (format[i] == '%')
		{
			++i;
			++data->count;
			if (!format[i])
				break ;
			else if (format[i] == '%')
				pf_buffer(data, format[i++]);
			else
				pf_parsing(format, data, &i);
		}
		else
			pf_buffer(data, format[i++]);
	}
}
