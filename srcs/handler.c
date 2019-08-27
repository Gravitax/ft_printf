/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handler.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: maboye <maboye@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/08/06 14:51:38 by maboye            #+#    #+#             */
/*   Updated: 2019/08/27 17:34:54 by maboye           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/ft_printf.h"

static void			pf_handle_width(t_printf *data)
{
	char	c;
	int		width;

	c = (data->flags & ZERO ? '0' : ' ');
	width = data->width;
	while (width-- > data->precision)
		pf_buffer(data, c);
}

static void			pf_handle_precision(t_printf *data)
{
	int		precision;

	if (data->p_token && data->conversion != 's')
	{
		precision = data->precision;
		while (precision-- > data->len)
			pf_buffer(data, '0');
	}
}

static void			pf_handle_flag(t_printf *data)
{
	if (!pf_strchr("pouxX", data->conversion))
	{
		if (data->flags & MORE && !data->neg)
		{
			pf_buffer(data, '+');
			--data->width;
		}
		if (data->neg)
		{
			pf_buffer(data, '-');
			--data->width;
		}
	}
	if (data->flags & HASH || data->conversion == 'p')
	{
		if (data->conversion == 'o')
		{
			if (data->precision <= data->len)
			{
				pf_buffer(data, '0');
				--data->width;
			}
		}
		else if (pf_strchr("pxX", data->conversion))
		{
			pf_buffer(data, '0');
			pf_buffer(data, data->conversion == 'X' ? 'X' : 'x');
			data->width -= 2;
		}
	}
}

static void			pf_refresh_data(t_printf *data)
{
	if (data->precision < 0)
		data->precision = 0;
	if (data->conversion == 's')
	{
		if (data->p_token && data->len >= data->precision)
			data->len = data->precision;
		if (data->precision > data->len)
			data->precision = data->len;
	}
	else if (data->conversion == 'c')
	{
		data->precision = 0;
		--data->width;
	}
	else
	{
		if (data->width < data->len)
			data->width = 0;
		if (data->precision < data->len)
			data->precision = data->len;
	}
}

void				pf_handler(t_printf *data)
{
	pf_get_type(data);
	pf_refresh_data(data);
	if (data->flags & SPC && data->neg == 0)
	{
		pf_buffer(data, ' ');
		--data->width;
	}
	if (data->flags & ZERO)
		pf_handle_flag(data);
	if (!(data->flags & LESS))
		pf_handle_width(data);
	if (!(data->flags & ZERO))
		pf_handle_flag(data);
	pf_handle_precision(data);
	pf_bufferstr(data, data->str);
	if (data->flags & LESS)
		pf_handle_width(data);
	free((void *)data->str);
}
