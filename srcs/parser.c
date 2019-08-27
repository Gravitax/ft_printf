/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: maboye <maboye@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/08/06 18:33:31 by maboye            #+#    #+#             */
/*   Updated: 2019/08/27 17:28:25 by maboye           ###   ########.fr       */
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
	if (format[*i] == 'j' || format[*i] == 'z')
	{
		data->i_conv = format[*i] == 'j' ? J : Z;
		(*i)++;
	}
}

static void		pf_validate_flags(t_printf *data)
{
	if ((data->flags & HASH) && pf_strchr("cdius", data->conversion))
		data->flags -= HASH;
	if (data->flags & ZERO && data->flags & LESS)
		data->flags -= ZERO;
	if ((data->flags & SPC)
	&& ((data->flags & MORE) || pf_strchr("couxX", data->conversion)))
		data->flags -= SPC;
	if (data->p_token && (data->flags & ZERO)
			&& pf_strchr("diouxX", data->conversion))
		data->flags -= ZERO;
	if ((data->flags & MORE) && pf_strchr("ouxXpc", data->conversion))
		data->flags -= MORE;
}

static void		pf_parse_conversion(const char *format, t_printf *data, int *i)
{
	if (pf_strchr("diouxX", format[*i]) && data->i_conv != LF)
		data->conversion = format[(*i)++];
	else if ((data->i_conv != LL && data->i_conv != H && data->i_conv != HH)
			&& format[*i] == 'f')
		data->conversion = format[(*i)++];
	else if (format[*i] == 'c' || format[*i] == 'p' || format[*i] == 's')
		data->conversion = format[(*i)++];
	pf_validate_flags(data);
}

static void		pf_parsing(const char *format, t_printf *data, int *i)
{
	data->flags = 0;
	data->i_conv = 0;
	data->len = 0;
	data->neg = 0;
	data->p_token = 0;
	data->precision = -1;
	data->width = 0;
	data->conversion = 0;
	data->str = NULL;
	pf_parse_flag(format, data, i);
	pf_parse_width(format, data, i);
	pf_parse_precision(format, data, i);
	pf_parse_size(format, data, i);
	pf_parse_conversion(format, data, i);
	if ((data->i_conv && data->conversion) || data->conversion)
		pf_handler(data);
}

void			pf_parser(const char *format, t_printf *data)
{
	int	i;

	i = 0;
	while (format && format[i])
	{
		if (format[i] == '%')
		{
			++i;
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
