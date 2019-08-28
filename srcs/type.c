/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   type.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: maboye <maboye@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/08/21 14:57:34 by maboye            #+#    #+#             */
/*   Updated: 2019/08/28 13:25:49 by maboye           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/ft_printf.h"

static void		handle_ubase(t_printf *data, uintmax_t nb)
{
	if (data->conversion == 'o')
		data->str = ft_uitoa_base(data, nb, 8);
	else if (data->conversion == 'u')
		data->str = ft_uitoa_base(data, nb, 10);
	else if (data->conversion == 'X')
		data->str = ft_uitoa_base(data, nb, 16);
	else
	{
		data->str = ft_uitoa_base(data, nb, 16);
		pf_strtolower(data->str);
	}
}

static void		pf_handle_unsigned(t_printf *data)
{
	uintmax_t	nb;

	if (data->i_conv)
	{
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
	}
	else
		nb = va_arg(data->list, unsigned int);
	handle_ubase(data, nb);
}

static void		handle_base(t_printf *data, intmax_t nb)
{
	if (data->conversion == 'c')
	{
		data->str = (char *)pf_memalloc(sizeof(char) * 2);
		*(data->str) = nb;
	}
	else
		data->str = ft_itoa_base(data, nb, 10);
}

static void		pf_handle_signed(t_printf *data)
{
	intmax_t	nb;

	if (data->i_conv)
	{
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
	}
	else
		nb = va_arg(data->list, int);
	handle_base(data, nb);
}

void			pf_get_type(t_printf *data)
{
	if (data->conversion == 's')
	{
		data->str = pf_strdup(va_arg(data->list, char *));
		if (!data->str)
			data->str = pf_strdup("(null)");
		else if (!pf_strlen(data->str))
			data->str = pf_strdup("");
	}
	else if (data->conversion == 'p')
	{
		data->str = ft_uitoa_base(data,
			(uintmax_t)va_arg(data->list, void *), 16);
		pf_strtolower(data->str);
	}
	else if (pf_strchr("cdi", data->conversion))
		pf_handle_signed(data);
	else if (data->conversion == 'f')
		pf_handle_float(data);
	else if (pf_strchr("ouxX", data->conversion))
		pf_handle_unsigned(data);
	data->len = data->conversion == 'c' ? 1 : pf_strlen(data->str);
}
