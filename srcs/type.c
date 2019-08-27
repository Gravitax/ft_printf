/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   type.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: maboye <maboye@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/08/21 14:57:34 by maboye            #+#    #+#             */
/*   Updated: 2019/08/27 15:25:22 by maboye           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/ft_printf.h"

static void		pf_handle_base(t_printf *data, uintmax_t nb)
{
	if (data->conversion == 'o')
		data->str = ft_uitoa_base(data, nb, 8);
	else if (data->conversion == 'u')
		data->str = ft_uitoa_base(data, nb, 10);
	else if (data->conversion == 'x')
	{
		data->str = ft_uitoa_base(data, nb, 16);
		pf_strtolower(data->str);
	}
	else if (data->conversion == 'X')
		data->str = ft_uitoa_base(data, nb, 16);
}

static void		pf_handle_unsigned(t_printf *data)
{
	uintmax_t	nb;

	if (data->i_conv == L)
		nb = va_arg(data->list, unsigned long);
	else if (data->i_conv == LL)
		nb = va_arg(data->list, unsigned long long);
	else if (data->i_conv == J)
		nb = va_arg(data->list, uintmax_t);
	else if (data->i_conv == Z)
		nb = va_arg(data->list, size_t);
	else
		nb = va_arg(data->list, unsigned int);
	if (data->i_conv == HH)
		nb = (unsigned char)nb;
	else if (data->i_conv == H)
		nb = (unsigned short)nb;
	pf_handle_base(data, nb);
}

static void		pf_handle_ps(t_printf *data, char c)
{
	if (c == 's')
	{
		data->str = pf_strdup(va_arg(data->list, char *));
		if (!data->str)
			data->str = pf_strdup("(null)");
		else if (!pf_strlen(data->str))
			data->str = pf_strdup("");
	}
	else
	{
		data->str = ft_uitoa_base(data,
			(uintmax_t)va_arg(data->list, void *), 16);
		pf_strtolower(data->str);
	}
}

static void		pf_handle_signed(t_printf *data)
{
	intmax_t	nb;

	if (data->i_conv == L)
		nb = va_arg(data->list, long);
	else if (data->i_conv == LL)
		nb = va_arg(data->list, long long);
	else if (data->i_conv == J)
		nb = va_arg(data->list, intmax_t);
	else if (data->i_conv == Z)
		nb = va_arg(data->list, size_t);
	else
		nb = va_arg(data->list, int);
	if (data->i_conv == HH)
		nb = (char)nb;
	else if (data->i_conv == H)
		nb = (short)nb;
	if (data->conversion == 'c')
	{
		data->str = (char *)pf_memalloc(sizeof(char) * 2);
		*(data->str) = (char)nb;
	}
	else
		data->str = ft_itoa_base(data, nb, 10);
}

void			pf_get_type(t_printf *data)
{
	if (pf_strchr("cdi", data->conversion))
		pf_handle_signed(data);
	else if (data->conversion == 's' || data->conversion == 'p')
		pf_handle_ps(data, data->conversion);
	else if (pf_strchr("ouxX", data->conversion))
		pf_handle_unsigned(data);
	else if (data->conversion == 'f')
		pf_handle_float(data);
	data->len = data->conversion == 'c' ? 1 : pf_strlen(data->str);
}
