/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   buffer.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: maboye <maboye@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/08/20 18:03:34 by maboye            #+#    #+#             */
/*   Updated: 2019/08/22 23:40:16 by maboye           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/ft_printf.h"

void				pf_print_buffer(t_printf *data, int len)
{
	int	size;

	if (data->i)
		write(1, data->buf, len);
	size = B_SIZE;
	while (size-- > 0)
		((char *)data->buf)[size] = (unsigned char)0;
	data->i = 0;
}

static inline void	pf_handle_string(t_printf *data, char c)
{
	if (!data->p_token)
		data->buf[data->i++] = c;
	else
	{
		if (data->precision-- > 0)
			data->buf[data->i++] = c;
	}
}

void				pf_bufferstr(t_printf *data, char *str)
{
	int	i;
	int	len;

	i = -1;
	len = pf_strlen(str);
	while (str && str[++i] && i < len)
	{
		if (data->i > B_SIZE - 1)
			pf_print_buffer(data, B_SIZE);
		if (data->conversion == 's')
			pf_handle_string(data, str[i]);
		else
			data->buf[data->i++] = str[i];
		++data->count;
	}
}

void				pf_buffer(t_printf *data, char c)
{
	if (data->i > B_SIZE - 1)
		pf_print_buffer(data, B_SIZE);
	data->buf[data->i++] = c;
	++data->count;
}
