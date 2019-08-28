/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: maboye <maboye@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/08/06 18:33:31 by maboye            #+#    #+#             */
/*   Updated: 2019/08/28 14:17:33 by maboye           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/ft_printf.h"

static void		pf_parse_wp(const char *format, t_printf *data, int *i)
{
	long	tmp;

	tmp = 0;
	while (pf_isdigit(format[*i]) && tmp <= 2147483647)
	{
		tmp = (10 * tmp) + (format[*i] - '0');
		(*i)++;
	}
	if (tmp > 2147483647)
		tmp = 2147283647;
	data->width = tmp;
	if (format[*i] == '.')
	{
		(*i)++;
		tmp = 0;
		while (pf_isdigit(format[*i]) && tmp <= 2147483647)
		{
			tmp = (10 * tmp) + (format[*i] - '0');
			(*i)++;
		}
		if (tmp > 2147483647)
			tmp = 2147283647;
		data->precision = tmp;
		data->p_token = 1;
	}
}

static void		pf_parse_size(const char *format, t_printf *data, int *i)
{
	data->i_conv = 0;
	if (format[*i] == 'l')
		data->i_conv = L;
	else if (format[*i] == 'h')
		data->i_conv = H;
	else if (format[*i] == 'j')
		data->i_conv = J;
	else if (format[*i] == 'z')
		data->i_conv = Z;
	else if (format[*i] == 'L')
		data->i_conv = LF;
	if (data->i_conv)
		++(*i);
	if ((format[*i] == 'l' || format[*i] == 'h') && (data->i_conv != LF))
	{
		data->i_conv = (format[*i] == 'l') ? LL : HH;
		(*i)++;
	}
}

static void		pf_parse_conversion(const char *format, t_printf *data, int *i)
{
	data->conversion = 0;
	if (pf_strchr("diouxX", format[*i]) && data->i_conv != LF)
		data->conversion = format[(*i)++];
	else if (format[*i] == 'c' || format[*i] == 'p' || format[*i] == 's')
		data->conversion = format[(*i)++];
	else if (data->i_conv < 6 && format[*i] == 'f')
		data->conversion = format[(*i)++];
	if (data->flags & HASH && pf_strchr("cdius", data->conversion))
		data->flags -= HASH;
	if (data->flags & ZERO && data->flags & LESS)
		data->flags -= ZERO;
	if (data->p_token && data->flags & ZERO
	&& pf_strchr("diouxX", data->conversion))
		data->flags -= ZERO;
	if (pf_strchr("cpouxX", data->conversion))
	{
		if (data->flags & MORE)
			data->flags -= MORE;
		if (data->flags & SPC)
			if (data->conversion != 'p')
				data->flags -= SPC;
	}
}

static void		pf_parsing(const char *format, t_printf *data, int *i)
{
	data->flags = 0;
	data->neg = 0;
	data->p_token = 0;
	data->precision = -1;
	data->str = NULL;
	while (pf_strchr("#0-+ ", format[*i]) != NULL)
	{
		if (format[*i] == '#' && !(data->flags & HASH))
			data->flags += HASH;
		else if (format[*i] == '0' && !(data->flags & ZERO))
			data->flags += ZERO;
		else if (format[*i] == '-' && !(data->flags & LESS))
			data->flags += LESS;
		else if (format[*i] == '+' && !(data->flags & MORE))
			data->flags += MORE;
		else if (format[*i] == ' ' && !(data->flags & SPC))
			data->flags += SPC;
		(*i)++;
	}
	pf_parse_wp(format, data, i);
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
