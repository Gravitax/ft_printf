/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   type.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: maboye <maboye@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/08/21 14:57:34 by maboye            #+#    #+#             */
/*   Updated: 2019/08/22 23:40:53 by maboye           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/ft_printf.h"

static void			pf_handle_base(t_printf *data, intmax_t nb)
{
	if (data->conversion == 'c')
	{
		data->str = (char *)pf_memalloc(sizeof(char) * 2);
		*(data->str) = nb;
	}
	else if (data->conversion == 'X')
		data->str = ft_itoa_base(nb, 16);
	else if (data->conversion == 'x')
	{
		data->str = ft_itoa_base(nb, 16);
		pf_strtolower(data->str);
	}
	else
		data->str = ft_itoa_base(nb, 10);
}

static void			pf_unsigned_type(t_printf *data)
{
	uintmax_t	nb;

	if (data->i_conv == L)
		nb = va_arg(data->list, unsigned long);
	else if (data->i_conv == LL)
		nb = va_arg(data->list, unsigned long long);
	else
		nb = va_arg(data->list, unsigned int);
	if (data->i_conv == HH)
		nb = (unsigned char)nb;
	else if (data->i_conv == H)
		nb = (unsigned short)nb;
	data->str = ft_uitoa_base(nb, data->conversion == 'o' ? 8 : 10);
}

static inline void	pf_handle_string(t_printf *data)
{
	data->str = va_arg(data->list, char *);
	if (!data->str)
	{
		data->str = data->precision > 0 ? "(null)" : "";
		data->precision = -1;
		data->p_token = 0;
	}
}

static inline void	pf_handle_pointer(t_printf *data)
{
	data->str = ft_itoa_base((intmax_t)va_arg(data->list, void *), 16);
	pf_strtolower(data->str);
}

void				pf_get_type(t_printf *data)
{
	intmax_t	nb;

	if (pf_strchr("cdixX", data->conversion))
	{
		if (data->i_conv == L)
			nb = va_arg(data->list, long);
		else if (data->i_conv == LL)
			nb = va_arg(data->list, long long);
		else
			nb = va_arg(data->list, int);
		if (data->i_conv == HH)
			nb = (char)nb;
		else if (data->i_conv == H)
			nb = (short)nb;
		pf_handle_base(data, nb);
	}
	else if (data->conversion == 'f')
		pf_handle_float(data);
	else if (data->conversion == 'o' || data->conversion == 'u')
		pf_unsigned_type(data);
	else if (data->conversion == 'p')
		pf_handle_pointer(data);
	else if (data->conversion == 's')
		pf_handle_string(data);
	data->len = pf_strlen(data->str);
}
