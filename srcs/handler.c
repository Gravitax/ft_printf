/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handler.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: maboye <maboye@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/08/06 14:51:38 by maboye            #+#    #+#             */
/*   Updated: 2019/08/22 23:33:58 by maboye           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/ft_printf.h"

void				pf_handle_width(t_printf *data)
{
	char	c;
	int		width;

	c = (data->flags & ZERO ? '0' : ' ');
	width = data->width;
	if (data->p_token)
	{
		while (width-- > data->precision)
			pf_buffer(data, c);
	}
	else
	{
		while (width-- > data->len)
			pf_buffer(data, c);
	}
}

void				pf_handle_precision(t_printf *data)
{
	int		precision;

	if (data->p_token && data->conversion != 's')
	{
		precision = data->precision;
		while (precision-- > data->len)
			pf_buffer(data, '0');
	}
}

void				pf_handle_flag(t_printf *data)
{
	if ((data->flags & SPC) && data->width < 1)
		pf_buffer(data, ' ');
	if (data->flags & HASH || data->conversion == 'p')
	{
		if (pf_strchr("xXo", data->conversion))
		{
			pf_buffer(data, 'O');
			if (data->conversion != 'o')
				pf_buffer(data, data->conversion == 'x' ? 'x' : 'X');
		}
		else if (data->conversion == 'p')
			pf_bufferstr(data, "0x");
	}
}

void				pf_handler(t_printf *data)
{
	pf_get_type(data);
	if (data->width <= data->len)
		data->width = 0;
	if ((data->precision <= data->len) && data->conversion != 's')
		data->precision = data->len;
	if (!(data->flags & LESS) && data->width > data->len)
		pf_handle_width(data);
	pf_handle_precision(data);
	pf_handle_flag(data);
	pf_bufferstr(data, data->str);
	if (data->flags & LESS)
		pf_handle_width(data);
}
